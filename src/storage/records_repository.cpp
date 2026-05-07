#include "records_repository.h"

#include <pqxx/pqxx>

#include <utility>

namespace postgres {

RecordsRepository::RecordsRepository(std::string db_url) : db_url_(std::move(db_url)) {
    InitDatabase();
}

void RecordsRepository::InitDatabase() {
    pqxx::connection conn{db_url_};
    pqxx::work tx{conn};

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
}

void RecordsRepository::Save(const RetiredPlayerRecord& record) {
    pqxx::connection conn{db_url_};
    pqxx::work tx{conn};

    tx.exec_params(
        R"(
            INSERT INTO retired_players (name, score, play_time_ms)
            VALUES ($1, $2, $3);
        )",
        record.name, record.score, record.play_time_ms);

    tx.commit();
}

std::vector<RetiredPlayerRecord> RecordsRepository::GetRecords(std::size_t start, std::size_t max_items) const {
    pqxx::connection conn{db_url_};
    pqxx::read_transaction tx{conn};

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
}

}  // namespace postgres
