#ifndef REQUEST_HANDLER_WITH_COMMAND_H
#define REQUEST_HANDLER_WITH_COMMAND_H

#include "abstract_handler.h"
#include "commands/command.h"

class request_handler_with_command : public abstract_handler
{
public:
    request_handler_with_command(command *target_action) : _target_action(target_action){};
    ~request_handler_with_command() { delete _target_action; }
    request_handler_with_command(request_handler_with_command const &) = delete;
    request_handler_with_command(request_handler_with_command &&) = delete;
    request_handler_with_command &operator=(request_handler_with_command const &) = delete;
    request_handler_with_command &operator=(request_handler_with_command &&) = delete;

public:
    bool handle(std::string const &request) const noexcept;

private:
    command *_target_action;
};

bool request_handler_with_command::handle(std::string const &request) const noexcept
{
    if (!_target_action->can_execute(request))
    {
        if (abstract_handler::_next_hadler == nullptr)
        {
            return false;
        }

        return abstract_handler::_next_hadler->handle(request);
    }

    _target_action->execute(request);
    return true;
}

#endif // REQUEST_HANDLER_WITH_COMMAND_H