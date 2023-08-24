#ifndef COMMAND_ADD_COLLECTION_H
#define COMMAND_ADD_COLLECTION_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include "../trees/trees_type.h"

class command_add_collection : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	trees_type _tree_type;

public:
	virtual ~command_add_collection() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_add_collection::can_execute(std::string const& request)
{
	if (request.starts_with("ADD_COLLECTION"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 5)
			return false;

		_pool_name = result[1];

		_scheme_name = result[2];

		_collection_name = result[3];

		if (result[4].starts_with("avl"))
			_tree_type = trees_type::AVL;
		else if (result[4].starts_with("bst"))
			_tree_type = trees_type::BST;
		else if (result[4].starts_with("rb"))
			_tree_type = trees_type::RB;
		else if (result[4].starts_with("splay"))
			_tree_type = trees_type::SPLAY;
		else
			return false;

		return true;
	}
	return false;
}

void command_add_collection::execute(std::string const& request)
{
	database_singleton::get_instance()->add_collection(_pool_name,
		_scheme_name,
		_collection_name,
		_tree_type);
	logger_singleton::get_instance()->get_logger()->log("In command ADD_COLLECTION execute called",
		logger::severity::trace);
}

#endif // COMMAND_ADD_COLLECTION_H