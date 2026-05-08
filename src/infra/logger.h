#pragma once

#include <string_view>

#include <boost/json.hpp>

namespace infra::log {

enum class Level { Info, Warning, Error };

void Write(Level level, std::string_view event, boost::json::object fields = {});
void Info(std::string_view event, boost::json::object fields = {});
void Warning(std::string_view event, boost::json::object fields = {});
void Error(std::string_view event, boost::json::object fields = {});

}  // namespace infra::log
