#include "request_utils.h"

namespace api::middleware {

namespace {

bool ParseSizeT(std::string_view value, std::size_t& result) {
    if (value.empty()) {
        return false;
    }
    std::size_t parsed = 0;
    const char* begin = value.data();
    const char* end = value.data() + value.size();
    const auto [ptr, ec] = std::from_chars(begin, end, parsed);
    if (ec != std::errc{} || ptr != end) {
        return false;
    }
    result = parsed;
    return true;
}

}  // namespace

bool ParseRecordsQuery(std::string_view target, std::size_t& start, std::size_t& max_items) {
    const auto query_pos = target.find('?');
    if (query_pos == std::string_view::npos) {
        return true;
    }

    std::string_view query = target.substr(query_pos + 1);
    while (!query.empty()) {
        const auto amp_pos = query.find('&');
        const std::string_view part = query.substr(0, amp_pos);
        const auto eq_pos = part.find('=');
        if (eq_pos != std::string_view::npos) {
            const std::string_view key = part.substr(0, eq_pos);
            const std::string_view value = part.substr(eq_pos + 1);
            if (key == "start" || key == "maxItems") {
                std::size_t parsed = 0;
                if (!ParseSizeT(value, parsed)) {
                    return false;
                }
                if (key == "start") {
                    start = parsed;
                } else {
                    max_items = parsed;
                }
            }
        }

        if (amp_pos == std::string_view::npos) {
            break;
        }
        query = query.substr(amp_pos + 1);
    }

    return true;
}

}  // namespace api::middleware
