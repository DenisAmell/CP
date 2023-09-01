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

		_pool_name = empty_check(result[1]);

		_pool_allocator_type = allocator_type_convert(result[2]);

		_allocator_size = is_unsigned_convert(result[3]);

		_pool_allocate_mode = allocate_mode_convert(result[4]);

		_tree_type = trees_type_convert(result[5]);

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