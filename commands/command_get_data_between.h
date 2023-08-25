#ifndef COMMAND_get_data_between_H
#define COMMAND_get_data_between_H

#include "command.h"

class get_data_between: public command
{
    public:
        virtual ~get_data_between() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_get_data_between_H