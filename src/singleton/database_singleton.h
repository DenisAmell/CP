#ifndef FUNDAMENTAL_ALGO_DATABASE_SINGLETON_H
#define FUNDAMENTAL_ALGO_DATABASE_SINGLETON_H
#include "../memory/memory.h"
#include "../memory/memory_holder.h"
#include "../singleton/logger_singleton.h"
#include "../logger/logger.h"
#include "../comparer/comparers.h"
#include "../allocators/allocator_type.h"
#include "../tree/tree_type.h"
#include "../type_data/student_definition.h"
#include "../tree/associative_container.h"
#include "../tree/avl_tree.h"
#include "../tree/binary_search_tree.h"
#include "../tree/splay_tree.h"
#include "../tree/red_black_tree.h"
#include "../allocators/boundary_tags_allocator.h"
#include "../allocators/memory_buddy_system.h"
#include "../allocators/list_memory.h"
#include "../conteiners/pool.h"
#include "../request_handler/request_handler_with_command_chain.h"
#include "../tree/tree_type.h"
#include "../string_pool/string_pool.h"
// #include "commands/command_add_pool.h"

// class command_add_pool;

class database_singleton
{
private:
	class stdpair_int_int_comparer final
	{
	private:
		int_comparer _int_comparer;


	public:
		int operator()(std::pair<int, int> const& left, std::pair<int, int> const& right)
		{
			auto user_id_comparison_result = _int_comparer(left.first, right.first);
			if (user_id_comparison_result != 0)
			{
				return user_id_comparison_result;
			}

			return _int_comparer(left.second, right.second);
		}
	};

private:
	static database_singleton* _instance;

	request_handler_with_command_chain<std::string> _chain;

public:
	static database_singleton* get_instance()
	{
		if (_instance == nullptr)
		{
			_instance = new database_singleton();
		}

		return _instance;
	}

private:
	associative_container<std::string, pool>* _database_entrypoint;

public:
	database_singleton()
	{

		_database_entrypoint = new red_black_tree<std::string, pool, stdstring_comparer>();

		_instance = this;
	}

public:
	~database_singleton()
	{
		delete _database_entrypoint;
	}
	database_singleton(database_singleton const&) = delete;
	database_singleton(database_singleton&&) = delete;
	database_singleton& operator=(database_singleton const&) = delete;
	database_singleton& operator=(database_singleton&&) = delete;

public:


