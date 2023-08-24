#ifndef ALLOCATOR_TYPE_H
#define ALLOCATOR_TYPE_H

enum class allocator_type
{
    GLOBAL_HEAP,
    MEMORY_LIST,
    BUDDIES_SYSTEM,
    BORDER_DESCRIPTORS
    // TODO: доделать другие аллокаторы
};

#endif // ALLOCATOR_TYPE_H