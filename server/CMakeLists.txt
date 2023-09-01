cmake_minimum_required(VERSION 3.22.1)
project(SERVER)

set(CMAKE_CXX_STANDARD 20)

#include(FetchContent)

#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
#FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(SERVER
        ../allocators/boundery_tags/boundery_tags.h
        ../allocators/boundery_tags/boundery_tags.cpp
        ../allocators/global_heap/memory_global_heap.cpp
        ../allocators/global_heap/memory_global_heap.h
        ../allocators/memory_list/memory_list.cpp
        ../allocators/memory_list/memory_list.h
        ../allocators/allocator_type.h
        ../classes/pool.h
        ../classes/scheme.h
        ../classes/collection.h
        ../collections/work_calendar.h
        ../commands/command.h
        ../commands/command_add_pool.h
        ../commands/command_add_scheme.h
        ../commands/command_add_collection.h
        ../commands/command_add_data.h
        ../commands/command_get_data.h
        ../commands/command_get_data_between.h
        ../commands/command_remove_data.h
        ../commands/command_remove_collection.h
        ../commands/command_remove_scheme.h
        ../commands/command_remove_pool.h
        ../commands/command_update.h
        ../logger/logger_builder_concrete.cpp
        ../logger/logger_builder_concrete.h
        ../logger/logger_builder.cpp
        ../logger/logger_builder.h
        ../logger/logger_concrete.cpp
        ../logger/logger_concrete.h
        ../logger/logger_holder.cpp
        ../logger/logger_holder.h
        ../logger/logger.cpp
        ../logger/logger.h
        ../memory/memory_holder.cpp
        ../memory/memory_holder.h
        ../memory/memory.h
        ../trees/BST/associative_container.h
        ../trees/BST/binary_search_tree.h 
        ../trees/RB/red_black_tree.h 
        ../trees/AVL/avl_tree.h
        ../trees/SPLAY/splay_tree.h
        ../trees/trees_type.h
        ../abstract_handler.h 
        ../comparer.h
        ../database_singleton.h
        ../logger_singleton.h
        ../pars.h     
        ../request_handler_with_command.h
        ../request_handler_with_command_chain.h
        server.cpp   )
target_link_libraries(SERVER)