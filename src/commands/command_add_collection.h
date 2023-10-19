#ifndef COMMAND_ADD_COLLECTION_H
#define COMMAND_ADD_COLLECTION_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include "../trees/trees_type.h"
#include <string>
#include <string_view>
#include <fstream>

class command_add_collection : public command
{
private:
	std::string _pool_name;
	std::string _scheme_name;
	std::string _collection_name;
	trees_type _tree_type;
	char* _filename_save = nullptr;

public:
	command_add_collection(char* filename = nullptr) :
		_filename_save(filename) {};
	virtual ~command_add_collection() = default;

public:
	bool can_execute(std::string const&) override;
	void execute(std::string const&) override;
};

bool command_add_collection::can_execute(std::string const& request)
{
    logger_singleton::get_instance()
    ->get_logger()
    ->log("command_add_collection::can_execute(std::string const& request) called",
          logger::severity::trace);

	if (request.starts_with("ADD_COLLECTION"))
	{
		std::vector<std::string> result = split(request, ' ');

		if (result.size() != 5)
			return false;

		std::cout << '[' << result[1] << ']' << std::endl;
		_pool_name = empty_check(result[1]);

		_scheme_name = empty_check(result[2]);

		_collection_name = empty_check(result[3]);

		_tree_type = trees_type_convert(result[4]);

		return true;
	}
	return false;
}

void command_add_collection::execute(std::string const& request)
{
	if (_filename_save != nullptr)
	{
		std::ofstream file_save(_filename_save, std::ios::app);
		file_save.is_open();
		file_save << "ADD_COLLECTION " + _pool_name + " "
			+ _scheme_name + " "
			+ _collection_name + " "
			+ trees_type_convert_to_string(_tree_type) << std::endl;
	}

	logger_singleton::get_instance()
		->get_logger()
		->log("command_add_collection::execute(std::string const& request) called", 
			logger::severity::trace);

	database_singleton::get_instance()->add_collection(_pool_name,
		_scheme_name,
		_collection_name,
		_tree_type);
	logger_singleton::get_instance()->get_logger()->log("In command ADD_COLLECTION execute called",
		logger::severity::trace);
}

#endif // COMMAND_ADD_COLLECTION_H