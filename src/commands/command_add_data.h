#ifndef COMMAND_ADD_DATA_H
#define COMMAND_ADD_DATA_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include "../collections/work_calendar.h"
#include <iostream>
#include <string>
#include <string_view>
#include <fstream>

class command_add_data : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	key _data_key;
	value _data_value;
	char* _filename_save = nullptr;

public:
	command_add_data(char* filename = nullptr) :
		_filename_save(filename) {};
	virtual ~command_add_data() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_add_data::can_execute(std::string const& request)
{
    logger_singleton::get_instance()
    ->get_logger()
    ->log("command_add_data::can_execute(std::string const& request) called", logger::severity::trace);

	if (request.starts_with("ADD_DATA"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 16)
			return false;

		_pool_name = empty_check(result[1]);
		_scheme_name = empty_check(result[2]);
		_collection_name = empty_check(result[3]);

		_data_key._id = is_unsigned_convert(result[4]);

		_data_value._type_of_meeting = type_of_meeting_convert(result[5]);
		_data_value._format = format_convert(result[6]);
		_data_value._meeting_description = string_flyweight_factory::get_instance().get_string_flyweight(result[7])->get_value();
		_data_value._link_to_meeting = string_flyweight_factory::get_instance().get_string_flyweight(result[8])->get_value();
		_data_value._first_name = string_flyweight_factory::get_instance().get_string_flyweight(result[9])->get_value();
		_data_value._last_name = string_flyweight_factory::get_instance().get_string_flyweight(result[10])->get_value();
		_data_value._middle_name = string_flyweight_factory::get_instance().get_string_flyweight(result[11])->get_value();
		_data_value._data = string_flyweight_factory::get_instance().get_string_flyweight(result[12])->get_value();
		_data_value._time = string_flyweight_factory::get_instance().get_string_flyweight(result[13])->get_value();
		_data_value._duration_of_meeting = is_unsigned_convert(result[14]);

		std::string list_invites = result[15];
		_data_value._list_invitees = string_flyweight_factory::get_instance().get_string_flyweight(list_invites.substr(0, list_invites.find("\r")))->get_value();

		return true;
	}
	return false;
}

void command_add_data::execute(std::string const& request)
{
	if (_filename_save != nullptr)
	{
		std::ofstream file_save(_filename_save, std::ios::app);
		file_save.is_open();
		file_save << "ADD_DATA " + _pool_name  + " "
			+ _scheme_name + " "
			+ _collection_name  + " "
			+ std::to_string(_data_key._id) + " "
			+ type_of_meeting_convert_to_string(_data_value._type_of_meeting) + " "
			+ format_convert_to_string(_data_value._format) + " "
			+ *(_data_value._meeting_description) + " "
			+ *(_data_value._link_to_meeting ) + " "
			+ *(_data_value._first_name ) + " "
			+ *(_data_value._last_name) + " "
			+ *(_data_value._middle_name) + " "
			+ *(_data_value._data ) + " "
			+ *(_data_value._time) + " "
			+ std::to_string(_data_value._duration_of_meeting) + " "
			+ *(_data_value._list_invitees) << std::endl;
			//TODO: add other areas of structures 'work_calendar' + pars_to_string for this areas
	}

	logger_singleton::get_instance()
		->get_logger()
		->log("command_add_data::execute(std::string const& request) called", 
			logger::severity::trace);

	key* k = new key(std::move(_data_key));
	value* v = new value(std::move(_data_value));
	// TODO: ес пролетит исключение, почистить k и v
	database_singleton::get_instance()->add_data(_pool_name,
		_scheme_name,
		_collection_name,
		k,
		v);
	logger_singleton::get_instance()->get_logger()->log("In command ADD_DATA execute called", logger::severity::trace);
}

#endif // COMMAND_ADD_DATA_H