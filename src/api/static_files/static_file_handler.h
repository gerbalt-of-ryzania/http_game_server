#pragma once

#include "responses.h"

#include <algorithm>
#include <cctype>
#include <optional>
#include <string>
#include <string_view>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/filesystem.hpp>

namespace api::static_files {
namespace beast = boost::beast;
namespace http = beast::http;
namespace fs = boost::filesystem;

class StaticFileHandler {
   public:
    explicit StaticFileHandler(fs::path static_root) : static_root_{fs::canonical(std::move(static_root))} {}

    template <typename Body, typename Allocator, typename Send>
    void Handle(const http::request<Body, http::basic_fields<Allocator>>& req, std::string_view path,
                Send&& send) const {
        if (req.method() != http::verb::get && req.method() != http::verb::head) {
            return responses::SendPlainText(req, http::status::method_not_allowed, "Method not allowed",
                                            std::forward<Send>(send));
        }

        auto file_path = ResolveStaticPath(path);
        if (!file_path) {
            return responses::SendPlainText(req, http::status::bad_request, "Bad request", std::forward<Send>(send));
        }

        SendFile(req, *file_path, std::forward<Send>(send));
    }

   private:
    fs::path static_root_;

    template <typename Body, typename Allocator, typename Send>
    static void SendFile(const http::request<Body, http::basic_fields<Allocator>>& req, const fs::path& path,
                         Send&& send) {
        beast::error_code ec;
        http::file_body::value_type file;
        file.open(path.string().c_str(), beast::file_mode::scan, ec);
        if (ec) {
            responses::SendPlainText(req, http::status::not_found, "File not found", std::forward<Send>(send));
            return;
        }

        const auto file_size = file.size();
        const auto content_type = GetMimeType(path.extension().string());

        if (req.method() == http::verb::head) {
            http::response<http::empty_body> res{http::status::ok, req.version()};
            res.set(http::field::content_type, responses::ToBeastStringView(content_type));
            res.content_length(file_size);
            res.keep_alive(req.keep_alive());
            send(std::move(res));
            return;
        }

        http::response<http::file_body> res{http::status::ok, req.version()};
        res.set(http::field::content_type, responses::ToBeastStringView(content_type));
        res.content_length(file_size);
        res.keep_alive(req.keep_alive());
        res.body() = std::move(file);
        send(std::move(res));
    }

    std::optional<fs::path> ResolveStaticPath(std::string_view path) const {
        if (path.empty() || path.front() != '/') {
            return std::nullopt;
        }

        auto decoded = UrlDecode(path);
        if (!decoded) {
            return std::nullopt;
        }

        decoded->erase(decoded->begin());

        fs::path relative_path{*decoded};
        if (relative_path.empty()) {
            relative_path = "index.html";
        }

        if (relative_path.is_absolute() || relative_path.has_root_name() || relative_path.has_root_directory()) {
            return std::nullopt;
        }

        relative_path = relative_path.lexically_normal();
        for (const auto& part : relative_path) {
            if (part == "..") {
                return std::nullopt;
            }
        }

        fs::path resolved = (static_root_ / relative_path).lexically_normal();

        boost::system::error_code ec;
        if (fs::is_directory(resolved, ec)) {
            resolved = (resolved / "index.html").lexically_normal();
        }

        return resolved;
    }

    static std::optional<std::string> UrlDecode(std::string_view value) {
        std::string result;
        result.reserve(value.size());

        for (size_t i = 0; i < value.size(); ++i) {
            const char ch = value[i];
            if (ch != '%') {
                result.push_back(ch);
                continue;
            }

            if (i + 2 >= value.size()) {
                return std::nullopt;
            }

            const int hi = HexDigitToInt(value[i + 1]);
            const int lo = HexDigitToInt(value[i + 2]);
            if (hi < 0 || lo < 0) {
                return std::nullopt;
            }

            result.push_back(static_cast<char>(hi * 16 + lo));
            i += 2;
        }

        return result;
    }

    static int HexDigitToInt(char ch) {
        if (ch >= '0' && ch <= '9') {
            return ch - '0';
        }
        if (ch >= 'a' && ch <= 'f') {
            return ch - 'a' + 10;
        }
        if (ch >= 'A' && ch <= 'F') {
            return ch - 'A' + 10;
        }
        return -1;
    }

    static std::string_view GetMimeType(std::string_view extension) {
        std::string lowercase_extension(extension);
        std::transform(lowercase_extension.begin(), lowercase_extension.end(), lowercase_extension.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

        if (lowercase_extension == ".htm" || lowercase_extension == ".html") {
            return "text/html";
        }
        if (lowercase_extension == ".css") {
            return "text/css";
        }
        if (lowercase_extension == ".txt") {
            return "text/plain";
        }
        if (lowercase_extension == ".js") {
            return "text/javascript";
        }
        if (lowercase_extension == ".json") {
            return "application/json";
        }
        if (lowercase_extension == ".xml") {
            return "application/xml";
        }
        if (lowercase_extension == ".png") {
            return "image/png";
        }
        if (lowercase_extension == ".jpg" || lowercase_extension == ".jpe" || lowercase_extension == ".jpeg") {
            return "image/jpeg";
        }
        if (lowercase_extension == ".gif") {
            return "image/gif";
        }
        if (lowercase_extension == ".bmp") {
            return "image/bmp";
        }
        if (lowercase_extension == ".ico") {
            return "image/vnd.microsoft.icon";
        }
        if (lowercase_extension == ".tif" || lowercase_extension == ".tiff") {
            return "image/tiff";
        }
        if (lowercase_extension == ".svg" || lowercase_extension == ".svgz") {
            return "image/svg+xml";
        }
        if (lowercase_extension == ".mp3") {
            return "audio/mpeg";
        }

        return "application/octet-stream";
    }
};

}  // namespace api::static_files
