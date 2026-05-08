#include "connection_pool.h"

#include <algorithm>
#include <utility>

namespace postgres {

ConnectionPool::ConnectionPtr::ConnectionPtr(ConnectionPool& pool,
                                             std::unique_ptr<pqxx::connection> connection) noexcept
    : pool_{&pool}, connection_{std::move(connection)} {}

ConnectionPool::ConnectionPtr::ConnectionPtr(ConnectionPtr&& other) noexcept {
    *this = std::move(other);
}

ConnectionPool::ConnectionPtr& ConnectionPool::ConnectionPtr::operator=(ConnectionPtr&& other) noexcept {
    if (this != &other) {
        Reset();
        pool_ = other.pool_;
        connection_ = std::move(other.connection_);
        other.pool_ = nullptr;
    }
    return *this;
}

ConnectionPool::ConnectionPtr::~ConnectionPtr() {
    Reset();
}

pqxx::connection& ConnectionPool::ConnectionPtr::operator*() const noexcept {
    return *connection_;
}

pqxx::connection* ConnectionPool::ConnectionPtr::operator->() const noexcept {
    return connection_.get();
}

ConnectionPool::ConnectionPtr::operator bool() const noexcept {
    return connection_ != nullptr;
}

void ConnectionPool::ConnectionPtr::Reset() noexcept {
    if (pool_ && connection_) {
        pool_->ReturnConnection(std::move(connection_));
    }
    pool_ = nullptr;
}

ConnectionPool::ConnectionPool(std::string db_url, std::size_t pool_size) {
    pool_size = std::max<std::size_t>(1, pool_size);
    for (std::size_t i = 0; i < pool_size; ++i) {
        connections_.push(std::make_unique<pqxx::connection>(db_url));
    }
}

ConnectionPool::ConnectionPtr ConnectionPool::GetConnection() {
    std::unique_lock lock{mutex_};
    condition_.wait(lock, [this] { return !connections_.empty(); });

    auto connection = std::move(connections_.front());
    connections_.pop();
    return ConnectionPtr{*this, std::move(connection)};
}

void ConnectionPool::ReturnConnection(std::unique_ptr<pqxx::connection> connection) noexcept {
    {
        std::lock_guard lock{mutex_};
        connections_.push(std::move(connection));
    }
    condition_.notify_one();
}

}  // namespace postgres
