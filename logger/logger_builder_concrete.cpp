#include "logger_builder_concrete.h"
#include "logger_concrete.h"
//#include "nlohmann-json/json-3.11.2/single_include/nlohmann/json.hpp"
#include <fstream>

//using json = nlohmann::json;

logger_builder *logger_builder_concrete::add_stream(
    std::string const &path,
    logger::severity severity)
{
    _construction_info[path] = severity;

    return this;
}
    
//logger_builder *logger_builder_concrete::from_json(
//    std::string const &name_json_file)
//{
//    std::ifstream f(name_json_file);
//    json data = json::parse(f);
//    logger::severity sever;
//    for (auto &json_stream : data.items())
//    {
//        if (json_stream.value() == "error")
//        {
//            sever = logger::severity::error;
//        }
//        if (json_stream.value() == "trace")
//        {
//            sever = logger::severity::trace;
//        }
//        if (json_stream.value() == "warning")
//        {
//            sever = logger::severity::warning;
//        }
//        if (json_stream.value() == "debug")
//        {
//            sever = logger::severity::debug;
//        }
//        if (json_stream.value() == "information")
//        {
//            sever = logger::severity::information;
//        }
//        if (json_stream.value() == "critical")
//        {
//            sever = logger::severity::critical;
//        }
//        _construction_info[json_stream.key()] = sever;
//    }
//    return this;
//}

logger *logger_builder_concrete::construct() const
{
    return new logger_concrete(_construction_info);
}
