cmake_minimum_required(VERSION 3.22.1)
project(KURSACH)

set(CMAKE_CXX_STANDARD 20)

#include(FetchContent)

#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
#FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(KURSACH
        src/allocators/boundery_tags/boundery_tags.h
        src/allocators/boundery_tags/boundery_tags.cpp
        src/allocators/buddy_system/buddy_system.h
        src/allocators/buddy_system/buddy_system.cpp
        src/allocators/global_heap/memory_global_heap.cpp
        src/allocators/global_heap/memory_global_heap.h
        src/allocators/memory_list/memory_list.cpp
        src/allocators/memory_list/memory_list.h
        src/allocators/allocator_type.h
        src/classes/pool.h
        src/classes/scheme.h
        src/classes/collection.h
        #src/client/client.cpp
        src/collections/work_calendar.h
        src/commands/command.h
        src/commands/command_add_pool.h
        src/commands/command_add_scheme.h
        src/commands/command_add_collection.h
        src/commands/command_add_data.h
        src/commands/command_get_data.h
        src/commands/command_get_data_between.h
        src/commands/command_remove_data.h
        src/commands/command_remove_collection.h
        src/commands/command_remove_scheme.h
        src/commands/command_remove_pool.h
        src/commands/command_update.h
        src/logger/logger_builder_concrete.cpp
        src/logger/logger_builder_concrete.h
        src/logger/logger_builder.cpp
        src/logger/logger_builder.h
        src/logger/logger_concrete.cpp
        src/logger/logger_concrete.h
        src/logger/logger_holder.cpp
        src/logger/logger_holder.h
        src/logger/logger.cpp
        src/logger/logger.h
        src/memory/memory_holder.cpp
        src/memory/memory_holder.h
        src/memory/memory.h
        src/trees/BST/associative_container.h
        src/trees/BST/binary_search_tree.h
        src/trees/RB/red_black_tree.h
        src/trees/AVL/avl_tree.h
        src/trees/SPLAY/splay_tree.h
        src/trees/trees_type.h
        src/abstract_handler.h
        src/comparer.h
        src/database_singleton.h
        src/logger_singleton.h
        src/pars.h
        src/request_handler_with_command.h
        src/request_handler_with_command_chain.h
        src/main.cpp
        src/flyweight/string_flyweight.h
        src/flyweight/string_flyweight_factory.h
        src/commands/command_restoration.h
        src/commands/command_clean.h)
target_link_libraries(KURSACH)