#ifndef PARS_H
#define PARS_H

#include <vector>
#include <iostream>
#include <sstream>

// TODO: вынести в класс
std::vector<std::string> split(std::string const &target, char delim)
{
    std::vector<std::string> result;
    std::string token;
    std::istringstream token_stream(target);

    while (std::getline(token_stream, token, delim))
    {
        result.push_back(token);
    }

    return result;
}

#endif // PARS_H