	void add_pool(
		std::string const& pool_name,
		allocator_type pool_allocator_type,
		unsigned int pool_allocator_size,
		memory::allocate_mode pool_allocator_allocation_mode,
		tree_type tree_type)
	{

		try
		{
			memory* allocator = nullptr;
			switch (pool_allocator_type)
			{
				// case allocator_type::global_heap:
				//     allocator = new memory_from_global_heap(logger_singleton::get_instance()->get_logger());
				//     break;
			case allocator_type::list_memory:
				allocator = new list_memory(logger_singleton::get_instance()->get_logger(), nullptr, pool_allocator_size, pool_allocator_allocation_mode);
				break;
			case allocator_type::border_descriptors:
				allocator = new border_descriptors_memory(logger_singleton::get_instance()->get_logger(), nullptr, pool_allocator_size, pool_allocator_allocation_mode);
				break;
			case allocator_type::buddy_allocator:
				allocator = new memory_buddy_system(logger_singleton::get_instance()->get_logger(), nullptr, pool_allocator_size, pool_allocator_allocation_mode);
				break;
			}

			_database_entrypoint->insert(pool_name, std::move(pool(allocator, tree_type)));

			std::cout << "[ADD_POOL] Pool with name:" << pool_name << " added to data base" << std::endl
				<< std::endl;
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void add_scheme(std::string const& pool_name, std::string const& scheme_name, tree_type tree_type)
	{
		try
		{

			if (_database_entrypoint->find_to_string(pool_name))
			{
				reinterpret_cast<pool&>(_database_entrypoint->find(pool_name)).add(scheme_name, std::move(scheme(tree_type)));
				std::cout << "[ADD_SCHEME] Scheme with name:" << scheme_name << " added to " << pool_name << std::endl
					<< std::endl;
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void add_collection(std::string const& pool_name, std::string const& scheme_name, std::string const& collection_name, tree_type tree_type)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{
				pool& current_pool = _database_entrypoint->find(pool_name);

				memory* allocator = current_pool.get_allocator();

				if (current_pool.find_to_string(scheme_name))
				{
					reinterpret_cast<scheme&>(current_pool.find(scheme_name)).add(collection_name, std::move(collection(allocator, tree_type)));
					std::cout << "[ADD_COLLECTION] Collection with name:" << collection_name << " added to " << scheme_name << " " << pool_name << std::endl
						<< std::endl;
				}
				else
				{
					std::cout << "[FAIL] Scheme with name:" << scheme_name << " not found" << std::endl
						<< std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void add_data(std::string const& pool_name,
		std::string const& scheme_name,
		std::string const& collection_name,
		unsigned int id_session,
		unsigned int id_student,
		reporting_format format,
		std::string const& subject,
		std::string const& surname,
		std::string const& name,
		std::string const& patronymic,
		std::string const& date,
		std::string const& time,
		unsigned int mark)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{
				pool& current_pool = _database_entrypoint->find(pool_name);
				memory* allocator = current_pool.get_allocator();

				if (current_pool.find_to_string(scheme_name))
				{
					scheme& current_scheme = current_pool.find(scheme_name);

					if (current_scheme.find_to_string(collection_name))
					{

						reinterpret_cast<collection&>(current_scheme.find(collection_name)).add(id_session, id_student, format, subject, surname, name, patronymic, date, time, mark);
						std::cout << "[ADD_DATA] Data added to " << pool_name << " " << scheme_name << " " << collection_name << std::endl
							<< std::endl;
					}
					else
					{
						std::cout << "[FAIL] Collection with name:" << collection_name << " not found" << std::endl
							<< std::endl;
					}
				}
				else
				{
					std::cout << "[FAIL] Scheme with name:" << scheme_name << " not found" << std::endl
						<< std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void update_date(std::string const& pool_name, std::string const& scheme_name,
		std::string const& collection_name,
		key* data_key,
		std::string const& surname,
		std::string const& name,
		std::string const& patronymic,
		std::string const& date,
		std::string const& time,
		unsigned int mark)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{
				pool& current_pool = _database_entrypoint->find(pool_name);
				memory* allocator = current_pool.get_allocator();

				if (current_pool.find_to_string(scheme_name))
				{
					scheme& current_scheme = current_pool.find(scheme_name);

					if (current_scheme.find_to_string(collection_name))
					{
						reinterpret_cast<collection&>(current_scheme.find(collection_name)).update(data_key, surname, name, patronymic, date, time, mark);
						std::cout << "[UPDATE_DATE] Data from:" << pool_name << " " << scheme_name << " " << collection_name << " updated" << std::endl
							<< std::endl;
					}
					else
					{
						std::cout << "[FAIL] Collection with name:" << collection_name << " not found" << std::endl
							<< std::endl;
					}
				}
				else
				{
					std::cout << "[FAIL] Scheme with name:" << scheme_name << " not found" << std::endl
						<< std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void remove_pool(std::string& pool_name)
	{
		try
		{

			pool_name = std::move(pool_name.substr(0, pool_name.find("\r"))); // token is "scott"

			if (_database_entrypoint->find_to_string(pool_name))
			{
				_database_entrypoint->remove(pool_name);
				std::cout << "[REMOVE_POOL] Pool with name :" << pool_name << " removed" << std::endl
					<< std::endl;
				std::cout.flush();
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void remove_scheme(std::string const& pool_name, std::string& scheme_name)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{
				scheme_name = std::move(scheme_name.substr(0, scheme_name.find("\r")));

				reinterpret_cast<pool&>(_database_entrypoint->find(pool_name)).remove(scheme_name);
				std::cout << "[REMOVE_SCHEME] Scheme from:" << pool_name << " removed" << std::endl
					<< std::endl;
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void remove_collection(std::string const& pool_name, std::string const& scheme_name, std::string& collection_name)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{
				pool& current_pool = _database_entrypoint->find(pool_name);

				if (current_pool.find_to_string(scheme_name))
				{
					collection_name = std::move(collection_name.substr(0, collection_name.find("\r")));
					reinterpret_cast<scheme&>(current_pool.find(scheme_name)).remove(collection_name);
					std::cout << "[REMOVE_COLLECTION] Collection from:" << pool_name << " " << scheme_name << " removed" << std::endl
						<< std::endl;
				}
				else
				{
					std::cout << "[FAIL] Scheme with name:" << pool_name << " not found" << std::endl
						<< std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void remove_data(std::string const& pool_name,
		std::string const& scheme_name,
		std::string const& collection_name,
		key* data_key)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{
				pool& current_pool = _database_entrypoint->find(pool_name);
				memory* allocator = current_pool.get_allocator();

				if (current_pool.find_to_string(scheme_name))
				{
					scheme& current_scheme = current_pool.find(scheme_name);

					if (current_scheme.find_to_string(collection_name))
					{
						reinterpret_cast<collection&>(current_scheme.find(collection_name)).remove(data_key);
						std::cout << "[REMOVE_DATA] Data from:" << pool_name << " " << scheme_name << " " << collection_name << " removed" << std::endl
							<< std::endl;
					}
					else
					{
						std::cout << "[FAIL] Collection with name:" << collection_name << " not found" << std::endl
							<< std::endl;
					}
				}
				else
				{
					std::cout << "[FAIL] Scheme with name:" << pool_name << " not found" << std::endl
						<< std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void get_data(std::string const& pool_name, std::string const& scheme_name, std::string const& collection_name, key* data_key)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{

				pool& current_pool = _database_entrypoint->find(pool_name);
				if (current_pool.find_to_string(scheme_name))
				{
					scheme& current_scheme = current_pool.find(scheme_name);

					if (current_scheme.find_to_string(collection_name))
					{

						collection& current_collection = current_scheme.find(collection_name);

						if (current_collection.find_in(data_key))
						{

							values* data = reinterpret_cast<collection&>(current_collection).get(data_key);

							std::cout << "[GET_DATA] Received value from " << pool_name << " " << scheme_name << " " << collection_name << std::endl
								<< std::endl;

							std::cout << "\tData:" << std::endl;

							std::cout << "----------------------------------" << std::endl;

							std::cout << "Surname: " << data->student_surname << std::endl;
							std::cout << "Name: " << data->student_name << std::endl;
							std::cout << "patronymic: " << data->student_patronymic << std::endl;
							std::cout << "Date: " << data->event_date << std::endl;
							std::cout << "Time: " << data->event_time << std::endl;
							std::cout << "Mark: " << data->mark << std::endl
								<< std::endl;
						}
						else
						{
							std::cout << "[FAIL] Data_key not found" << std::endl
								<< std::endl;
						}
					}
					else
					{
						std::cout << "[FAIL] Collection with name:" << collection_name << " not found" << std::endl
							<< std::endl;
					}
				}
				else
				{
					std::cout << "[FAIL] Scheme with name:" << scheme_name << " not found" << std::endl
						<< std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}

	void get_data_between_keys(std::string const& pool_name, std::string const& scheme_name, std::string const& collection_name, key* const& min_key, key* const& max_key)
	{
		try
		{
			if (_database_entrypoint->find_to_string(pool_name))
			{
				pool const& current_pool = _database_entrypoint->find(pool_name);

				if (current_pool.find_to_string(scheme_name))
				{
					scheme const& current_scheme = current_pool.find(scheme_name);

					if (current_scheme.find_to_string(collection_name))
					{
						std::vector<values*> data = reinterpret_cast<collection&>(current_scheme.find(collection_name)).get_between_keys(min_key, max_key);

						std::cout << "GET_DATA_BETWEEM] Received values from " << pool_name << " " << scheme_name << " " << collection_name << std::endl
							<< std::endl;

						int index = 1;

						for (auto const& data_value : data)
						{
							std::cout << "\tData:" << index << std::endl;

							std::cout << "----------------------------------" << std::endl;

							std::cout << "Surname: " << data_value->student_surname << std::endl;
							std::cout << "Name: " << data_value->student_name << std::endl;
							std::cout << "patronymic: " << data_value->student_patronymic << std::endl;
							std::cout << "Date: " << data_value->event_date << std::endl;
							std::cout << "Time: " << data_value->event_time << std::endl;
							std::cout << "Mark: " << data_value->mark << std::endl
								<< std::endl;

							index++;
						}
					}
					else
					{
						std::cout << "[FAIL] Collection with name:" << collection_name << " not found" << std::endl
							<< std::endl;
					}
				}
				else
				{
					std::cout << "[FAIL] Scheme with name:" << scheme_name << " not found" << std::endl
						<< std::endl;
				}
			}
			else
			{
				std::cout << "[FAIL] Pool with name:" << pool_name << " not found" << std::endl
					<< std::endl;
			}
		}
		catch (std::exception const& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
};

database_singleton* database_singleton::_instance = nullptr;

#endif // FUNDAMENTAL_ALGO_DATABASE_SINGLETON_H