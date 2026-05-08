#include "records_repository.h"

#include "logger.h"

#include <utility>

namespace postgres {

RecordsRepository::RecordsRepository(std::string db_url, std::size_t pool_size)
    : connection_pool_{std::move(db_url), pool_size} {
    InitDatabase();
}

void RecordsRepository::InitDatabase() {
    try {
        auto conn = connection_pool_.GetConnection();
        pqxx::work tx{*conn};

        tx.exec(R"(
        CREATE TABLE IF NOT EXISTS retired_players (
            id BIGSERIAL PRIMARY KEY,
            name TEXT NOT NULL,
            score BIGINT NOT NULL,
            play_time_ms BIGINT NOT NULL
        );
    )");

        tx.exec(R"(
        CREATE INDEX IF NOT EXISTS retired_players_order_idx
        ON retired_players (score DESC, play_time_ms ASC, name ASC);
    )");

        tx.commit();
    } catch (const std::exception& ex) {
        infra::log::Error("db_init_failed", {{"message", ex.what()}});
        throw;
    }
}

void RecordsRepository::Save(const RetiredPlayerRecord& record, std::string_view request_id) {
    try {
        auto conn = connection_pool_.GetConnection();
        pqxx::work tx{*conn};

        tx.exec_params(
            R"(
            INSERT INTO retired_players (name, score, play_time_ms)
            VALUES ($1, $2, $3);
        )",
            record.name, record.score, record.play_time_ms);

        tx.commit();
    } catch (const std::exception& ex) {
        infra::log::Error("db_query_failed", {
                                                 {"request_id", std::string(request_id)},
                                                 {"operation", "save_retired_player"},
                                                 {"message", ex.what()},
                                             });
        throw;
    }
}

std::vector<RetiredPlayerRecord> RecordsRepository::GetRecords(std::size_t start, std::size_t max_items,
                                                               std::string_view request_id) const {
    try {
        auto conn = connection_pool_.GetConnection();
        pqxx::read_transaction tx{*conn};

        const auto result = tx.exec_params(
            R"(
            SELECT name, score, play_time_ms
            FROM retired_players
            ORDER BY score DESC, play_time_ms ASC, name ASC
            OFFSET $1
            LIMIT $2;
        )",
            start, max_items);

        std::vector<RetiredPlayerRecord> records;
        records.reserve(result.size());

        for (const auto& row : result) {
            records.push_back({
                row["name"].as<std::string>(),
                row["score"].as<std::uint64_t>(),
                row["play_time_ms"].as<std::int64_t>(),
            });
        }

        return records;
    } catch (const std::exception& ex) {
        infra::log::Error("db_query_failed", {
                                                 {"request_id", std::string(request_id)},
                                                 {"operation", "get_retired_player_records"},
                                                 {"message", ex.what()},
                                             });
        throw;
    }
}

}  // namespace postgres
