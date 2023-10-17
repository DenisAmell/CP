#ifndef COMMAND_GET_DATA_H
#define COMMAND_GET_DATA_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include <string>
#include <string_view>
#include <fstream>

class command_get_data : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	key _data_key;
	char* _filename_save = nullptr;

public:
	command_get_data(char* filename) :
		_filename_save(filename) {};
	virtual ~command_get_data() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_get_data::can_execute(std::string const& request)
{
    logger_singleton::get_instance()
    ->get_logger()
    ->log("command_get_data::can_execute(std::string const& request) called",
          logger::severity::trace);

	if (request.starts_with("GET_DATA"))
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

void command_get_data::execute(std::string const&)
{
	if (_filename_save != nullptr)
	{
		std::ofstream file_save(_filename_save, std::ios::app);
		file_save.is_open();
		file_save << "GET_DATA " + _pool_name
			+ _scheme_name
			+ _collection_name
			+ std::to_string(_data_key._id) << std::endl;
	}

	logger_singleton::get_instance()
		->get_logger()
		->log("command_get_data::execute(std::string const&) called",
			logger::severity::trace);

	key* k = new key(std::move(_data_key));
	database_singleton::get_instance()->get_data(_pool_name,
		_scheme_name,
		_collection_name,
		k);
	logger_singleton::get_instance()->get_logger()->log("In command GET_DATA execute called", logger::severity::trace);
}

#endif // COMMAND_GET_DATA_H