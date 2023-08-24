#ifndef REQUEST_HANDLER_WITH_COMMAND_CHAIN_H
#define REQUEST_HANDLER_WITH_COMMAND_CHAIN_H

#include "request_handler_with_command.h"

class request_handler_with_command_chain
{
public:
    request_handler_with_command_chain() : _first_handler(nullptr), _last_handler(nullptr){};
    ~request_handler_with_command_chain()
    {
        while (_first_handler != nullptr)
        {
            _last_handler = _first_handler;
            _first_handler = _first_handler->_next_hadler;
            delete _last_handler;
        }
    };
    request_handler_with_command_chain(request_handler_with_command_chain const &) = delete;
    request_handler_with_command_chain(request_handler_with_command_chain &&) = delete;
    request_handler_with_command_chain &operator=(request_handler_with_command_chain const &) = delete;
    request_handler_with_command_chain &operator=(request_handler_with_command_chain &&) = delete;

public:
    bool handle(std::string const &request) const noexcept;
    request_handler_with_command_chain &add_handler(command *cmd);

private:
    abstract_handler *_first_handler;
    abstract_handler *_last_handler;
};

bool request_handler_with_command_chain::handle(std::string const &request) const noexcept
{
    if (_first_handler == nullptr)
        return false;
    else
        return _first_handler->handle(request);
}

request_handler_with_command_chain &request_handler_with_command_chain::add_handler(command *cmd)
{
    if (_first_handler != nullptr)
    {
        _last_handler = _last_handler->_next_hadler = new request_handler_with_command(cmd);
    }
    else
        _last_handler = _first_handler = new request_handler_with_command(cmd);

    return *this;
}

#endif // REQUEST_HANDLER_WITH_COMMAND_CHAIN_H