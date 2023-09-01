#ifndef COMMAND_REMOVE_DATA_H
#define COMMAND_REMOVE_DATA_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"

class command_remove_data : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	key _data_key;

public:
	virtual ~command_remove_data() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_remove_data::can_execute(std::string const& request)
{
	if (request.starts_with("REMOVE_DATA"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 5)
			return false;

		_pool_name = empty_check(result[1]);

		_scheme_name = empty_check(result[2]);

		_collection_name = empty_check(result[3]);

		_data_key._id = is_unsigned_convert(result[4]);

		return true;
	}
	return false;
}

void command_remove_data::execute(std::string const&)
{
	key* k = new key(std::move(_data_key));
	database_singleton::get_instance()->remove_data(_pool_name,
		_scheme_name,
		_collection_name,
		k);
	logger_singleton::get_instance()->get_logger()->log("In command REMOVE_DATA execute called", logger::severity::trace);
}

#endif // COMMAND_REMOVE_DATA_H