#pragma once

#include "logger.h"
#include "request_context.h"

#include <optional>
#include <string>
#include <string_view>

#include <boost/beast/http.hpp>
#include <boost/json.hpp>

namespace api::responses {
namespace beast = boost::beast;
namespace http = beast::http;
namespace json = boost::json;

inline beast::string_view ToBeastStringView(std::string_view value) noexcept {
    return {value.data(), value.size()};
}

inline void SetRequestId(auto& res, const api::RequestContext& ctx) {
    res.set("X-Request-Id", ctx.request_id);
}

inline void LogCompleted(const api::RequestContext& ctx, http::status status) {
    if (static_cast<unsigned>(status) >= 400) {
        return;
    }

    infra::log::Info("http_request_completed", {
                                                   {"request_id", ctx.request_id},
                                                   {"method", ctx.method},
                                                   {"path", ctx.path},
                                                   {"status", static_cast<int>(status)},
                                               });
}

template <typename Body, typename Allocator>
http::response<http::string_body> MakeApiJsonResponse(const api::RequestContext& ctx,
                                                      const http::request<Body, http::basic_fields<Allocator>>& req,
                                                      http::status status, std::string body) {
    http::response<http::string_body> res{status, req.version()};
    res.set(http::field::content_type, "application/json");
    res.set(http::field::cache_control, "no-cache");
    SetRequestId(res, ctx);
    res.body() = std::move(body);
    res.content_length(res.body().size());
    res.keep_alive(req.keep_alive());
    LogCompleted(ctx, status);
    return res;
}

template <typename Body, typename Allocator>
http::response<http::empty_body> MakeApiJsonHeadResponse(const api::RequestContext& ctx,
                                                         const http::request<Body, http::basic_fields<Allocator>>& req,
                                                         http::status status, std::size_t content_length) {
    http::response<http::empty_body> res{status, req.version()};
    res.set(http::field::content_type, "application/json");
    res.set(http::field::cache_control, "no-cache");
    SetRequestId(res, ctx);
    res.content_length(content_length);
    res.keep_alive(req.keep_alive());
    LogCompleted(ctx, status);
    return res;
}

template <typename Body, typename Allocator>
http::response<http::string_body> MakeStringResponse(const api::RequestContext& ctx,
                                                     const http::request<Body, http::basic_fields<Allocator>>& req,
                                                     http::status status, std::string body,
                                                     std::string_view content_type = "text/plain") {
    http::response<http::string_body> res{status, req.version()};
    res.set(http::field::content_type, ToBeastStringView(content_type));
    SetRequestId(res, ctx);
    res.body() = std::move(body);
    res.content_length(res.body().size());
    res.keep_alive(req.keep_alive());
    LogCompleted(ctx, status);
    return res;
}

template <typename Body, typename Allocator>
auto MakeApiError(const api::RequestContext& ctx, const http::request<Body, http::basic_fields<Allocator>>& req,
                  http::status status, std::string_view code, std::string_view message,
                  std::optional<std::string_view> allow = std::nullopt) {
    infra::log::Warning("http_request_failed", {
                                                   {"request_id", ctx.request_id},
                                                   {"method", ctx.method},
                                                   {"path", ctx.path},
                                                   {"status", static_cast<int>(status)},
                                                   {"error_code", std::string(code)},
                                                   {"message", std::string(message)},
                                               });

    json::object obj;
    obj["code"] = std::string(code);
    obj["message"] = std::string(message);
    auto res = MakeApiJsonResponse(ctx, req, status, json::serialize(obj));
    if (allow) {
        res.set(http::field::allow, *allow);
    }
    return res;
}

template <typename Body, typename Allocator, typename Send>
void SendPlainText(const api::RequestContext& ctx, const http::request<Body, http::basic_fields<Allocator>>& req,
                   http::status status, std::string_view text, Send&& send) {
    if (req.method() == http::verb::head) {
        http::response<http::empty_body> res{status, req.version()};
        res.set(http::field::content_type, "text/plain");
        SetRequestId(res, ctx);
        res.content_length(text.size());
        res.keep_alive(req.keep_alive());
        LogCompleted(ctx, status);
        send(std::move(res));
        return;
    }

    send(MakeStringResponse(ctx, req, status, std::string(text)));
}

}  // namespace api::responses
