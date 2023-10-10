cmake_minimum_required(VERSION 3.21.1)
project(cp)

set(CMAKE_CXX_STANDARD 20)



include_directories(.)
# find_package(nlohmann_json 3.11.2 REQUIRED)

add_executable(cp
        src/logger/logger.cpp
        src/logger/logger.h
        src/logger/logger_holder.cpp
        src/logger/logger_holder.h
        src/logger/logger_builder.cpp
        src/logger/logger_builder.h
        src/logger/logger_builder_concrete.cpp
        src/logger/logger_builder_concrete.h
        src/logger/logger_concrete.cpp
        src/logger/logger_concrete.h
        src/memory/memory_holder.h
        src/memory/memory_holder.cpp
        src/memory/memory.h
        src/memory/memory.cpp
        src/not_implemented/not_implemented.h
        src/allocators/list_memory.cpp
        src/allocators/list_memory.h
        src/allocators/boundary_tags_allocator.cpp
        src/allocators/boundary_tags_allocator.h
        src/allocators/memory_buddy_system.cpp
        src/allocators/memory_buddy_system.h
        src/allocators/allocator_type.h
        src/tree/associative_container.h
        src/tree/binary_search_tree.h
        src/tree/red_black_tree.h
        src/tree/avl_tree.h
        src/tree/splay_tree.h
        src/tree/tree_type.h
        src/commands/command_add_collection.h
        src/commands/command_add_data.h
        src/commands/command_add_pool.h
        src/commands/command_add_scheme.h
        src/commands/command_get_data_between.h
        src/commands/command_get_data.h
        src/commands/command_remove_collection.h
        src/commands/command_remove_data.h
        src/commands/command_remove_pool.h
        src/commands/command_remove_scheme.h
        src/commands/command_update_data.h
        src/exception/doesnt_exist.h
        src/commands/command.h
        src/comparer/comparers.h
        src/validation/parse.h
        src/conteiners/pool.h
        src/conteiners/scheme.h
        src/conteiners/collection.h
        src/singleton/database_singleton.h
        src/singleton/logger_singleton.h
        src/request_handler/request_handler_with_command_chain.h
        src/request_handler/request_handler_with_command.h
        src/request_handler/abstract_handler.h
        src/type_data/student_definition.h
        src/main.cpp)
target_link_libraries(cp)