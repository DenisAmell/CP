#ifndef COLLECTION_H
#define COLLECTION_H

#include "../memory/memory.h"
#include "../collections/work_calendar.h"
#include "../trees/BST/associative_container.h"
#include "../memory/memory_holder.h"
#include "../trees/BST/binary_search_tree.h"
#include "../comparer.h"
#include "../trees/trees_type.h"
#include "trees/BST/binary_search_tree.h"
#include "trees/AVL/avl_tree.h"
#include "trees/RB/red_black_tree.h"
// #include "trees/SPLAY/splay_tree.h"
#include "logger_singleton.h"

class collection : public memory_holder
{
private:
	memory *_allocator;
	associative_container<key *, value *> *_data;
	trees_type _trees_type;

public:
	collection(memory *allocator = nullptr, trees_type trees_type = trees_type::RB) : _allocator(allocator), _trees_type(trees_type)
	{
		switch (_trees_type)
		{
		case trees_type::AVL:
			_data = new avl_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		case trees_type::RB:
			_data = new red_black_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		// case trees_type::SPLAY:
		// 	_data = new splay_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
		// 	break;
		case trees_type::BST:
			_data = new binary_search_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		}
	}

	~collection() { delete _data; }

	collection(collection const &other) : _allocator(other._allocator), _trees_type(other._trees_type)
	{
		switch (_trees_type)
		{
		case trees_type::AVL:
			_data = new avl_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		case trees_type::RB:
			_data = new red_black_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		// case trees_type::SPLAY:
		// 	_data = new splay_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
		// 	break;
		case trees_type::BST:
			_data = new binary_search_tree<key *, value *, key_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		}
	}

	collection &operator=(collection const &other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete this->_data;

		if (this->_allocator != other._allocator)
		{
			delete this->_allocator;
			this->_allocator = other._allocator;
		}
		this->_trees_type = other._trees_type;

		return *this;
	}

	collection(collection &&other) noexcept
	{
		this->_data = other._data;
		this->_allocator = other._allocator;
		this->_trees_type = other._trees_type;

		other._data = nullptr;
		other._allocator = nullptr;
		other._trees_type = trees_type::RB;
	}

	collection &operator=(collection &&other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete this->_data;
		delete this->_allocator;

		this->_data = other._data;
		this->_allocator = other._allocator;
		this->_trees_type = other._trees_type;

		other._data = nullptr;
		other._allocator = nullptr;
		other._trees_type = trees_type::RB;

		return *this;
	}

public:
	void add(key *key, value *value);
	value *get(key *const &key);
	bool find_in(key *key);
	memory *get_memory() const override;
	value remove(key *data_key);
	void update(key *data_key, value *target_value);
	std::vector<value *> get_data_between(key *const &left_key, key *const &right_key);
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
	return _data->find_in(key);
}

memory *collection::get_memory() const
{
	return _allocator;
}

value collection::remove(key *data_key)
{
	auto removed_node = _data->remove_node(data_key);

	value result = *(std::get<1>(removed_node));

	std::get<0>(removed_node)->~key();
	deallocate_with_guard(std::get<0>(removed_node));

	std::get<1>(removed_node)->~value();
	deallocate_with_guard(std::get<1>(removed_node));

	return result;
}

void collection::update(key *data_key, value *target_value)
{
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

	_data->update(data_key, std::move(data_value));
}

std::vector<value *> collection::get_data_between(key *const &left_key, key *const &right_key)
{
	return _data->get_data_between(left_key, right_key);
}

#endif // COLLECTION_H