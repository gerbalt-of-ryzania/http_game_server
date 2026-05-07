#include "game_serializers.h"

#include <cstdint>
#include <string>

namespace api::serializers {

namespace {

const char* DirectionToApiLetter(model::Direction d) noexcept {
    using model::Direction;
    switch (d) {
        case Direction::NORTH:
            return "U";
        case Direction::SOUTH:
            return "D";
        case Direction::WEST:
            return "L";
        case Direction::EAST:
            return "R";
    }
    return "U";
}

json::object SerializeRoad(const model::Road& road) {
    json::object road_obj;
    road_obj["x0"] = road.GetStart().x;
    road_obj["y0"] = road.GetStart().y;
    if (road.IsHorizontal()) {
        road_obj["x1"] = road.GetEnd().x;
    } else {
        road_obj["y1"] = road.GetEnd().y;
    }
    return road_obj;
}

json::object SerializeBuilding(const model::Building& building) {
    const auto& rect = building.GetBounds();
    json::object building_obj;
    building_obj["x"] = rect.position.x;
    building_obj["y"] = rect.position.y;
    building_obj["w"] = rect.size.width;
    building_obj["h"] = rect.size.height;
    return building_obj;
}

json::object SerializeOffice(const model::Office& office) {
    json::object office_obj;
    office_obj["id"] = *office.GetId();
    office_obj["x"] = office.GetPosition().x;
    office_obj["y"] = office.GetPosition().y;
    office_obj["offsetX"] = office.GetOffset().dx;
    office_obj["offsetY"] = office.GetOffset().dy;
    return office_obj;
}

}  // namespace

json::array SerializeMapsList(const model::Game::Maps& maps) {
    json::array arr;
    for (const auto& map : maps) {
        json::object obj;
        obj["id"] = *map.GetId();
        obj["name"] = map.GetName();
        arr.push_back(std::move(obj));
    }
    return arr;
}

json::object SerializeMap(const model::Map& map, const extra_data::MapExtraData& map_extra_data) {
    json::object obj;
    obj["id"] = *map.GetId();
    obj["name"] = map.GetName();

    json::array roads;
    for (const auto& road : map.GetRoads()) {
        roads.push_back(SerializeRoad(road));
    }
    obj["roads"] = std::move(roads);

    json::array buildings;
    for (const auto& building : map.GetBuildings()) {
        buildings.push_back(SerializeBuilding(building));
    }
    obj["buildings"] = std::move(buildings);

    json::array offices;
    for (const auto& office : map.GetOffices()) {
        offices.push_back(SerializeOffice(office));
    }
    obj["offices"] = std::move(offices);

    if (const json::array* loot_types = map_extra_data.FindLootTypes(map.GetId())) {
        obj["lootTypes"] = *loot_types;
    }

    return obj;
}

json::object SerializePlayers(const std::vector<const model::Game::Player*>& players) {
    json::object response_body;
    for (const model::Game::Player* player : players) {
        json::object player_data;
        player_data["name"] = player->name;
        response_body[std::to_string(player->id)] = std::move(player_data);
    }
    return response_body;
}

json::object SerializeGameState(const std::vector<const model::Game::Player*>& players,
                                const std::vector<const model::Game::LostObject*>& lost_objects) {
    json::object response_body;
    json::object players_obj;
    for (const model::Game::Player* player : players) {
        json::object player_data;
        json::array pos;
        pos.push_back(player->position.x);
        pos.push_back(player->position.y);
        player_data["pos"] = std::move(pos);

        json::array speed;
        speed.push_back(player->speed.x);
        speed.push_back(player->speed.y);
        player_data["speed"] = std::move(speed);

        player_data["dir"] = DirectionToApiLetter(player->direction);

        json::array bag;
        for (const auto& item : player->bag) {
            json::object bag_item;
            bag_item["id"] = item.id;
            bag_item["type"] = static_cast<std::uint64_t>(item.type);
            bag.push_back(std::move(bag_item));
        }
        player_data["bag"] = std::move(bag);
        player_data["score"] = static_cast<std::uint64_t>(player->score);
        players_obj[std::to_string(player->id)] = std::move(player_data);
    }
    response_body["players"] = std::move(players_obj);

    json::object lost_objects_obj;
    for (const model::Game::LostObject* lost_object : lost_objects) {
        json::object lost_object_data;
        lost_object_data["type"] = static_cast<std::uint64_t>(lost_object->type);
        json::array pos;
        pos.push_back(lost_object->position.x);
        pos.push_back(lost_object->position.y);
        lost_object_data["pos"] = std::move(pos);
        lost_objects_obj[std::to_string(lost_object->id)] = std::move(lost_object_data);
    }
    response_body["lostObjects"] = std::move(lost_objects_obj);

    return response_body;
}

json::array SerializeRecords(const std::vector<postgres::RetiredPlayerRecord>& records) {
    json::array arr;
    for (const auto& record : records) {
        json::object obj;
        obj["name"] = record.name;
        obj["score"] = record.score;
        obj["playTime"] = static_cast<double>(record.play_time_ms) / 1000.0;
        arr.push_back(std::move(obj));
    }
    return arr;
}

}  // namespace api::serializers
