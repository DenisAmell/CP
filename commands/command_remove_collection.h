#ifndef COMMANDREMOVE_COLLECTION_H
#define COMMANDREMOVE_COLLECTION_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"

class command_remove_collection : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;

public:
	virtual ~command_remove_collection() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_remove_collection::can_execute(std::string const& request)
{
	if (request.starts_with("REMOVE_COLLECTION"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 4)
			return false;

		_pool_name = empty_check(result[1]);

		_scheme_name = empty_check(result[2]);

		_collection_name = empty_check(result[3]);

		return true;
	}
	return false;
}

void command_remove_collection::execute(std::string const&)
{
	database_singleton::get_instance()->remove_collection(_pool_name,
		_scheme_name,
		_collection_name);
	logger_singleton::get_instance()->get_logger()->log("In command REMOVE_COLLECTION execute called",
		logger::severity::trace);
}

#endif // COMMANDREMOVE_COLLECTION_H