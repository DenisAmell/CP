#ifndef FUNDAMENTAL_ALGO_COMMAND_ADD_POOL_H
#define FUNDAMENTAL_ALGO_COMMAND_ADD_POOL_H

#include "command.h"
#include "../database_singleton.h"
#include "../memory/memory.h"
#include "../parse.h"
#include "../tree/tree_type.h"
#include <string>
#include <string_view>

class database_singleton;

class command_add_pool final : public command<std::string>
{
private:
	std::string _pool_name;
	allocator_type _pool_allocator_type;
	unsigned int _pool_allocator_size;
	memory::allocate_mode _pool_allocator_allocation_mode;
	tree_type _tree_type;

public:
	bool can_execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_add_pool::can_execute(std::string const &request) called", logger::severity::trace);
		// // if (!prefix_validation("ADD_POOL", request))
		// //     return false;

		// std::vector<std::string> result_parsed_strings = validation("ADD_POOL", request);


		if (request.starts_with("ADD_POOL"))
		{

			auto result_parsed_strings = validation(request, ' ');

			if (result_parsed_strings.size() == 6)
			{

				_pool_name = result_parsed_strings[1];

				if (result_parsed_strings[2] == "list_memory")
				{
					_pool_allocator_type = allocator_type::list_memory;
				}
				else if (result_parsed_strings[2] == "border_descriptors")
				{

					_pool_allocator_type = allocator_type::border_descriptors;
				}
				else if (result_parsed_strings[2] == "buddies_system")
				{
					_pool_allocator_type = allocator_type::buddy_allocator;
				}
				else
				{
					return false;
				}

				std::stringstream size(result_parsed_strings[3]);
				size >> _pool_allocator_size;

				// if (_digit_validator(argc[3]))
				// {
				//     std::stringstream size(argc[3]);
				//     size >> _pool_allocator_size;
				// }
				// else
				// {
				//     return false;
				// }



				if (result_parsed_strings[4] == "first_fit")
				{
					_pool_allocator_allocation_mode = memory::allocate_mode::first_fit;
				}
				else if (result_parsed_strings[4] == "best_fit")
				{
					_pool_allocator_allocation_mode = memory::allocate_mode::best_fit;
				}
				else if (result_parsed_strings[4] == "worst_fit")
				{
					_pool_allocator_allocation_mode = memory::allocate_mode::worst_fit;
				}
				else
				{
					return false;
				}

				if (result_parsed_strings[5] == "binary_search_tree")
				{
					_tree_type = tree_type::BINARY_SEARCH_TREE;
				}
				else if (result_parsed_strings[5] == "red_black_tree")
				{
					_tree_type = tree_type::RED_BLACK_TREE;
				}
				else if (result_parsed_strings[5] == "avl_tree")
				{
					_tree_type = tree_type::AVL_TREE;
				}
				else if (result_parsed_strings[5] == "splay_tree") {
					_tree_type = tree_type::SPALY_TREE;
				}
				else
				{
					return false;
				}

				return true;
				// _pool_name = std::move(result_parsed_strings[1]);

				// try
				// {
				//     _pool_allocator_type = string_to_allocator_type(result_parsed_strings[2]);
				// }
				// catch (doesnt_exist(&))
				// {
				//     return false;
				// }

				// try
				// {
				//     _pool_allocator_allocation_mode = allocation_mode_convert(result_parsed_strings[3]);
				// }
				// catch (doesnt_exist(&))
				// {
				//     return false;
				// }

				// try
				// {
				//     _pool_allocator_size = is_unsigned_with_convert(result_parsed_strings[4]);
				// }
				// catch (doesnt_exist(&))
				// {
				//     return false;
				// }

				// return true;
			}
		}
		return false;
	}

	void execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_add_pool::execute(std::string const &request) called", logger::severity::trace);
		database_singleton::get_instance()->add_pool(_pool_name, _pool_allocator_type, _pool_allocator_size, _pool_allocator_allocation_mode, _tree_type);
	}
};
#endif // FUNDAMENTAL_ALGO_COMMAND_ADD_POOL_H