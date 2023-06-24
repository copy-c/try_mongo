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

using nlohmann::json;
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

Mongo::Mongo() {
    try {
        // The mongocxx::instance constructor and destructor initialize and shut down the driver,
        // respectively. Therefore, a mongocxx::instance must be created before using the driver and
        // must remain alive for as long as the driver is in use.
        const auto uri = mongocxx::uri{
                "mongodb+srv://copy:muqurenxuexi@cluster0.s5iqjku.mongodb.net/?retryWrites=true&w=majority"};
        // Set the version of the Stable API on the client.
        mongocxx::options::client client_options;
        const auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
        client_options.server_api_opts(api);
        // Setup the connection and get a handle on the "admin" database.
        client_ = mongocxx::client{uri, client_options};
    } catch (const std::exception& e)
    {
        // Handle errors
        std::cout<< "Exception: " << e.what() << std::endl;
    }
}

Mongo& getInstance() {
    // 在第一次调用时创建实例
    static Mongo instance;
    return instance;
}
