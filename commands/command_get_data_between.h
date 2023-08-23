#ifndef FUNDAMENTAL_ALGO_COMMAND_GET_DATA_BETWEEN_H
#define FUNDAMENTAL_ALGO_COMMAND_GET_DATA_BETWEEN_H

#include "../logger_singleton.h"
#include "../database_singleton.h"
#include "../student_definition.h"
#include <iostream>
#include "command.h"
#include "../parse.h"
class command_get_data_between final : public command<std::string>
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	unsigned int _id_session_for_first_key;
	unsigned int _id_student_for_first_key;
	reporting_format _format_for_first_key;
	std::string _subject_for_first_key;
	unsigned int _id_session_for_second_key;
	unsigned int _id_student_for_second_key;
	reporting_format _format_for_second_key;
	std::string _subject_for_second_key;
public:
	bool can_execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_get_data_between::can_execute(std::string const &request) called", logger::severity::trace);

		if (request.starts_with("GET_DATA_BETWEEN")) {
			std::vector<std::string> result_parsed_strings = validation(request, ' ');
			if (result_parsed_strings.size() == 12)
			{
				_pool_name = std::move(result_parsed_strings[1]);
				_scheme_name = std::move(result_parsed_strings[2]);
				_collection_name = std::move(result_parsed_strings[3]);

				_id_session_for_first_key = is_unsigned_with_convert(result_parsed_strings[4]);
				_id_student_for_first_key = is_unsigned_with_convert(result_parsed_strings[5]);

				_format_for_first_key = reporting_format_convert(result_parsed_strings[6]);
				_subject_for_first_key = std::move(result_parsed_strings[7]);


				_id_session_for_second_key = is_unsigned_with_convert(result_parsed_strings[8]);
				_id_student_for_second_key = is_unsigned_with_convert(result_parsed_strings[9]);

				_format_for_second_key = reporting_format_convert(result_parsed_strings[10]);
				_subject_for_second_key = std::move(result_parsed_strings[11]);

				return true;
			}
		}
		return false;
	}

	void execute(std::string const& request) noexcept final
	{
		key* min_key = new key();

		min_key->id_session = _id_session_for_first_key;
		min_key->id_student = _id_student_for_first_key;
		min_key->format = _format_for_first_key;
		min_key->subject = _subject_for_first_key;

		key* max_key = new key();

		max_key->id_session = _id_session_for_second_key;
		max_key->id_student = _id_student_for_second_key;
		max_key->format = _format_for_second_key;
		max_key->subject = _subject_for_second_key;

		database_singleton::get_instance()->get_data_between_keys(_pool_name, _scheme_name, _collection_name, min_key, max_key);
		logger_singleton::get_instance()->get_logger()->log("command_get_data_between::execute(std::string const &request) called", logger::severity::trace);

		delete min_key;
		delete max_key;
	}
};
#endif // FUNDAMENTAL_ALGO_COMMAND_GET_DATA_BETWEEN_H