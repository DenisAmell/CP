#ifndef COMMAND_remove_pool_H
#define COMMAND_remove_pool_H

#include "command.h"

class remove_pool: public command
{
    public:
        virtual ~remove_pool() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_remove_pool_H