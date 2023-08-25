#ifndef COMMAND_remove_scheme_H
#define COMMAND_remove_scheme_H

#include "command.h"

class remove_scheme: public command
{
    public:
        virtual ~remove_scheme() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_remove_scheme_H