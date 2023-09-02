#ifndef COMMAND_ADD_DATA_H
#define COMMAND_ADD_DATA_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include "../collections/work_calendar.h"
#include <iostream>

class command_add_data : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	key _data_key;
	value _data_value;

public:
	virtual ~command_add_data() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_add_data::can_execute(std::string const& request)
{
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
		_data_value._meeting_description = result[7];
		_data_value._link_to_meeting = result[8];
		_data_value._first_name = name_surname_convert(result[9]);
		_data_value._last_name = name_surname_convert(result[10]);
		_data_value._middle_name = middle_name_convert(result[11]);
		_data_value._data = data_convert(result[12]);
		_data_value._time = time_convert(result[13]);
		_data_value._duration_of_meeting = is_unsigned_convert(result[14]);

		std::string list_invites = result[15];
		_data_value._list_invitees = std::move(list_invites.substr(0, list_invites.find("\r")));

		return true;
	}
	return false;
}

void command_add_data::execute(std::string const& request)
{
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