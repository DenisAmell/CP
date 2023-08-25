#ifndef COMMAND_add_scheme_H
#define COMMAND_add_scheme_H

#include "command.h"

class add_scheme: public command
{
    public:
        virtual ~add_scheme() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_add_scheme_H