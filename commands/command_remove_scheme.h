#ifndef COMMAND_REMOVE_SCHEME_H
#define COMMAND_REMOVE_SCHEME_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"

class command_remove_scheme : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;

public:
	virtual ~command_remove_scheme() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_remove_scheme::can_execute(std::string const& request)
{
	if (request.starts_with("REMOVE_SCHEME"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 3)
			return false;

		_pool_name = empty_check(result[1]);

		_scheme_name = empty_check(result[2]);

		return true;
	}
	return false;
}

void command_remove_scheme::execute(std::string const&)
{
	database_singleton::get_instance()->remove_scheme(_pool_name,
		_scheme_name);
	logger_singleton::get_instance()->get_logger()->log("In command REMOVE_SCHEME execute called",
		logger::severity::trace);
}

#endif // COMMAND_REMOVE_SCHEME_H