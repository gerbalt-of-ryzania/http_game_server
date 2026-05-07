#pragma once

#include "extra_data.h"
#include "model.h"
#include "records_repository.h"

#include <boost/json.hpp>

#include <vector>

namespace api::serializers {
namespace json = boost::json;

json::array SerializeMapsList(const model::Game::Maps& maps);
json::object SerializeMap(const model::Map& map, const extra_data::MapExtraData& map_extra_data);
json::object SerializePlayers(const std::vector<const model::Game::Player*>& players);
json::object SerializeGameState(const std::vector<const model::Game::Player*>& players,
                                const std::vector<const model::Game::LostObject*>& lost_objects);
json::array SerializeRecords(const std::vector<postgres::RetiredPlayerRecord>& records);

}  // namespace api::serializers
