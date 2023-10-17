#ifndef DATABASE_SINGLETON_H
#define DATABASE_SINGLETON_H

#include "memory/memory.h"
#include "memory/memory_holder.h"
#include "collections/work_calendar.h"
#include "classes/pool.h"
#include "trees/BST/associative_container.h"
#include "trees/BST/binary_search_tree.h"
#include "trees/AVL/avl_tree.h"
#include "trees/RB/red_black_tree.h"
#include "trees/SPLAY/splay_tree.h"
#include "trees/trees_type.h"
#include "comparer.h"
#include "allocators/allocator_type.h"
#include "allocators/global_heap/memory_global_heap.h"
#include "allocators/memory_list/memory_list.h"
#include "allocators/boundery_tags/boundery_tags.h"
#include "allocators/buddy_system/buddy_system.h"
#include "logger_singleton.h"
#include "logger/logger.h"
#include "request_handler_with_command_chain.h"
#include <string>
#include <iostream>

class database_singleton
{
public:
	static database_singleton* get_instance();
	void add_pool(std::string const& name_pool, allocator_type allocator_type, size_t allocator_size, memory::allocate_mode mode, trees_type _trees_type);
	void add_scheme(std::string const& name_pool, std::string const& name_scheme, trees_type _trees_type);
	void add_collection(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, trees_type _trees_type);
	void add_data(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key, value* data_value);
	void get_data(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key);
	void get_data_between(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* left_key, key* right_key);
	void update(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key, value* data_value);
	void remove_pool(std::string const& name_pool);
	void remove_scheme(std::string const& name_pool, std::string const& name_scheme);
	void remove_collection(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection);
	void remove_data(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key);

public:
	database_singleton();
	~database_singleton()
	{
		delete _database;
	};

	database_singleton(database_singleton const&) = delete;
	database_singleton(database_singleton&&) = delete;
	database_singleton& operator=(database_singleton const&) = delete;
	database_singleton& operator=(database_singleton&&) = delete;

private:
	static database_singleton* _instance;
	associative_container<std::string, pool>* _database;
};

database_singleton* database_singleton::_instance = nullptr;

database_singleton* database_singleton::get_instance()
{
	if (_instance == nullptr)
		_instance = new database_singleton();

	return _instance;
}

database_singleton::database_singleton()
{
	_database = new red_black_tree<std::string, pool, string_comparer>();
	//_database = new binary_search_tree<std::string, pool, string_comparer>();
	logger_singleton::get_instance()->get_logger()->log("Database constructor", logger::severity::trace);

	_instance = this;
}

