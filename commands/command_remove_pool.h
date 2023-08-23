#ifndef FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
#define FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H
#include "logger_singleton.h"
#include "logger/logger.h"
#include "command.h"
#include "../parse.h"
#include "../database_singleton.h"

class command_remove_pool final : public command<std::string>
{
private:
	std::string _pool_name;

public:
	bool can_execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_remove_pool::can_execute(std::string const &request) called", logger::severity::trace);
		if (request.starts_with("REMOVE_POOL")) {


			std::vector<std::string> result_parsed_strings = validation(request, ' ');
			if (result_parsed_strings.size() == 2)
			{
				_pool_name = result_parsed_strings[1];
				return true;
			}
		}
		return false;
	}

	void execute(std::string const& request) noexcept final
	{
		database_singleton::get_instance()->remove_pool(_pool_name);
		logger_singleton::get_instance()->get_logger()->log("command_remove_pool::execute(std::string const &request) called", logger::severity::trace);
	}
};
#endif // FUNDAMENTAL_ALGO_COMMAND_REMOVE_POOL_H