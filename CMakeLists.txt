cmake_minimum_required(VERSION 3.22.1)
project(KURSACH)

set(CMAKE_CXX_STANDARD 20)

#include(FetchContent)

#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
#FetchContent_MakeAvailable(json)

include_directories(.)

add_executable(KURSACH
        allocators/global_heap/memory_global_heap.cpp
        allocators/global_heap/memory_global_heap.h
        allocators/memory_list/memory_list.cpp
        allocators/memory_list/memory_list.h
        database_singleton.h
        classes/pool.h
        classes/scheme.h
        classes/collection.h
        collections/work_calendar.h
        commands/command.h
        commands/command_add_pool.h
        commands/command_add_scheme.h
        commands/command_add_collection.h
        commands/command_add_data.h
        commands/command_get_data.h
        commands/command_get_data_between.h
        commands/command_remove_data.h
        commands/command_remove_collection.h
        commands/command_remove_scheme.h
        commands/command_remove_pool.h
        commands/command_update.h
        logger/logger_builder_concrete.cpp
        logger/logger_builder_concrete.h
        logger/logger_builder.cpp
        logger/logger_builder.h
        logger/logger_concrete.cpp
        logger/logger_concrete.h
        logger/logger_holder.cpp
        logger/logger_holder.h
        logger/logger.cpp
        logger/logger.h
        memory/memory_holder.cpp
        memory/memory_holder.h
        memory/memory.h
        trees/BST/associative_container.h
        trees/BST/binary_search_tree.h 
        trees/RB/red_black_tree.h 
        trees/AVL/avl_tree.h
        trees/SPLAY/splay_tree.h
        trees/trees_type.h
        abstract_handler.h 
        comparer.h
        logger_singleton.h
        pars.h     
        request_handler_with_command.h
        request_handler_with_command_chain.h
        main.cpp   "allocators (2)/allocator_type.h" "allocators (2)/buddy_system.h" "allocators (2)/global_heap/memory_global_heap.cpp" "allocators (2)/global_heap/memory_global_heap.h" "allocators (2)/memory_list/memory_list.cpp" "allocators (2)/memory_list/memory_list.h" "build (2)/CMakeFiles/3.27.3/CompilerIdC/CMakeCCompilerId.c" "build (2)/CMakeFiles/3.27.3/CompilerIdCXX/CMakeCXXCompilerId.cpp" "classes (2)/collection.h" "classes (2)/pool.h" "classes (2)/scheme.h" "CMakeFiles (2)/3.22.1/CompilerIdC/CMakeCCompilerId.c" "CMakeFiles (2)/3.22.1/CompilerIdCXX/CMakeCXXCompilerId.cpp" "CMakeFiles (2)/3.27.3/CompilerIdC/CMakeCCompilerId.c" "collections (2)/work_calendar.h" "commands (2)/command.h" "commands (2)/command_add_collection.h" "commands (2)/command_add_data.h" "commands (2)/command_add_pool.h" "commands (2)/command_add_scheme.h" "commands (2)/command_get_data.h" "commands (2)/command_get_data_between.h" "commands (2)/command_remove_collection.h" "commands (2)/command_remove_data.h" "commands (2)/command_remove_pool.h" "commands (2)/command_remove_scheme.h" "commands (2)/command_update.h" "logger (2)/logger.cpp" "logger (2)/logger.h" "logger (2)/logger_builder.cpp" "logger (2)/logger_builder.h" "logger (2)/logger_builder_concrete.cpp" "logger (2)/logger_builder_concrete.h" "logger (2)/logger_concrete.cpp" "logger (2)/logger_concrete.h" "logger (2)/logger_holder.cpp" "logger (2)/logger_holder.h" "logger (2)/main.cpp" "memory (2)/memory.h" "memory (2)/memory_holder.cpp" "memory (2)/memory_holder.h" "out (2)/build/x64-Debug/CMakeFiles/3.26.0-msvc3/CompilerIdC/CMakeCCompilerId.c" "out (2)/build/x64-Debug/CMakeFiles/3.26.0-msvc3/CompilerIdCXX/CMakeCXXCompilerId.cpp" "out (2)/build/x64-Debug/CMakeFiles/ShowIncludes/foo.h" "out (2)/build/x64-Debug/CMakeFiles/ShowIncludes/main.c" "trees (2)/trees_type.h" "trees (2)/AVL/avl_tree.h" "trees (2)/AVL/main.cpp" "trees (2)/AVL/build/CMakeFiles/3.27.3/CompilerIdC/CMakeCCompilerId.c" "trees (2)/AVL/build/CMakeFiles/3.27.3/CompilerIdCXX/CMakeCXXCompilerId.cpp" "trees (2)/BST/associative_container.h" "trees (2)/BST/binary_search_tree.h" "trees (2)/RB/main.cpp" "trees (2)/RB/red_black_tree.h" "trees (2)/RB/build/CMakeFiles/3.27.3/CompilerIdC/CMakeCCompilerId.c" "trees (2)/RB/build/CMakeFiles/3.27.3/CompilerIdCXX/CMakeCXXCompilerId.cpp" "trees (2)/SPLAY/main.cpp" "trees (2)/SPLAY/splay_tree.h" "trees (2)/SPLAY/build/CMakeFiles/3.27.3/CompilerIdC/CMakeCCompilerId.c" "trees (2)/SPLAY/build/CMakeFiles/3.27.3/CompilerIdCXX/CMakeCXXCompilerId.cpp"    )
target_link_libraries(KURSACH)