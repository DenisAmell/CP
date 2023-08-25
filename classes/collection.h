#ifndef collection_H
#define collection_H

#include "../memory/memory.h"
#include "../collections/work_calendar.h"
#include "../trees/BST/associative_container.h"
#include "../memory/memory_holder.h"
#include "../trees/BST/binary_search_tree.h"
#include "../comparer.h"

class collection : public memory_holder
{
private:
    memory *_allocator;
    associative_container<key *, value *> *_data;

public:
    collection(memory *allocator = nullptr) : _data(new binary_search_tree<key *, value *, key_comparer>(allocator, nullptr)), _allocator(allocator){};
    ~collection(){};

    void add(key *key, value *value);
    value *get(key *const &key);
    bool find_in(key *key);
    memory *get_memory() const override;
};

void collection::add(key *target_key, value *target_value)
{
    key *data_key = reinterpret_cast<key *>(allocate_with_guard(sizeof(key)));
    new (data_key) key;

    data_key->_id = target_key->_id;

    value *data_value = reinterpret_cast<value *>(allocate_with_guard(sizeof(value)));
    new (data_value) value;

    data_value->_type_of_meeting = target_value->_type_of_meeting;
    data_value->_format = target_value->_format;
    data_value->_meeting_description = target_value->_meeting_description;
    data_value->_link_to_meeting = target_value->_link_to_meeting;
    data_value->_first_name = target_value->_first_name;
    data_value->_last_name = target_value->_last_name;
    data_value->_middle_name = target_value->_middle_name;
    data_value->_data = target_value->_data;
    data_value->_time = target_value->_time;
    data_value->_duration_of_meeting = target_value->_duration_of_meeting;
    data_value->_list_invitees = target_value->_list_invitees;

    _data->insert(data_key, std::move(data_value));
}

value *collection::get(key *const &key)
{
    return _data->get_value(key);
}

bool collection::find_in(key *key)
{
    return true;
}

memory *collection::get_memory() const
{
    return _allocator;
}

#endif // collection_H