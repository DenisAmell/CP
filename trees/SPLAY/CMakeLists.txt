cmake_minimum_required(VERSION 3.22.1)
project(SPLAY)

set(CMAKE_CXX_STANDARD 20)

#include(FetchContent)

#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
#FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(SPLAY
        ../../allocators/global_heap/memory_global_heap.cpp
        ../../allocators/global_heap/memory_global_heap.h
        ../../allocators/memory_list/memory_list.cpp
        ../../allocators/memory_list/memory_list.h
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
        ../../memory/memory_holder.cpp
        ../../memory/memory_holder.h
        ../../memory/memory.h
        ../BST/associative_container.h
        ../BST/binary_search_tree.h
        ../../collections/work_calendar.h
        splay_tree.h
        main.cpp)
target_link_libraries(SPLAY)