#ifndef COMMAND_get_data_H
#define COMMAND_get_data_H

#include "command.h"

class get_data: public command
{
    public:
        virtual ~get_data() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_get_data_H