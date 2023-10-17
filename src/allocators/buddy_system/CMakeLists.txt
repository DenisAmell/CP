cmake_minimum_required(VERSION 3.22.1)
project(bs)

set(CMAKE_CXX_STANDARD 20)

#include(FetchContent)

#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
#FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(bs
        ../../logger/logger_builder_concrete.cpp
        ../../logger/logger_builder_concrete.h
        ../../logger/logger_builder.cpp
        ../../logger/logger_builder.h
        ../../logger/logger_concrete.cpp
        ../../logger/logger_concrete.h
        ../../logger/logger_holder.cpp
        ../../logger/logger_holder.h
        ../../logger/logger.cpp
        ../../logger/logger.h
        ../../memory/memory.h
        buddy_system.h
        buddy_system.cpp
        main.cpp   )
target_link_libraries(bs)