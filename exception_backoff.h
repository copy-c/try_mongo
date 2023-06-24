//
// Created by 赵超 on 2024/6/2.
//

#ifndef TRY_MONGO_EXCEPTION_BACKOFF_H
#define TRY_MONGO_EXCEPTION_BACKOFF_H

#include <random>
#include <thread>
#include <optional>
#include <iostream>

template <typename HandledExceptionType>
struct ExponentialBackoff {

    size_t min_wait_ms_;
    size_t max_wait_ms_;
    size_t curr_wait_ms_;

    ExponentialBackoff(size_t min_wait_ms, size_t max_wait_ms) :
            min_wait_ms_(min_wait_ms),
            max_wait_ms_(max_wait_ms),
            curr_wait_ms_(min_wait_ms_){}

    void sleep_ms(size_t ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    bool wait()
    {
        thread_local std::uniform_int_distribution<size_t> dist;
        thread_local std::minstd_rand gen(std::random_device{}());
        const size_t wait = dist(gen, decltype(dist)::param_type{0, curr_wait_ms_});
        sleep_ms(wait);
        curr_wait_ms_ = std::min(curr_wait_ms_ * 2, max_wait_ms_);
        return curr_wait_ms_ != max_wait_ms_;
    }

    template <typename Callable>
    auto go(Callable&& callable) {
        //Throw exception with error msg, as user may turn off warn or in juypter notebook
        return go(std::forward<Callable>(callable),
                  [](const HandledExceptionType &e){
                      std::cout << "Exhausted retry attempts, likely due to errors given by the storage" << e.what();
                  });
    }

    template<typename Callable, typename FailurePolicy>
    auto go(Callable&& c, FailurePolicy&& failure_policy) {
        std::optional<HandledExceptionType> last_exception; //HandledExceptionType may have the default ctor deleted
        do {
            try {
                return c();
            }
            catch (HandledExceptionType &e) {
                std::cout << "Exhausted retry attempts, likely due to errors given by the storage" << e.what();
                last_exception = e;
            }
        } while(wait());

        failure_policy(last_exception.value());
    }
};

#endif //TRY_MONGO_EXCEPTION_BACKOFF_H
