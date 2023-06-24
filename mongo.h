//
// Created by 赵超 on 2023/2/23.
//

#ifndef TRY_MONGO_MONGO_H
#define TRY_MONGO_MONGO_H

#include <string_view>

class Mongo {
public:
    static void init(std::string_view address,
                     uint64_t min_pool_size,
                     uint64_t max_pool_size,
                     uint64_t selection_timeout_ms);

    static auto client();
};

#endif //TRY_MONGO_MONGO_H
