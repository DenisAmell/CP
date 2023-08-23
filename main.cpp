#include <iostream>
#include "database_singleton.h"
// #include "abstract_handler.h"
// #include "commands/command.h"
#include "commands/command_add_pool.h"
#include "commands/command_add_scheme.h"
#include "commands/command_add_collection.h"
#include "commands/command_add_data.h"
#include "commands/command_get_data.h"
#include "commands/command_remove_pool.h"
#include "commands/command_remove_scheme.h"
#include "commands/command_remove_collection.h"
#include "commands/command_remove_data.h"
#include "commands/command_update_data.h"
#include "commands/command_get_data_between.h"
#include <fstream>
#include "request_handler_with_command_chain.h"
#include "tree/tree_type.h"

int main(int argc, char* argv[])
{

	database_singleton* db = new database_singleton();

	std::string command;

	request_handler_with_command_chain<std::string> chain;
	chain.add_handler(new command_add_pool())
		.add_handler(new command_add_scheme())
		.add_handler(new command_add_collection())
		.add_handler(new command_add_data())
		.add_handler(new command_get_data())
		.add_handler(new command_remove_pool())
		.add_handler(new command_remove_scheme())
		.add_handler(new command_remove_collection())
		.add_handler(new command_remove_data())
		.add_handler(new command_update_data())
		.add_handler(new command_get_data_between());


	try {

		while (true) {
			size_t number_menu = 0;
			std::cout << "\tMENU" << std::endl;
			std::cout << "=================================" << std::endl;
			std::cout << "1. From read to console" << std::endl;
			std::cout << "2. From read to file" << std::endl;
			std::cout << "3. Exit" << std::endl;
			std::cout << "Enter: ";
			std::cin >> number_menu;


			if (number_menu == 1) {
				while (true) {

					std::getline(std::cin, command);

					if (command.starts_with("-1")) break;

					if (!chain.handle(command) && command != "")
					{
						std::cout << "[DATA BASE] command can't be executed" << std::endl
							<< std::endl;
					}

				}
			}
			else if (number_menu == 2) {
				std::string file_name;
				std::cout << "Enter name file ";
				std::cin >> file_name;
				std::ifstream file(file_name);
				if (file.is_open())
				{
					while (std::getline(file, command))
					{
						if (!chain.handle(command))
						{
							std::cout << "[DATA BASE] command can't be executed" << std::endl
								<< std::endl;
						}
					}
				}
				else
				{
					std::cout << "File with name:" << file_name << " can't be opened" << std::endl;
					continue;
				}

			}
			else if (number_menu == 3) break;
			else
				throw std::invalid_argument::invalid_argument("Error input!");

		}
	}
	catch (std::invalid_argument const& ex) {
		std::cout << ex.what() << std::endl;
	}



	// db->add_pool("aboba", allocator_type::border_descriptors, 1000000, memory::allocate_mode::first_fit);

	// db->add_scheme("aboba", "lol");

	// db->add_collection("aboba", "lol", "gg");

	// db->add_data("aboba", "lol", "gg", 1, 4, reporting_format::exam, "fundi", "Ivanov", "Ivan", "Ivsnovich", "1.05.2022", "9:00", 4);

	// db->add_pool("aboba2", allocator_type::border_descriptors, 1000000, memory::allocate_mode::first_fit);

	// db->add_scheme("aboba2", "lol2");

	// db->add_collection("aboba2", "lol2", "gg2");

	// db->add_data("aboba2", "lol2", "gg2", 1, 4, reporting_format::exam, "fundi", "Ivanov", "Ivan", "Ivsnovich", "1.05.2022", "9:00", 4);

	// key data_key = {1, 4, reporting_format::exam, "fundi"};

	// db->get_data("aboba", "lol", "gg", &data_key);

	// db->update_date("aboba", "lol", "gg", &data_key, "Petrov", "Petr", "Petrovich", "2.06.2022", "10:00", 4);

	// db->get_data("aboba", "lol", "gg", &data_key);

	// abstract_handler<student_definition> *db = new database_singleton<int, std::string, key_comparer>();

	// std::string command;

	// std::ifstream file("../tests/file_to_test.txt");

	// while (std::getline(file, command))
	// {
	//     db->handle_request(command);
	// }

	// delete db;

	// getchar();

	return 0;
}