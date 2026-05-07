#pragma once

#include "extra_data.h"
#include "game_serializers.h"
#include "model.h"
#include "records_repository.h"
#include "request_utils.h"
#include "responses.h"
#include "static_file_handler.h"

#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <utility>

#include <boost/asio/post.hpp>
#include <boost/asio/strand.hpp>
#include <boost/filesystem.hpp>
#include <boost/json.hpp>

namespace http_handler {
namespace beast = boost::beast;
namespace http = beast::http;
namespace json = boost::json;
namespace fs = boost::filesystem;
namespace net = boost::asio;

using ApiStrand = net::strand<net::io_context::executor_type>;

struct Endpoints {
    static constexpr std::string_view Api = "/api/";
    static constexpr std::string_view Maps = "/api/v1/maps";
    static constexpr std::string_view MapsPrefix = "/api/v1/maps/";
    static constexpr std::string_view JoinGame = "/api/v1/game/join";
    static constexpr std::string_view Players = "/api/v1/game/players";
    static constexpr std::string_view GameState = "/api/v1/game/state";
    static constexpr std::string_view PlayerAction = "/api/v1/game/player/action";
    static constexpr std::string_view GameTick = "/api/v1/game/tick";
    static constexpr std::string_view Records = "/api/v1/game/records";
};

class RequestHandler {
   public:
    explicit RequestHandler(model::Game& game, const extra_data::MapExtraData& map_extra_data,
                            postgres::RecordsRepository& records_repository, fs::path static_root, ApiStrand api_strand,
                            bool enable_http_tick = true)
        : game_{game},
          map_extra_data_{map_extra_data},
          records_repository_{records_repository},
          static_files_{std::move(static_root)},
          api_strand_{std::move(api_strand)},
          http_tick_enabled_{enable_http_tick} {}

    RequestHandler(const RequestHandler&) = delete;
    RequestHandler& operator=(const RequestHandler&) = delete;

    template <typename Body, typename Allocator, typename Send>
    void operator()(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        const std::string path_str{api::middleware::ExtractPath(req)};

        if (path_str.starts_with(Endpoints::Api)) {
            net::post(api_strand_, [this, path_str, req = std::move(req), send = std::forward<Send>(send)]() mutable {
                ProcessApi(std::string_view{path_str}, std::move(req), std::move(send));
            });
            return;
        }

        static_files_.Handle(req, std::string_view{path_str}, std::forward<Send>(send));
    }

   private:
    model::Game& game_;
    const extra_data::MapExtraData& map_extra_data_;
    postgres::RecordsRepository& records_repository_;
    api::static_files::StaticFileHandler static_files_;
    ApiStrand api_strand_;
    bool http_tick_enabled_;

    template <typename Body, typename Allocator, typename Send>
    void ProcessApi(std::string_view path, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        if (path == Endpoints::JoinGame) {
            return HandleJoinGame(std::move(req), std::forward<Send>(send));
        }
        if (path == Endpoints::Players) {
            return HandlePlayers(std::move(req), std::forward<Send>(send));
        }
        if (path == Endpoints::GameState) {
            return HandleGameState(std::move(req), std::forward<Send>(send));
        }
        if (path == Endpoints::PlayerAction) {
            return HandlePlayerAction(std::move(req), std::forward<Send>(send));
        }
        if (path == Endpoints::GameTick) {
            if (!http_tick_enabled_) {
                return send(
                    api::responses::MakeApiError(req, http::status::bad_request, "badRequest", "Invalid endpoint"));
            }
            return HandleGameTick(std::move(req), std::forward<Send>(send));
        }
        if (path == Endpoints::Records) {
            return HandleRecords(std::move(req), std::forward<Send>(send));
        }

        HandleMapRequest(path, std::move(req), std::forward<Send>(send));
    }

