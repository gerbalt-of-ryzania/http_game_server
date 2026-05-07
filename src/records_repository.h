#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace postgres {

struct RetiredPlayerRecord {
    std::string name;
    std::uint64_t score = 0;
    std::int64_t play_time_ms = 0;
};

class RecordsRepository {
   public:
    explicit RecordsRepository(std::string db_url);

    void Save(const RetiredPlayerRecord& record);

    std::vector<RetiredPlayerRecord> GetRecords(std::size_t start, std::size_t max_items) const;

   private:
    void InitDatabase();

    std::string db_url_;
};

}  // namespace postgres
