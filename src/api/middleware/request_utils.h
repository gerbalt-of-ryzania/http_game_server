#pragma once

#include <algorithm>
#include <charconv>
#include <cctype>
#include <optional>
#include <string>
#include <string_view>
#include <system_error>

#include <boost/beast/http.hpp>

namespace api::middleware {
namespace beast = boost::beast;
namespace http = beast::http;

template <typename Body, typename Allocator>
std::string_view ExtractPath(const http::request<Body, http::basic_fields<Allocator>>& req) {
    std::string_view target = req.target();
    std::string_view path = target.substr(0, target.find('?'));
    if (!path.starts_with('/')) {
        if (const auto scheme_pos = path.find("://"); scheme_pos != std::string_view::npos) {
            const auto path_pos = path.find('/', scheme_pos + 3);
            path = (path_pos == std::string_view::npos) ? std::string_view{"/"} : path.substr(path_pos);
        }
    }
    return path;
}

template <typename Body, typename Allocator>
bool IsJsonContentType(const http::request<Body, http::basic_fields<Allocator>>& req) {
    const auto value = req[http::field::content_type];
    if (value.empty()) {
        return false;
    }
    std::string lower(value);
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return lower == "application/json" || lower.starts_with("application/json;");
}

template <typename Body, typename Allocator>
std::optional<std::string> ExtractBearerToken(const http::request<Body, http::basic_fields<Allocator>>& req) {
    const auto auth = req[http::field::authorization];
    if (auth.empty()) {
        return std::nullopt;
    }
    constexpr std::string_view prefix = "Bearer ";
    std::string auth_value(auth);
    if (!auth_value.starts_with(prefix)) {
        return std::nullopt;
    }
    std::string token = auth_value.substr(prefix.size());
    if (token.size() != 32) {
        return std::nullopt;
    }
    for (char ch : token) {
        const bool is_digit = (ch >= '0' && ch <= '9');
        const bool is_hex_alpha = (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
        if (!is_digit && !is_hex_alpha) {
            return std::nullopt;
        }
    }
    return token;
}

bool ParseRecordsQuery(std::string_view target, std::size_t& start, std::size_t& max_items);

}  // namespace api::middleware
