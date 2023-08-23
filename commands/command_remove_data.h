
#ifndef FUNDAMENTAL_ALGO_COMMAND_REMOVE_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_REMOVE_DATA_H
#include <iostream>
#include "command.h"
#include "../logger_singleton.h"
#include "../parse.h"
#include <vector>
#include "../database_singleton.h"
#include "../student_definition.h"
#include <string>

class command_remove_data final : public command<std::string>
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	unsigned int _id_session;
	unsigned int _id_student;
	reporting_format _format;
	std::string _subject;


public:

	bool can_execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_remove_data::can_execute(std::string const &request) called", logger::severity::trace);

		if (request.starts_with("REMOVE_DATA")) {
			std::vector<std::string> result_parsed_strings = validation(request, ' ');
			if (result_parsed_strings.size() == 8)
			{
				_pool_name = std::move(result_parsed_strings[1]);
				_scheme_name = std::move(result_parsed_strings[2]);
				_collection_name = std::move(result_parsed_strings[3]);



				// TODO: valid
				_id_session = is_unsigned_with_convert(result_parsed_strings[4]);

				// TODO: valid
				_id_student = is_unsigned_with_convert(result_parsed_strings[5]);

				_format = reporting_format_convert(result_parsed_strings[6]);

				_subject = result_parsed_strings[7];

				return true;
			}
		}
		return false;
	}

	void execute(std::string const& request) noexcept final
	{

		key* data_key = new key();

		data_key->id_session = _id_session;
		data_key->id_student = _id_student;
		data_key->format = _format;
		data_key->subject = _subject;

		database_singleton::get_instance()->remove_data(_pool_name, _scheme_name, _collection_name, data_key);
		logger_singleton::get_instance()->get_logger()->log("command_remove_data::execute(std::string const &request) called", logger::severity::trace);

		delete data_key;
	}

};
#endif // FUNDAMENTAL_ALGO_COMMAND_REMOVE_DATA_H