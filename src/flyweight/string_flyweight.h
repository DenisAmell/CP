#ifndef STRING_FLYWEIGHT_H
#define STRING_FLYWEIGHT_H
#include <string>

class string_flyweight {
private:
    std::string _value;

public:
    std::string * get_value() {
        return &_value;
    }

    void set_value(const std::string& value) {
        _value = value;
    }
};


#endif // STRING_FLYWEIGHT_H