    template <typename Body, typename Allocator, typename Send>
    void HandleMapRequest(std::string_view path, http::request<Body, http::basic_fields<Allocator>>&& req,
                          Send&& send) {
        if (req.method() != http::verb::get && req.method() != http::verb::head) {
            return send(api::responses::MakeApiError(req, http::status::method_not_allowed, "invalidMethod",
                                                     "Invalid method", "GET, HEAD"));
        }

        if (path == Endpoints::Maps) {
            const std::string body = json::serialize(api::serializers::SerializeMapsList(game_.GetMaps()));
            if (req.method() == http::verb::head) {
                return send(api::responses::MakeApiJsonHeadResponse(req, http::status::ok, body.size()));
            }
            return send(api::responses::MakeApiJsonResponse(req, http::status::ok, body));
        }

        if (path.starts_with(Endpoints::MapsPrefix)) {
            std::string_view id_str = path.substr(Endpoints::MapsPrefix.size());
            if (id_str.empty()) {
                return send(api::responses::MakeApiError(req, http::status::bad_request, "badRequest", "Bad request"));
            }
            model::Map::Id id{std::string{id_str}};
            const model::Map* map = game_.FindMap(id);
            if (!map) {
                return send(api::responses::MakeApiError(req, http::status::not_found, "mapNotFound", "Map not found"));
            }
            return send(api::responses::MakeApiJsonResponse(
                req, http::status::ok, json::serialize(api::serializers::SerializeMap(*map, map_extra_data_))));
        }

        return send(api::responses::MakeApiError(req, http::status::bad_request, "badRequest", "Invalid endpoint"));
    }

    template <typename Body, typename Allocator, typename Send>
    void HandleJoinGame(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        if (req.method() != http::verb::post) {
            return send(api::responses::MakeApiError(req, http::status::method_not_allowed, "invalidMethod",
                                                     "Only POST method is expected", "POST"));
        }
        if (!api::middleware::IsJsonContentType(req)) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Join game request parse error"));
        }

        try {
            const json::value value = json::parse(req.body());
            const json::object& obj = value.as_object();
            const std::string user_name = json::value_to<std::string>(obj.at("userName"));
            const std::string map_id = json::value_to<std::string>(obj.at("mapId"));

            if (user_name.empty()) {
                return send(
                    api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument", "Invalid name"));
            }

            if (!game_.FindMap(model::Map::Id{map_id})) {
                return send(api::responses::MakeApiError(req, http::status::not_found, "mapNotFound", "Map not found"));
            }

            const auto join_result = game_.JoinGame(user_name, model::Map::Id{map_id});
            json::object response_body;
            response_body["authToken"] = join_result.auth_token;
            response_body["playerId"] = join_result.player_id;
            return send(api::responses::MakeApiJsonResponse(req, http::status::ok, json::serialize(response_body)));
        } catch (const std::exception&) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Join game request parse error"));
        }
    }

    template <typename Body, typename Allocator, typename Send>
    void HandlePlayers(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        if (req.method() != http::verb::get && req.method() != http::verb::head) {
            return send(api::responses::MakeApiError(req, http::status::method_not_allowed, "invalidMethod",
                                                     "Invalid method", "GET, HEAD"));
        }

        const auto token = api::middleware::ExtractBearerToken(req);
        if (!token) {
            return send(api::responses::MakeApiError(req, http::status::unauthorized, "invalidToken",
                                                     "Authorization header is missing"));
        }

        const model::Game::Player* current_player = game_.FindPlayerByToken(*token);
        if (!current_player) {
            return send(api::responses::MakeApiError(req, http::status::unauthorized, "unknownToken",
                                                     "Player token has not been found"));
        }

        const std::string body =
            json::serialize(api::serializers::SerializePlayers(game_.GetPlayersByMap(current_player->map_id)));
        if (req.method() == http::verb::head) {
            return send(api::responses::MakeApiJsonHeadResponse(req, http::status::ok, body.size()));
        }
        return send(api::responses::MakeApiJsonResponse(req, http::status::ok, body));
    }

    template <typename Body, typename Allocator, typename Send>
    void HandleGameState(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        if (req.method() != http::verb::get && req.method() != http::verb::head) {
            return send(api::responses::MakeApiError(req, http::status::method_not_allowed, "invalidMethod",
                                                     "Invalid method", "GET, HEAD"));
        }

        const model::Game::Player* current_player = AuthorizePlayer(req, "Authorization header is required", send);
        if (!current_player) {
            return;
        }

        const std::string body = json::serialize(api::serializers::SerializeGameState(
            game_.GetPlayersByMap(current_player->map_id), game_.GetLostObjectsByMap(current_player->map_id)));
        if (req.method() == http::verb::head) {
            return send(api::responses::MakeApiJsonHeadResponse(req, http::status::ok, body.size()));
        }
        return send(api::responses::MakeApiJsonResponse(req, http::status::ok, body));
    }

