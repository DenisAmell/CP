#ifndef COMMAND_add_pool_H
#define COMMAND_add_pool_H

#include "command.h"

class add_pool: public command
{
    public:
        virtual ~add_pool() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_add_pool_H