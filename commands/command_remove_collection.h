#ifndef COMMAND_remove_collection_H
#define COMMAND_remove_collection_H

#include "command.h"

class remove_collection: public command
{
    public:
        virtual ~remove_collection() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_remove_collection_H