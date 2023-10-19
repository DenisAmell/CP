#ifndef COMMAND_CLEAN_H
#define COMMAND_CLEAN_H

#include "command.h"
#include "../pars.h"
#include "../database_singleton.h"
#include "../logger_singleton.h"
#include "../trees/trees_type.h"
#include <string>
#include <string_view>
#include <fstream>

class command_clean : public command
{
private:
    std::string _file_for_cleaning;
//    char* _filename_save = nullptr;

public:
//    command_clean(char* filename) :
//            _filename_save(filename) {};
    virtual ~command_clean() = default;

public:
    bool can_execute(std::string const&) override;
    void execute(std::string const& ) override;
};

bool command_clean::can_execute(std::string const& request)
{
    logger_singleton::get_instance()
            ->get_logger()
            ->log("command_clear::can_execute(std::string const& request) called",
                  logger::severity::trace);

    if (request.starts_with("CLEAR"))
    {
        std::vector<std::string> result = split(request, ' ');

        if (result.size() != 2)
            return false;

        std::cout << '[' << result[1] << ']' << std::endl;

        std::string file_for_clean = result[1];
        _file_for_cleaning = std::move(file_for_clean.substr(0, file_for_clean.find("\r")));

        return true;
    }
    return false;
}

void command_clean::execute(std::string const& request)
{
    logger_singleton::get_instance()
            ->get_logger()
            ->log("command_clean::execute(std::string const& request) called",
                  logger::severity::trace);

    database_singleton::get_instance()->clean(_file_for_cleaning);
    logger_singleton::get_instance()->get_logger()->log("In command CLEAN execute called",
                                                        logger::severity::trace);
}

#endif // COMMAND_CLEAN_H