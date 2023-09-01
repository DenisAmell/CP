#ifndef COMMAND_ADD_SCHEME_H
#define COMMAND_ADD_SCHEME_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include "../trees/trees_type.h"

class command_add_scheme : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	trees_type _tree_type;

public:
	virtual ~command_add_scheme() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_add_scheme::can_execute(std::string const& request)
{
	if (request.starts_with("ADD_SCHEME"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 4)
			return false;

		_pool_name = empty_check(result[1]);

		_scheme_name = empty_check(result[2]);

		_tree_type = trees_type_convert(result[3]);

		return true;
	}
	return false;
}

void command_add_scheme::execute(std::string const& request)
{
	database_singleton::get_instance()->add_scheme(_pool_name,
		_scheme_name,
		_tree_type);
	logger_singleton::get_instance()->get_logger()->log("In command ADD_SCHEME execute called",
		logger::severity::trace);
}

#endif // COMMAND_ADD_SCHEME_H