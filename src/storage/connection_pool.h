#pragma once

#include <condition_variable>
#include <cstddef>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include <pqxx/pqxx>

namespace postgres {

class ConnectionPool {
   public:
    class ConnectionPtr {
       public:
        ConnectionPtr() = default;
        ConnectionPtr(const ConnectionPtr&) = delete;
        ConnectionPtr& operator=(const ConnectionPtr&) = delete;
        ConnectionPtr(ConnectionPtr&& other) noexcept;
        ConnectionPtr& operator=(ConnectionPtr&& other) noexcept;
        ~ConnectionPtr();

        pqxx::connection& operator*() const noexcept;
        pqxx::connection* operator->() const noexcept;
        explicit operator bool() const noexcept;

       private:
        friend class ConnectionPool;

        ConnectionPtr(ConnectionPool& pool, std::unique_ptr<pqxx::connection> connection) noexcept;

        void Reset() noexcept;

        ConnectionPool* pool_ = nullptr;
        std::unique_ptr<pqxx::connection> connection_;
    };

    explicit ConnectionPool(std::string db_url, std::size_t pool_size = 4);

    ConnectionPool(const ConnectionPool&) = delete;
    ConnectionPool& operator=(const ConnectionPool&) = delete;

    ConnectionPtr GetConnection();

   private:
    void ReturnConnection(std::unique_ptr<pqxx::connection> connection) noexcept;

    std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<std::unique_ptr<pqxx::connection>> connections_;
};

}  // namespace postgres
