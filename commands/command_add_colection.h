#ifndef COMMAND_add_collection_H
#define COMMAND_add_collection_H

#include "command.h"

class add_collection: public command
{
    public:
        virtual ~add_collection() = default;

    public:
        bool can_execute(std::string const &) override;
        void execute(std::string const &) override;

}



#endif //COMMAND_add_collection_H