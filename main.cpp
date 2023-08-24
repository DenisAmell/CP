#include <iostream>

#include "database_singleton.h"
#include "request_handler_with_command_chain.h"
#include "commands/command_add_pool.h"
#include "commands/command_add_scheme.h"
#include "commands/command_add_collection.h"
#include "commands/command_add_data.h"
#include "commands/command_get_data.h"
#include "commands/command_get_data_between.h"
#include "commands/command_remove_data.h"
#include "commands/command_remove_collection.h"
#include "commands/command_remove_scheme.h"
#include "commands/command_remove_pool.h"
#include "commands/command_update.h"
#include <fstream>

int main(int argc, char* argv[])
{
	database_singleton* database = new database_singleton();

	std::string command;
	request_handler_with_command_chain chain;
	chain.add_handler(new command_add_pool())
		.add_handler(new command_add_scheme())
		.add_handler(new command_add_collection())
		.add_handler(new command_add_data())
		.add_handler(new command_get_data())
		.add_handler(new command_get_data_between())
		.add_handler(new command_remove_data())
		.add_handler(new command_remove_collection())
		.add_handler(new command_remove_scheme())
		.add_handler(new command_remove_pool())
		.add_handler(new command_update());

	//std::ifstream file(argv[1]);
	std::ifstream file("../../test.txt");
	if (file.is_open())
	{
		while (std::getline(file, command))
		{
			if (!chain.handle(command))
			{
				std::cout << "command can't executed" << std::endl;
			}
		}
	}

	// database->add_pool("aboba", allocator_type::MEMORY_LIST, 100000, memory::allocate_mode::best_fit);

	// database->add_scheme("aboba", "lol");
	// database->add_collection("aboba", "lol", "gg");

	// key data_key = {5};

	// key data_key1 = {0};
	// key data_key2 = {7};
	// key data_key3 = {6};

	// value data_value = {type_of_meeting::DAILY,
	//                     format::FACE_TO_FACE,
	//                     "djalab",
	//                     "http//pizdec.lol",
	//                     "Ivan",
	//                     "Ivanov",
	//                     "Ivanovich",
	//                     "2.09.2023",
	//                     "9:00",
	//                     "gg",
	//                     "Iliy Irbitski"};

	// value data_value2 = {type_of_meeting::DAILY,
	//                      format::FACE_TO_FACE,
	//                      "djalab",
	//                      "http//pizdec.lol",
	//                      "Ivan",
	//                      "Ivanov",
	//                      "Ivanovich",
	//                      "9.09.2023",
	//                      "9:00",
	//                      "gg",
	//                      "Iliy Irbitski"};

	// database->add_data("aboba", "lol", "gg", &data_key, &data_value);
	// database->add_data("aboba", "lol", "gg", &data_key1, &data_value);
	// database->add_data("aboba", "lol", "gg", &data_key2, &data_value);
	// database->add_data("aboba", "lol", "gg", &data_key3, &data_value);
	// database->get_data_between("aboba", "lol", "gg", &data_key3, &data_key2);

	// database->update("aboba", "lol", "gg", &data_key, &data_value2);
	// database->get_data("aboba", "lol", "gg", &data_key);
	return 0;
}