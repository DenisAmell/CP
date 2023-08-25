#ifndef COMMAND_update_H
#define COMMAND_update_H

#include "command.h"

class update: public command
{
    public:
        virtual ~update() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_update_H