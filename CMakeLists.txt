cmake_minimum_required(VERSION 3.22.1)
project(KURSACH)

set(CMAKE_CXX_STANDARD 17)



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
        comparer.h
        logger_singleton.h     
        main.cpp)
target_link_libraries(KURSACH)