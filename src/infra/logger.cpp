#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

namespace infra::log {
namespace json = boost::json;

namespace {

std::mutex log_mutex;

const char* LevelToString(Level level) {
    switch (level) {
        case Level::Info:
            return "info";
        case Level::Warning:
            return "warning";
        case Level::Error:
            return "error";
    }
    return "info";
}

std::string TimestampUtc() {
    using namespace std::chrono;

    const auto now = system_clock::now();
    const auto time = system_clock::to_time_t(now);
    const auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    std::tm tm{};
    gmtime_r(&time, &tm);

    std::ostringstream out;
    out << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
    out << '.' << std::setw(3) << std::setfill('0') << ms.count() << 'Z';
    return out.str();
}

}  // namespace

void Write(Level level, std::string_view event, json::object fields) {
    json::object log_record;
    log_record["timestamp"] = TimestampUtc();
    log_record["level"] = LevelToString(level);
    log_record["event"] = std::string(event);

    for (auto& field : fields) {
        log_record[field.key()] = std::move(field.value());
    }

    std::lock_guard lock{log_mutex};
    auto& stream = (level == Level::Error) ? std::cerr : std::cout;
    stream << json::serialize(log_record) << std::endl;
}

void Info(std::string_view event, json::object fields) {
    Write(Level::Info, event, std::move(fields));
}

void Warning(std::string_view event, json::object fields) {
    Write(Level::Warning, event, std::move(fields));
}

void Error(std::string_view event, json::object fields) {
    Write(Level::Error, event, std::move(fields));
}

}  // namespace infra::log
