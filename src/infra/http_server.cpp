#include "http_server.h"

#include "logger.h"

#include <boost/asio/dispatch.hpp>

namespace http_server {

void ReportError(beast::error_code ec, std::string_view what) {
    infra::log::Error("http_io_error", {
                                           {"where", std::string(what)},
                                           {"message", ec.message()},
                                       });
}

void SessionBase::Run() {
    net::dispatch(stream_.get_executor(), beast::bind_front_handler(&SessionBase::Read, GetSharedThis()));
}

void SessionBase::Read() {
    using namespace std::literals;
    request_ = {};
    stream_.expires_after(30s);
    http::async_read(stream_, buffer_, request_, beast::bind_front_handler(&SessionBase::OnRead, GetSharedThis()));
}

void SessionBase::OnRead(beast::error_code ec, [[maybe_unused]] std::size_t bytes_read) {
    using namespace std::literals;
    if (ec == http::error::end_of_stream) {
        return Close();
    }
    if (ec) {
        return ReportError(ec, "read"sv);
    }
    HandleRequest(std::move(request_));
}

void SessionBase::OnWrite(beast::error_code ec, [[maybe_unused]] std::size_t bytes_written, bool close) {
    if (ec) {
        return ReportError(ec, "write"sv);
    }

    if (close) {
        return Close();
    }

    Read();
}

void SessionBase::Close() {
    try {
        stream_.socket().shutdown(tcp::socket::shutdown_send);
    } catch (const std::exception& e) {
        infra::log::Error("http_shutdown_failed", {{"message", e.what()}});
    }
}

}  // namespace http_server
