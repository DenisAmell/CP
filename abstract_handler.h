#ifndef ABSTRACT_HANDLER_H
#define ABSTRACT_HANDLER_H

class abstract_handler
{
public:
    abstract_handler *_next_hadler;

public:
    abstract_handler() : _next_hadler(nullptr){};
    virtual ~abstract_handler() = default;

public:
    virtual bool handle(std::string const &) const noexcept = 0;
};

#endif // ABSTRACT_HANDLER_H