    template <typename Body, typename Allocator, typename Send>
    void HandlePlayerAction(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        if (req.method() != http::verb::post) {
            return send(api::responses::MakeApiError(req, http::status::method_not_allowed, "invalidMethod",
                                                     "Invalid method", "POST"));
        }
        if (!api::middleware::IsJsonContentType(req)) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Invalid content type"));
        }

        const auto token = api::middleware::ExtractBearerToken(req);
        if (!token) {
            return send(api::responses::MakeApiError(req, http::status::unauthorized, "invalidToken",
                                                     "Authorization header is required"));
        }

        if (!game_.FindPlayerByToken(*token)) {
            return send(api::responses::MakeApiError(req, http::status::unauthorized, "unknownToken",
                                                     "Player token has not been found"));
        }

        std::string move_str;
        try {
            const json::value value = json::parse(req.body());
            const json::object& obj = value.as_object();
            const auto& mv = obj.at("move");
            if (!mv.is_string()) {
                return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                         "Failed to parse action"));
            }
            move_str = std::string{mv.as_string()};
        } catch (const std::exception&) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Failed to parse action"));
        }

        const std::string_view mv = move_str;
        if (!(mv == "L" || mv == "R" || mv == "U" || mv == "D" || mv.empty())) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Failed to parse action"));
        }

        game_.ApplyPlayerMove(*token, mv);
        return send(api::responses::MakeApiJsonResponse(req, http::status::ok, "{}"));
    }

    template <typename Body, typename Allocator, typename Send>
    void HandleGameTick(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        if (req.method() != http::verb::post) {
            return send(api::responses::MakeApiError(req, http::status::method_not_allowed, "invalidMethod",
                                                     "Invalid method", "POST"));
        }
        if (!api::middleware::IsJsonContentType(req)) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Failed to parse tick request JSON"));
        }

        int64_t time_delta_ms = 0;
        try {
            const json::value value = json::parse(req.body());
            const json::object& obj = value.as_object();
            const json::value& td = obj.at("timeDelta");
            if (td.is_int64()) {
                time_delta_ms = td.as_int64();
            } else if (td.is_uint64()) {
                const std::uint64_t u = td.as_uint64();
                if (u > static_cast<std::uint64_t>(std::numeric_limits<int64_t>::max())) {
                    return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                             "Invalid timeDelta value"));
                }
                time_delta_ms = static_cast<int64_t>(u);
            } else {
                return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                         "Invalid timeDelta value"));
            }
        } catch (const std::exception&) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Failed to parse tick request JSON"));
        }

        if (time_delta_ms < 0) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Invalid timeDelta value"));
        }

        game_.Tick(time_delta_ms);
        return send(api::responses::MakeApiJsonResponse(req, http::status::ok, "{}"));
    }

    template <typename Body, typename Allocator, typename Send>
    void HandleRecords(http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        if (req.method() != http::verb::get && req.method() != http::verb::head) {
            return send(api::responses::MakeApiError(req, http::status::method_not_allowed, "invalidMethod",
                                                     "Invalid method", "GET, HEAD"));
        }

        std::size_t start = 0;
        std::size_t max_items = 100;
        if (!api::middleware::ParseRecordsQuery(req.target(), start, max_items)) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "Invalid query parameters"));
        }
        if (max_items > 100) {
            return send(api::responses::MakeApiError(req, http::status::bad_request, "invalidArgument",
                                                     "maxItems must not exceed 100"));
        }

        const std::string body =
            json::serialize(api::serializers::SerializeRecords(records_repository_.GetRecords(start, max_items)));
        if (req.method() == http::verb::head) {
            return send(api::responses::MakeApiJsonHeadResponse(req, http::status::ok, body.size()));
        }
        return send(api::responses::MakeApiJsonResponse(req, http::status::ok, body));
    }

    template <typename Body, typename Allocator, typename Send>
    const model::Game::Player* AuthorizePlayer(const http::request<Body, http::basic_fields<Allocator>>& req,
                                               std::string_view missing_message, Send& send) {
        const auto token = api::middleware::ExtractBearerToken(req);
        if (!token) {
            send(api::responses::MakeApiError(req, http::status::unauthorized, "invalidToken", missing_message));
            return nullptr;
        }

        const model::Game::Player* player = game_.FindPlayerByToken(*token);
        if (!player) {
            send(api::responses::MakeApiError(req, http::status::unauthorized, "unknownToken",
                                              "Player token has not been found"));
            return nullptr;
        }

        return player;
    }
};

}  // namespace http_handler
