#ifndef COMMAND_add_data_H
#define COMMAND_add_data_H

#include "command.h"

class add_data: public command
{
    public:
        virtual ~add_data() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_add_data_H