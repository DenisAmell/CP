#ifndef COMMAND_GET_DATA_BETWEEN_H
#define COMMAND_GET_DATA_BETWEEN_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"

class command_get_data_between : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	key _left_data_key;
	key _right_data_key;

public:
	virtual ~command_get_data_between() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_get_data_between::can_execute(std::string const& request)
{
	if (request.starts_with("GET_DATA_BETWEEN"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 6)
			return false;

		_pool_name = empty_check(result[1]);

		_scheme_name = empty_check(result[2]);

		_collection_name = empty_check(result[3]);

		_left_data_key._id = is_unsigned_convert(result[4]);

		_right_data_key._id = is_unsigned_convert(result[5]);

		return true;
	}
	return false;
}

void command_get_data_between::execute(std::string const&)
{
	key* lk = new key(std::move(_left_data_key));
	key* rk = new key(std::move(_right_data_key));
	database_singleton::get_instance()->get_data_between(_pool_name,
		_scheme_name,
		_collection_name,
		lk,
		rk);
	logger_singleton::get_instance()->get_logger()->log("In command GET_DATA_BETWEEN execute called", logger::severity::trace);
}

#endif // COMMAND_GET_DATA_BETWEEN_H