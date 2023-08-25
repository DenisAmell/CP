#ifndef COMMAND_H
#define COMMAND_H

class command
{
    public:
        virtual ~command() = default;

    public:
        virtual bool can_execute(std::string const &) = 0;
        virtual void execute(std::string const &) = 0;

}



#endif //COMMAND_H