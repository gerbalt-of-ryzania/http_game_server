#pragma once

#include "connection_pool.h"

#include <cstddef>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace postgres {

struct RetiredPlayerRecord {
    std::string name;
    std::uint64_t score = 0;
    std::int64_t play_time_ms = 0;
};

class RecordsRepository {
   public:
    explicit RecordsRepository(std::string db_url, std::size_t pool_size = 4);

    void Save(const RetiredPlayerRecord& record, std::string_view request_id = {});

    std::vector<RetiredPlayerRecord> GetRecords(std::size_t start, std::size_t max_items,
                                                std::string_view request_id = {}) const;

   private:
    void InitDatabase();

    mutable ConnectionPool connection_pool_;
};

}  // namespace postgres
