#include <goblin-engineer/log.hpp>

namespace  goblin_engineer {

    log::log(std::shared_ptr<spdlog::async_logger> logger) : logger_(logger) {}

    auto log::clone() noexcept -> log {
        return logger_;
    }

    auto log::context(std::shared_ptr<spdlog::async_logger> logger) noexcept -> void {
        logger_= logger;
    }

}