#ifndef FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H
#define FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H

#include "logger_singleton.h"
#include <iostream>
#include "command.h"
#include "parse.h"
#include "../database_singleton.h"
#include "../student_definition.h"

class command_update_data final : public command<std::string>
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	unsigned int _id_session;
	unsigned int _id_student;
	reporting_format _format;
	std::string _subject;
	std::string _student_name;
	std::string _student_surname;
	std::string _student_patronymic;
	std::string _event_date;
	std::string _event_time;
	unsigned int _mark;


public:
	bool can_execute(std::string const& request) noexcept final
	{
		logger_singleton::get_instance()->get_logger()->log("command_update_data::can_execute(std::string const &request) called", logger::severity::trace);

		if (request.starts_with("UPDATE_DATA")) {
			std::vector<std::string> result_parsed_strings = validation(request, ' ');
			if (result_parsed_strings.size() == 14)
			{
				_pool_name = std::move(result_parsed_strings[1]);
				_scheme_name = std::move(result_parsed_strings[2]);
				_collection_name = std::move(result_parsed_strings[3]);

				// _id_session = is_unsigned_with_convert(std::move(result_parsed_strings[4])); // session id
				// _id_student = is_unsigned_with_convert(std::move(result_parsed_strings[5])); // student id

				std::stringstream id_session(result_parsed_strings[4]);
				id_session >> _id_session;
				std::stringstream id_student(result_parsed_strings[5]);
				id_student >> _id_student;
				_format = reporting_format_convert(result_parsed_strings[6]);
				_subject = std::move(result_parsed_strings[7]);

				_student_name = std::move(result_parsed_strings[8]);
				_student_surname = std::move(result_parsed_strings[9]);
				_student_patronymic = std::move(result_parsed_strings[10]);

				// _current_student._values.tutor_name = std::move(result_parsed_strings[6]);
				// _current_student._values.tutor_surname = std::move(result_parsed_strings[7]);
				// _current_student._values.tutor_patronymic = std::move(result_parsed_strings[8]);
				_event_date = result_parsed_strings[11]; // TODO: validate
				_event_time = result_parsed_strings[12]; // TODO: validate
				_mark = is_valid_grade(_format, result_parsed_strings[13]);

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

		/*values* data_value = new values();

		data_value->student_name = _student_name;
		data_value->student_surname = _student_surname;
		data_value->student_patronymic = _student_patronymic;
		data_value->event_date = _event_date;
		data_value->event_time = _event_time;
		data_value->mark = _mark; */


		database_singleton::get_instance()->update_date(_pool_name, _scheme_name, _collection_name, data_key, _student_surname, _student_name, _student_patronymic, _event_date, _event_time, _mark);
		logger_singleton::get_instance()->get_logger()->log("command_update_data::execute(std::string const &request) called", logger::severity::trace);
		delete data_key;
	}
};

#endif // FUNDAMENTAL_ALGO_COMMAND_UPDATE_DATA_H