#ifndef FUNDAMENTAL_ALGO_COMMAND_GET_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_GET_DATA_H
#include <iostream>
#include "command.h"
#include "../database_singleton.h"

class command_get_data final : public command<std::string>
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	key _data_key;

public:
	bool can_execute(std::string const &request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_get_data::can_execute(std::string const &request) called", logger::severity::trace);
		// if (!prefix_validation("GET_DATA", request))
		//     return false;

		if (request.starts_with("GET_DATA"))
		{

			std::vector<std::string> result_parsed_strings = validation(request, ' ');
			if (result_parsed_strings.size() == 8)
			{
				_pool_name = std::move(result_parsed_strings[1]);
				_scheme_name = std::move(result_parsed_strings[2]);
				_collection_name = std::move(result_parsed_strings[3]);

				// _data_key->id_session = is_unsigned_with_convert(result_parsed_strings[4]);
				// _data_key->id_session = is_unsigned_with_convert(result_parsed_strings[5]);
				std::stringstream id_session(result_parsed_strings[4]);
				id_session >> _data_key.id_session;
				std::stringstream id_student(result_parsed_strings[5]);
				id_student >> _data_key.id_student;

				_data_key.format = reporting_format_convert(result_parsed_strings[6]);

				_data_key.subject = std::move(result_parsed_strings[7].substr(0, result_parsed_strings[7].find("\r")));

				return true;
			}
		}
		return false;
	}

	void execute(std::string const &request) noexcept final
	{
		database_singleton::get_instance()->get_data(_pool_name, _scheme_name, _collection_name, &_data_key);
		logger_singleton::get_instance()
			->get_logger()
			->log("command_get_data::execute(std::string const &request) called", logger::severity::trace);
	}
};
#endif // FUNDAMENTAL_ALGO_COMMAND_GET_DATA_H