#ifndef COMMAND_GET_DATA_BETWEEN_H
#define COMMAND_GET_DATA_BETWEEN_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include <string>
#include <string_view>
#include <fstream>

class command_get_data_between : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	key _left_data_key;
	key _right_data_key;
	char* _filename_save = nullptr;

public:
	command_get_data_between(char* filename = nullptr) :
		_filename_save(filename) {};
	virtual ~command_get_data_between() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_get_data_between::can_execute(std::string const& request)
{
    logger_singleton::get_instance()
    ->get_logger()
    ->log("command_get_data_between::can_execute(std::string const& request) called",
          logger::severity::trace);

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

        if (_left_data_key._id > _right_data_key._id)
            return false;

		return true;
	}
	return false;
}

void command_get_data_between::execute(std::string const&)
{
	if (_filename_save != nullptr)
	{
		std::ofstream file_save(_filename_save, std::ios::app);
		file_save.is_open();
		file_save << "GET_DATA_BETWEEN "
			+ _pool_name + " "
			+ _scheme_name + " "
			+ _collection_name + " "
			+ std::to_string(_left_data_key._id) + " "
			+ std::to_string(_right_data_key._id) << std::endl;
	}

	logger_singleton::get_instance()
		->get_logger()
		->log("command_get_data_between::execute(std::string const&) called", 
			logger::severity::trace);

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