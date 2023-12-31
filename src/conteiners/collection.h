#ifndef FUNDAMENTAL_ALGO_COLLECTION_H
#define FUNDAMENTAL_ALGO_COLLECTION_H

#include "../type_data/student_definition.h"
#include <tuple>
#include <iostream>
#include "../memory/memory_holder.h"
#include "../tree/tree_type.h"
#include "../tree/avl_tree.h"
#include "../tree/binary_search_tree.h"
//#include "tree/splay_tree.h"
#include "../tree/red_black_tree.h"
//#include "tree/associative_container.h"
#include "../comparer/comparers.h"
#include "../flyweight/string_flyweight_factory.h"

class collection final : protected memory_holder
{
private:
	memory* _allocator;
	associative_container<key*, values*>* _data;
	tree_type _tree_type;

public:
	collection(memory* allocator = nullptr, tree_type tree_type = tree_type::RED_BLACK_TREE) : _allocator(allocator), _tree_type(tree_type)
	{
		switch (tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			_data = new binary_search_tree<key*, values*, key_comparer>();
			break;
		case tree_type::RED_BLACK_TREE:
			_data = new red_black_tree<key*, values*, key_comparer>();
			break;
		case tree_type::AVL_TREE:
			_data = new avl_tree<key*, values*, key_comparer>();
			break;
			/*case tree_type::SPALY_TREE:
				_data = new splay_tree<key*, values*, key_comparer>();
				break;*/
		}
	}

	~collection()
	{
		delete _data;
	}

public:
	void add(
		unsigned int id_session,
		unsigned int id_student,
		reporting_format format,
		const std::string& subject,
		const std::string& surname,
		const std::string& name,
		const std::string& patronymic,
		const std::string& date,
		const std::string& time,
		unsigned int mark)
	{
		key* data_key = reinterpret_cast<key*>(allocate_with_guard(sizeof(key)));
		new (data_key) key;

		data_key->id_session = id_session;
		data_key->id_student = id_student;
		data_key->format = format;
		data_key->subject = string_flyweight_factory::get_instance().get_string_flyweight(subject)->get_value();

		values* data_value = reinterpret_cast<values*>(allocate_with_guard(sizeof(values)));
		new (data_value) values;

		data_value->student_surname = string_flyweight_factory::get_instance().get_string_flyweight(surname)->get_value();
		data_value->student_name = string_flyweight_factory::get_instance().get_string_flyweight(name)->get_value();
		data_value->student_patronymic = string_flyweight_factory::get_instance().get_string_flyweight(patronymic)->get_value();
		data_value->event_date = string_flyweight_factory::get_instance().get_string_flyweight(date)->get_value();
		data_value->event_time = string_flyweight_factory::get_instance().get_string_flyweight(time)->get_value();
		data_value->mark = mark;

		_data->insert(data_key, std::move(data_value));
	}

	bool find_in(key* const& data_key) const
	{
		return _data->find_in(data_key);
	}

	values remove(key* data_key)
	{
		auto returned_node = _data->remove_node(data_key);

		values result = *(std::get<1>(returned_node));

		std::get<0>(returned_node)->~key();
		deallocate_with_guard(std::get<0>(returned_node));

		std::get<1>(returned_node)->~values();
		deallocate_with_guard(std::get<1>(returned_node));

		return result;
	}

	values* get(key* const& data_key)
	{
		return _data->get_value(data_key);
	}

	std::vector<values*> get_between_keys(key* const& min_key, key* const& max_key)
	{
		return _data->find_in_range(min_key, max_key);
	}

	void update(
		key* const& data_key,
		const std::string& surname,
		const std::string& name,
		const std::string& patronymic,
		const std::string& date,
		const std::string& time,
		unsigned int mark)
	{
		values* data_value = reinterpret_cast<values*>(allocate_with_guard(sizeof(values)));
		new (data_value) values;

        data_value->student_surname = string_flyweight_factory::get_instance().get_string_flyweight(surname)->get_value();
        data_value->student_name = string_flyweight_factory::get_instance().get_string_flyweight(name)->get_value();
        data_value->student_patronymic = string_flyweight_factory::get_instance().get_string_flyweight(patronymic)->get_value();
        data_value->event_date = string_flyweight_factory::get_instance().get_string_flyweight(date)->get_value();
        data_value->event_time = string_flyweight_factory::get_instance().get_string_flyweight(time)->get_value();
		data_value->mark = mark;

		_data->update(data_key, std::move(data_value));
	}

public:
	collection(collection const& other) : _allocator(other._allocator), _tree_type(other._tree_type)
	{

		switch (_tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			_data = new binary_search_tree<key*, values*, key_comparer>(*reinterpret_cast<binary_search_tree<key*, values*, key_comparer>*>(other._data));
			break;
		case tree_type::RED_BLACK_TREE:
			_data = new red_black_tree<key*, values*, key_comparer>(*reinterpret_cast<red_black_tree<key*, values*, key_comparer>*>(other._data));
			break;
		case tree_type::AVL_TREE:
			_data = new avl_tree<key*, values*, key_comparer>(*reinterpret_cast<avl_tree<key*, values*, key_comparer>*>(other._data));
			break;
			/*case tree_type::SPALY_TREE:
				_data = new splay_tree<key*, values*, key_comparer>(*reinterpret_cast<splay_tree<key*, values*, key_comparer>*>(other._data));
				break;*/
		}
	}

	collection& operator=(collection const& other)
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

		this->_tree_type = other._tree_type;

		return *this;
	}

	collection(collection&& other) noexcept
	{
		this->_data = other._data;
		this->_allocator = other._allocator;
		this->_tree_type = other._tree_type;

		other._data = nullptr;
		other._allocator = nullptr;
		other._tree_type = tree_type::RED_BLACK_TREE;
	}

	collection& operator=(collection&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}

		delete this->_data;
		delete this->_allocator;

		this->_data = other._data;
		this->_allocator = other._allocator;
		this->_tree_type = other._tree_type;

		other._data = nullptr;
		other._allocator = nullptr;
		other._tree_type = tree_type::RED_BLACK_TREE;


		return *this;
	}

private:
	memory* get_memory() const override
	{
		return _allocator;
	}
};
#endif // FUNDAMENTAL_ALGO_COLLECTION_H