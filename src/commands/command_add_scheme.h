#ifndef FUNDAMENTAL_ALGO_COMMAND_ADD_SCHEME_H
#define FUNDAMENTAL_ALGO_COMMAND_ADD_SCHEME_H
#include <iostream>

#include "command.h"
#include "../singleton/logger_singleton.h"
#include "../singleton/database_singleton.h"
#include "../tree/tree_type.h"

class command_add_scheme final : public command<std::string>
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	tree_type _tree_type;

public:
	bool can_execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_add_scheme::can_execute(std::string const &request) called", logger::severity::trace);

		if (request.starts_with("ADD_SCHEME"))
		{

			std::vector<std::string> result_parsed_strings = validation(request, ' ');

			if (result_parsed_strings.size() == 4)
			{
				_pool_name = std::move(result_parsed_strings[1]);
				_scheme_name = std::move(result_parsed_strings[2]);

				if (result_parsed_strings[3].starts_with("binary_search_tree"))
				{
					_tree_type = tree_type::BINARY_SEARCH_TREE;
				}
				else if (result_parsed_strings[3].starts_with("red_black_tree"))
				{
					_tree_type = tree_type::RED_BLACK_TREE;

				}
				else if (result_parsed_strings[3].starts_with("avl_tree"))
				{
					_tree_type = tree_type::AVL_TREE;
				}
				else if (result_parsed_strings[3].starts_with("splay_tree")) {
					_tree_type = tree_type::SPALY_TREE;
				}
				else
				{
					return false;
				}

				return true;
			}
		}
		return false;
	}

	void execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_add_scheme::execute(std::string const &request) called", logger::severity::trace);
		database_singleton::get_instance()->add_scheme(_pool_name, _scheme_name, _tree_type);
	}
};

#endif // FUNDAMENTAL_ALGO_COMMAND_ADD_SCHEME_H