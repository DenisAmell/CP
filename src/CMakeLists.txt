cmake_minimum_required(VERSION 3.22.1)
project(cp)

set(CMAKE_CXX_STANDARD 20)



include_directories(.)
# find_package(nlohmann_json 3.11.2 REQUIRED)

add_executable(cp
        logger/logger.cpp
        logger/logger.h
        logger/logger_holder.cpp
        logger/logger_holder.h
        logger/logger_builder.cpp
        logger/logger_builder.h
        logger/logger_builder_concrete.cpp
        logger/logger_builder_concrete.h
        logger/logger_concrete.cpp
        logger/logger_concrete.h
        memory/memory_holder.h
        memory/memory_holder.cpp
        memory/memory.h
        memory/memory.cpp
        not_implemented/not_implemented.h
        allocators/list_memory.cpp
        allocators/list_memory.h
        allocators/boundary_tags_allocator.cpp
        allocators/boundary_tags_allocator.h
        allocators/memory_buddy_system.cpp
        allocators/memory_buddy_system.h
        allocators/allocator_type.h
        tree/associative_container.h
        tree/binary_search_tree.h
        tree/red_black_tree.h
        tree/avl_tree.h
        tree/splay_tree.h
        tree/tree_type.h
        commands/command_add_collection.h
        commands/command_add_data.h
        commands/command_add_pool.h
        commands/command_add_scheme.h
        commands/command_get_data_between.h
        commands/command_get_data.h
        commands/command_remove_collection.h
        commands/command_remove_data.h
        commands/command_remove_pool.h
        commands/command_remove_scheme.h
        commands/command_update_data.h
        exception/doesnt_exist.h
        commands/command.h
        comparer/comparers.h
        validation/parse.h
        conteiners/pool.h
        conteiners/scheme.h
        conteiners/collection.h
        singleton/database_singleton.h
        singleton/logger_singleton.h
        request_handler/request_handler_with_command_chain.h
        request_handler/request_handler_with_command.h
        request_handler/abstract_handler.h
        type_data/student_definition.h
        main.cpp)
target_link_libraries(cp)