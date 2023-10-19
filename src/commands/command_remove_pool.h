#ifndef COMMAND_REMOVE_POOL_H
#define COMMAND_REMOVE_POOL_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include <string>
#include <string_view>
#include <fstream>

class command_remove_pool : public command
{
private:
	std::string _pool_name;
	char* _filename_save = nullptr;

public:
	command_remove_pool(char* filename = nullptr) :
		_filename_save(filename) {};
	virtual ~command_remove_pool() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_remove_pool::can_execute(std::string const& request)
{
    logger_singleton::get_instance()
    ->get_logger()
    ->log("command_remove_pool::can_execute(std::string const& request) called",
          logger::severity::trace);

	if (request.starts_with("REMOVE_POOL"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 2)
			return false;

		std::string pool_name = empty_check(result[1]);
		_pool_name = std::move(pool_name.substr(0, pool_name.find("\r")));

		return true;
	}
	return false;
}

void command_remove_pool::execute(std::string const&)
{
	if (_filename_save != nullptr)
	{
		std::ofstream file_save(_filename_save, std::ios::app);
		file_save.is_open();
		file_save << "REMOVE_POOL " + _pool_name << std::endl;
	}

	logger_singleton::get_instance()
		->get_logger()
		->log("command_remove_pool::execute(std::string const&) called",
			logger::severity::trace);

	database_singleton::get_instance()->remove_pool(_pool_name);
	logger_singleton::get_instance()->get_logger()->log("In command REMOVE_POOL execute called",
		logger::severity::trace);
}

#endif // COMMAND_REMOVE_POOL_H