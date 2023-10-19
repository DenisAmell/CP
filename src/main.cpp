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
#include "commands/command_clean.h"
#include <fstream>

int main(int argc, char* argv[])
{
	database_singleton* database = new database_singleton();

	std::string command;
	char filename_to_save[] = "additional.txt";

	request_handler_with_command_chain chain;
	chain.add_handler(new command_add_pool(filename_to_save))
		.add_handler(new command_add_scheme(filename_to_save))
		.add_handler(new command_add_collection(filename_to_save))
		.add_handler(new command_add_data(filename_to_save))
		.add_handler(new command_get_data(filename_to_save))
		.add_handler(new command_get_data_between(filename_to_save))
		.add_handler(new command_remove_data(filename_to_save))
		.add_handler(new command_remove_collection(filename_to_save))
		.add_handler(new command_remove_scheme(filename_to_save))
		.add_handler(new command_remove_pool(filename_to_save))
		.add_handler(new command_update(filename_to_save))
        .add_handler(new command_clean());

    try
    {
        while (true)
        {
            std::string number_sub0_menu;
            std::cout << "-------~~~~~~--------" << std::endl;
            std::cout << "| Do you wish to restore some data? |" << std::endl;
            std::cout << "-------~~~~~~--------" << std::endl;
            std::cout << "1. Yes" << std::endl;
            std::cout << "2. No" << std::endl;
            std::cout << "Your choise: ";
            std::cin >> number_sub0_menu;

            if (number_sub0_menu == "1")
            {
                std::string file_restore;
                std::cout << "Enter restore filename: ";
                std::cin >> file_restore;
                std::ifstream file(file_restore);
                if (file.is_open())
                {
                    while (std::getline(file, command))
                    {
                        if (!chain.handle(command))
                        {
                            std::cout << "[MAIN] command can't be executed" << std::endl
                                      << std::endl;
                        }
                    }
                    break;
                }
                else
                {
                    std::cout << "File with name:" << file_restore << " can't be opened" << std::endl;
                    continue;
                }
            }

            if (number_sub0_menu == "2") break;
        }
    }
    catch (std::invalid_argument const& ex)
    {
        std::cout << ex.what() << std::endl;
    }

	try
    {
		while (true)
        {
			std::string number_menu;
			std::cout << "-------~~~~~~--------" << std::endl;
			std::cout << "|\tMENU\t    |" << std::endl;
			std::cout << "-------~~~~~~--------" << std::endl;
			std::cout << "~~  Please specify the way in which the input data will be supplied  ~~" << std::endl;
			std::cout << "1. From the console" << std::endl;
			std::cout << "2. From the file" << std::endl;
            std::cout << "3. Back up" << std::endl;
            std::cout << "4. Restore" << std::endl;
			std::cout << "5. Exit from MENU" << std::endl;
			std::cout << "Your choise: ";
			std::cin >> number_menu;


			if (number_menu == "1") {

				std::cout << "you can enter commands (be careful when entering and try to enter correctly):" << std::endl;

				while (true) {

					std::getline(std::cin, command);

					if (command.starts_with("end")) break;

					if (!chain.handle(command) && command != "")
					{
						std::cout << "[MAIN] command can't be executed" << std::endl
							<< std::endl;
					}
				}
			}
			else if (number_menu == "2") {
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
							std::cout << "[MAIN] command can't be executed" << std::endl
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
            else if (number_menu == "3") //back-up
            {
                std::string file_name;
                std::cout << "Enter name file for back-up ";
                std::cin >> file_name;
                std::ifstream infile("additional.txt", std::ios::in);
                std::ofstream outfile(file_name, std::ios::out);
                std::string line;
                if (outfile.is_open())
                {
                    while (std::getline(infile, line))
                        outfile << line << std::endl;
                }
                else
                {
                    std::cout << "File with name:" << file_name << " can't be opened" << std::endl;
                    continue;
                }

                infile.close();
                outfile.close();
            }
            else if (number_menu == "4") //restore
            {
                std::ofstream file_add("additional.txt", std::ios::trunc);
                std::string file_restore;
                std::cout << "Enter restore filename: ";
                std::cin >> file_restore;
                std::ifstream file(file_restore);
                if (file.is_open())
                {
                    while (std::getline(file, command))
                    {
                        if (!chain.handle(command))
                        {
                            std::cout << "[MAIN] command can't be executed" << std::endl
                                      << std::endl;
                        }
                    }
                }
                else
                {
                    std::cout << "File with name:" << file_restore << " can't be opened" << std::endl;
                    continue;
                }
            }
			else if (number_menu == "5")
            {
                std::string number_sub2_menu;
                while(true)
                {

                    std::cout << "-------~~~~~~--------" << std::endl;
                    std::cout << "| Do you wish to back-up? |" << std::endl;
                    std::cout << "-------~~~~~~--------" << std::endl;
                    std::cout << "1. Yes" << std::endl;
                    std::cout << "2. No" << std::endl;
                    std::cout << "Your choise: ";
                    std::cin >> number_sub2_menu;

                    if (number_sub2_menu == "1")
                    {
                        std::string file_name;
                        std::cout << "Enter name file ";
                        std::cin >> file_name;
                        std::ifstream infile("additional.txt", std::ios::in);
                        std::ofstream outfile(file_name, std::ios::out);
                        std::string line;
                        if (outfile.is_open())
                        {
                            while (std::getline(infile, line))
                                outfile << line << std::endl;
                        }
                        else
                        {
                            std::cout << "File with name:" << file_name << " can't be opened" << std::endl;
                            continue;
                        }

                        infile.close();
                        outfile.close();

                        infile.open("additional.txt", std::ios::trunc);
                        infile.close();
                        break;
                    }

                    if (number_sub2_menu == "2")
                    {
                        std::ofstream file_add("additional.txt", std::ios::trunc);
                        break;
                    }
                }
                break;
            }
			else
				std::cout << "Error input!" << std::endl;
		}
	}
	catch (std::invalid_argument const& ex)
    {
		std::cout << ex.what() << std::endl;
	}

	//std::ifstream file(argv[1]);
	/*std::ifstream file("../../test.txt");
	if (file.is_open())
	{
		while (std::getline(file, command))
		{
			if (!chain.handle(command))
			{
				std::cout << "command can't executed" << std::endl;
			}
		}
	}*/

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