void database_singleton::add_pool(std::string const& name_pool, allocator_type allocator_type, size_t allocator_size, memory::allocate_mode mode, trees_type _trees_type)
{
	try
	{
		memory* allocator = nullptr;

		switch (allocator_type)
		{
		case allocator_type::GLOBAL_HEAP:
			allocator = new memory_global_heap(logger_singleton::get_instance()->get_logger());
			break;
		case allocator_type::MEMORY_LIST:
			allocator = new memory_list(nullptr, logger_singleton::get_instance()->get_logger(), allocator_size, mode);
			break;
		case allocator_type::BORDER_DESCRIPTORS:
			allocator = new boundery_tags(logger_singleton::get_instance()->get_logger(), nullptr, allocator_size, mode);
			break;
		case allocator_type::BUDDIES_SYSTEM:
			allocator = new buddy_system(logger_singleton::get_instance()->get_logger(), nullptr, allocator_size, mode);
			break;
		}

		_database->insert(name_pool, std::move(pool(allocator, _trees_type)));

		std::cout << "[DATABASE] Add pool with name '" << name_pool << "' added to database" << std::endl;
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::add_scheme(std::string const& name_pool, std::string const& name_scheme, trees_type _tree_type)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			reinterpret_cast<pool&>(_database->find(name_pool)).add(name_scheme, std::move(scheme(_tree_type)));
			std::cout << "[DATABASE] Scheme with name '" << name_scheme << "' added to pool: " << name_pool << std::endl;
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::add_collection(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, trees_type _trees_type)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			pool& current_pool = const_cast<pool&>(_database->find(name_pool));

			memory* allocator = current_pool.get_allocator();

			if (current_pool.find_to_string(name_scheme))
			{
				scheme& current_scheme = const_cast<scheme&>(current_pool.find(name_scheme));

				current_scheme.add(name_collection, std::move(collection(allocator, _trees_type)));
				std::cout << "[DATABASE] Collection with name '" << name_collection << "'" << "added to: " << name_scheme << "->" << name_pool << std::endl;
			}
			else
			{
				std::cout << "[FAIL] Scheme with name '" << name_scheme << "' not found" << std::endl;
			}
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::add_data(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key, value* data_value)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			pool& current_pool = const_cast<pool&>(_database->find(name_pool));

			memory* allocator = current_pool.get_allocator();

			if (current_pool.find_to_string(name_scheme))
			{
				scheme& current_scheme = const_cast<scheme&>(current_pool.find(name_scheme));

				if (current_scheme.find_to_string(name_collection))
				{
					collection& current_collection = const_cast<collection&>(current_scheme.find(name_collection));

					current_collection.add(data_key, data_value);
				}
				else
				{
					std::cout << "[FAIL] Collection with name '" << name_collection << "' not found" << std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Scheme with name '" << name_scheme << "' not found" << std::endl;
			}
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::get_data(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			pool& current_pool = const_cast<pool&>(_database->find(name_pool));

			memory* allocator = current_pool.get_allocator();

			if (current_pool.find_to_string(name_scheme))
			{
				scheme& current_scheme = const_cast<scheme&>(current_pool.find(name_scheme));

				if (current_scheme.find_to_string(name_collection))
				{
					collection& current_collection = const_cast<collection&>(current_scheme.find(name_collection));

					if (current_collection.find_in(data_key))
					{
						value* data = current_collection.get(data_key);
						std::cout << data->_meeting_description << std::endl;
						std::cout << data->_link_to_meeting << std::endl;
						std::cout << data->_first_name << std::endl;
						std::cout << data->_last_name << std::endl;
						std::cout << data->_middle_name << std::endl;
						std::cout << data->_data << std::endl;
						std::cout << data->_time << std::endl;
						std::cout << data->_duration_of_meeting << std::endl;
						std::cout << data->_list_invitees << std::endl;
						std::cout << std::endl;
					}
					else
					{
						std::cout << "[FAIL] Key with name '" << data_key << "' not found" << std::endl;
					}
				}
				else
				{
					std::cout << "[FAIL] Collection with name '" << name_collection << "' not found" << std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Scheme with name '" << name_scheme << "' not found" << std::endl;
			}
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::get_data_between(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* left_key, key* right_key)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			pool& current_pool = const_cast<pool&>(_database->find(name_pool));

			memory* allocator = current_pool.get_allocator();

			if (current_pool.find_to_string(name_scheme))
			{
				scheme& current_scheme = const_cast<scheme&>(current_pool.find(name_scheme));

				if (current_scheme.find_to_string(name_collection))
				{
					collection& current_collection = const_cast<collection&>(current_scheme.find(name_collection));

					std::vector<value*> data = current_collection.get_data_between(left_key, right_key);

					int index = 1;

					for (auto const& data_value : data)
					{
						std::cout << index << ':' << std::endl;
						std::cout << data_value->_meeting_description << std::endl;
						std::cout << data_value->_link_to_meeting << std::endl;
						std::cout << data_value->_first_name << std::endl;
						std::cout << data_value->_last_name << std::endl;
						std::cout << data_value->_middle_name << std::endl;
						std::cout << data_value->_data << std::endl;
						std::cout << data_value->_time << std::endl;
						std::cout << data_value->_duration_of_meeting << std::endl;
						std::cout << data_value->_list_invitees << std::endl;
						std::cout << std::endl;
						index++;
					}
				}
				else
				{
					std::cout << "[FAIL] Collection with name '" << name_collection << "' not found" << std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Scheme with name '" << name_scheme << "' not found" << std::endl;
			}
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::update(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key, value* data_value)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			pool& current_pool = const_cast<pool&>(_database->find(name_pool));

			memory* allocator = current_pool.get_allocator();

			if (current_pool.find_to_string(name_scheme))
			{
				scheme& current_scheme = const_cast<scheme&>(current_pool.find(name_scheme));

				if (current_scheme.find_to_string(name_collection))
				{
					collection& current_collection = const_cast<collection&>(current_scheme.find(name_collection));

					current_collection.update(data_key, data_value);
				}
				else
				{
					std::cout << "[FAIL] Collection with name '" << name_collection << "' not found" << std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Scheme with name '" << name_scheme << "' not found" << std::endl;
			}
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::remove_pool(std::string const& name_pool)
{
	_database->remove(name_pool);
}

void database_singleton::remove_scheme(std::string const& name_pool, std::string const& name_scheme)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			reinterpret_cast<pool&>(_database->find(name_pool)).remove(name_scheme);
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::remove_collection(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			pool& current_pool = const_cast<pool&>(_database->find(name_pool));

			if (current_pool.find_to_string(name_scheme))
			{
				scheme& current_scheme = const_cast<scheme&>(current_pool.find(name_scheme));

				current_scheme.remove(name_collection);
			}
			else
			{
				std::cout << "[FAIL] Scheme with name '" << name_scheme << "' not found" << std::endl;
			}
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

void database_singleton::remove_data(std::string const& name_pool, std::string const& name_scheme, std::string const& name_collection, key* data_key)
{
	try
	{
		if (_database->find_to_string(name_pool))
		{
			pool& current_pool = const_cast<pool&>(_database->find(name_pool));

			memory* allocator = current_pool.get_allocator();

			if (current_pool.find_to_string(name_scheme))
			{
				scheme& current_scheme = const_cast<scheme&>(current_pool.find(name_scheme));

				if (current_scheme.find_to_string(name_collection))
				{
					collection& current_collection = const_cast<collection&>(current_scheme.find(name_collection));

					current_collection.remove(data_key);
				}
				else
				{
					std::cout << "[FAIL] Collection with name '" << name_collection << "' not found" << std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Scheme with name '" << name_scheme << "' not found" << std::endl;
			}
		}
		else
		{
			std::cout << "[FAIL] Pool with name '" << name_pool << "' not found" << std::endl;
		}
	}
	catch (std::exception const& excep)
	{
		std::cout << excep.what() << std::endl;
	}
}

#endif // DATABASE_SINGLETON_H