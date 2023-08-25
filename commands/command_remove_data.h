#ifndef COMMAND_remove_data_H
#define COMMAND_remove_data_H

#include "command.h"

class remove_data: public command
{
    public:
        virtual ~remove_data() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_remove_data_H