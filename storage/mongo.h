//
// Created by 赵超 on 2023/2/23.
//

#ifndef TRY_MONGO_MONGO_H
#define TRY_MONGO_MONGO_H

#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/builder/list.hpp>
#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

class Mongo {
public:
    static Mongo& getInstance();
    Mongo();
    mongocxx::client client_;
};

#endif //TRY_MONGO_MONGO_H
