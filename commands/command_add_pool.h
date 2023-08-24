#ifndef COMMAND_ADD_POOL_H
#define COMMAND_ADD_POOL_H

#include "command.h"
#include "../pars.h"
#include "../allocators/allocator_type.h"
#include "../memory/memory.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include "../trees/trees_type.h"

class command_add_pool : public command
{
private:
	std::string _pool_name;
	allocator_type _pool_allocator_type;
	size_t _allocator_size;
	memory::allocate_mode _pool_allocate_mode;
	trees_type _tree_type;


public:
	virtual ~command_add_pool() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_add_pool::can_execute(std::string const& request)
{
	if (request.starts_with("ADD_POOL"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 6)
			return false;

		_pool_name = result[1];
		if (result[2] == "memory_list")
			_pool_allocator_type = allocator_type::MEMORY_LIST;
		else if (result[2] == "buddies_system")
			_pool_allocator_type = allocator_type::BUDDIES_SYSTEM;
		else if (result[2] == "border_descriptors")
			_pool_allocator_type = allocator_type::BORDER_DESCRIPTORS;
		else
			return false;

		std::stringstream size(result[3]);
		size >> _allocator_size;

		if (result[4] == "first_fit")
			_pool_allocate_mode = memory::allocate_mode::first_fit;
		else if (result[4] == "best_fit")
			_pool_allocate_mode = memory::allocate_mode::best_fit;
		else if (result[4] == "worst_fit")
			_pool_allocate_mode = memory::allocate_mode::worst_fit;
		else
			return false;

		if (result[5].starts_with("avl"))
			_tree_type = trees_type::AVL;
		else if (result[5].starts_with("bst"))
			_tree_type = trees_type::BST;
		else if (result[5].starts_with("rb"))
			_tree_type = trees_type::RB;
		else if (result[5].starts_with("splay"))
			_tree_type = trees_type::SPLAY;
		else
			return false;

		return true;
	}
	return false;
}
// FIXME: попробовать разобраться как выпилить перенос строки

void command_add_pool::execute(std::string const& request)
{
	database_singleton::get_instance()->add_pool(_pool_name,
		_pool_allocator_type,
		_allocator_size,
		_pool_allocate_mode,
		_tree_type);
	logger_singleton::get_instance()->get_logger()->log("In command ADD_POOL execute called", logger::severity::trace);
}

#endif // COMMAND_ADD_POOL_H