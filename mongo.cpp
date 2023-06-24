//
// Created by 赵超 on 2023/2/23.
//

#include "mongo.h"

#include "nlohmann/json.hpp"

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/list.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <fmt/format.h>
#include <mongocxx/pool.hpp>

using nlohmann::json;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

namespace {

class Access {
public:
    static Access& instance() {
        static Access instance;
        return instance;
    }

    void configure(std::unique_ptr<mongocxx::instance> instance,
                   std::unique_ptr<mongocxx::pool> pool) {
        _instance = std::move(instance);
        _pool = std::move(pool);
    }

    using connection = mongocxx::pool::entry;
    std::optional<connection> try_get_connection() {
        return _pool->try_acquire();
    }

private:
    Access() = default;

    std::unique_ptr<mongocxx::instance> _instance = nullptr;
    std::unique_ptr<mongocxx::pool> _pool = nullptr;
    std::string_view db_name_;
};

}

auto Mongo::client() {
    // 100ms - 2000ms
    // auto client = ExponentialBackoff<std::runtime_error>(100, 2000).go(std::move(try_get));
    return Access::instance().try_get_connection();
};

void Mongo::init(std::string_view address,
                 uint64_t min_pool_size,
                 uint64_t max_pool_size,
                 uint64_t selection_timeout_ms) {
    // add
    auto uri_str = fmt::format("{}&minPoolSize={}&maxPoolSize={}&serverSelectionTimeoutMS={}",
                                      address, min_pool_size, max_pool_size, selection_timeout_ms);
    auto uri = mongocxx::uri{uri_str};
    auto instance = std::make_unique<mongocxx::instance>();
    Access::instance().configure(std::move(instance),
                                 std::make_unique<mongocxx::pool>(std::move(uri)));
}