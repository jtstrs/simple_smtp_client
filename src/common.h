#ifndef COMMON_H
#define COMMON_H

#include "logger_wrapper.h"
#include <cstdint>

constexpr int32_t INPUT_BUFFER_SIZE = 2048;

#define CHECK_NULL(ptr, name)                        \
    do {                                             \
        if (!ptr) {                                  \
            LOG_FMT_MESSAGE("%s ptr is null", name); \
        }                                            \
    } while (0);

#endif