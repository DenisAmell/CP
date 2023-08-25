#include "logger.h"
#include "logger_builder_concrete.h"


int main()
{
    logger_builder* builder = new logger_builder_concrete();

    logger *constructed_logger = builder
        ->add_stream("file1.txt", logger::severity::critical)
        ->add_stream("file2.txt", logger::severity::debug)
        ->add_stream("file3.txt", logger::severity::trace)
        ->add_stream("console", logger::severity::information)
        ->from_json("pars.json")
        ->construct();

    

    logger *constructed_logger_2 = builder
        ->add_stream("file4.txt", logger::severity::error)
        ->from_json("pars.json")
        ->construct();

    constructed_logger
        ->log("allocate memory to arrey", logger::severity::information);

    constructed_logger_2
        ->log("123 kek lol", logger::severity::critical);

    delete constructed_logger_2;
    delete constructed_logger;
    delete builder;

    return 0;
}