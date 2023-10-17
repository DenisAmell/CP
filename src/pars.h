#ifndef PARS_H
#define PARS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <regex>
#include <string>
#include "trees/trees_type.h"
#include "collections/work_calendar.h"
#include "allocators/allocator_type.h"
#include "memory/memory.h"

// TODO: вынести в класс
std::vector<std::string> split(std::string const& target, char delim)
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

trees_type trees_type_convert(std::string& tree_type_to_convert)
{
	if (tree_type_to_convert.starts_with("avl"))
		return trees_type::AVL;
	if (tree_type_to_convert.starts_with("bst"))
		return trees_type::BST;
	if (tree_type_to_convert.starts_with("rb"))
		return trees_type::RB;
	if (tree_type_to_convert.starts_with("splay"))
		return trees_type::SPLAY;
	throw std::logic_error("Not found tree type");
}

std::string trees_type_convert_to_string(trees_type tree_type_to_convert)
{
	std::string tree_type_string;
	if (tree_type_to_convert == trees_type::AVL)
		return tree_type_string = "avl";
	if (tree_type_to_convert == trees_type::BST)
		return tree_type_string = "bst";
	if (tree_type_to_convert == trees_type::RB)
		return tree_type_string = "rb";
	if (tree_type_to_convert == trees_type::SPLAY)
		return tree_type_string = "splay";
	throw std::logic_error("Input error tree type");
}

type_of_meeting type_of_meeting_convert(std::string& type_of_meeting_to_convert)
{
	if (type_of_meeting_to_convert == "daily")
		return type_of_meeting::DAILY;
	if (type_of_meeting_to_convert == "based_on_results_of_reporting_period")
		return type_of_meeting::BASED_ON_RESULTS_OF_REPORTING_PERIOD;
	if (type_of_meeting_to_convert == "interview")
		return type_of_meeting::INTERVIEW;
	if (type_of_meeting_to_convert == "corporate")
		return type_of_meeting::CORPORATE;
	throw std::logic_error("Not found type of meeting");
}

std::string type_of_meeting_convert_to_string(type_of_meeting type_of_meeting_to_convert)
{
	std::string type_of_meeting_string;
	if (type_of_meeting_to_convert == type_of_meeting::DAILY)
		return type_of_meeting_string = "daily";
	if (type_of_meeting_to_convert == type_of_meeting::BASED_ON_RESULTS_OF_REPORTING_PERIOD)
		return type_of_meeting_string = "based_on_results_of_reporting_period";
	if (type_of_meeting_to_convert == type_of_meeting::INTERVIEW)
		return type_of_meeting_string = "interview";
	if (type_of_meeting_to_convert == type_of_meeting::CORPORATE)
		return type_of_meeting_string = "corporate";
	throw std::logic_error("Input error type of meeting");
}

format format_convert(std::string& format_to_convert)
{
	if (format_to_convert == "face_to_face")
		return format::FACE_TO_FACE;
	if (format_to_convert == "remote")
		return format::REMOTE;
	throw std::logic_error("Not found format of meeting");
}

std::string format_convert_to_string(format format_to_convert)
{
	std::string format_to_convert_string;
	if (format_to_convert == format::FACE_TO_FACE)
		return format_to_convert_string = "face_to_face";
	if (format_to_convert == format::REMOTE)
		return format_to_convert_string = "remote";
	throw std::logic_error("Input error format of meeting");
}

allocator_type allocator_type_convert(std::string& allocator_type_to_convert)
{
	if (allocator_type_to_convert == "memory_list")
		return allocator_type::MEMORY_LIST;
	if (allocator_type_to_convert == "buddies_system")
		return allocator_type::BUDDIES_SYSTEM;
	if (allocator_type_to_convert == "border_descriptors")
		return allocator_type::BORDER_DESCRIPTORS;
	throw std::logic_error("Not found allocator type");
}

std::string allocator_type_convert_to_string(allocator_type allocator_type_to_convert)
{
	std::string allocator_type_string;
	if (allocator_type_to_convert == allocator_type::MEMORY_LIST)
		return allocator_type_string = "memory_list";
	if (allocator_type_to_convert == allocator_type::BUDDIES_SYSTEM)
		return allocator_type_string = "buddies_system";
	if (allocator_type_to_convert == allocator_type::BORDER_DESCRIPTORS)
		return allocator_type_string = "border_descriptors";
	throw std::logic_error("Input error allocator type");
}

memory::allocate_mode allocate_mode_convert(std::string& allocate_mode_to_convert)
{
	if (allocate_mode_to_convert == "first_fit")
		return memory::allocate_mode::first_fit;
	if (allocate_mode_to_convert == "best_fit")
		return memory::allocate_mode::best_fit;
	if (allocate_mode_to_convert == "worst_fit")
		return memory::allocate_mode::worst_fit;
	throw std::logic_error("Not found allocate mode");
}

std::string convert_allocate_mode_to_string(memory::allocate_mode allocate_mode_to_convert)
{
	std::string allocate_mode_string;
	if (allocate_mode_to_convert == memory::allocate_mode::first_fit)
		return allocate_mode_string = "first_fit";
	if (allocate_mode_to_convert == memory::allocate_mode::best_fit)
		return allocate_mode_string = "best_fit";
	if (allocate_mode_to_convert == memory::allocate_mode::worst_fit)
		return allocate_mode_string = "worst_fit";
	throw std::logic_error("Input error allocate mode");
}

//валидация по айдишнику\продолжительности на то что это должно быть целшое и неотрицательное
unsigned int is_unsigned_convert(std::string& current_line)
{
	size_t check_size = -1;
	try
	{
		std::stoi(current_line, &check_size);
	}
	catch (std::invalid_argument)
	{
		throw std::logic_error("pipau");
	}
	catch (std::out_of_range)
	{
		throw std::logic_error("pipau");
	}

    try
    {
        if (check_size != current_line.size())
        {

        }
    }
	catch(std::exception e)
    {
		e.what();
	}
	return std::stoi(current_line);
}

std::string empty_check(std::string& name)
{
	if (name.empty())
		throw std::logic_error("sting is emoty");
	return name;
}

//для фамилии и имени не пустые и с большой буквы
std::string name_surname_convert(std::string& name_surname_to_convert)
{
	if (name_surname_to_convert.empty())
	{
		throw std::logic_error("Name or Surname is empty");
	}
	else if (!std::isupper(name_surname_to_convert[0]))
	{
		throw std::logic_error("Name or Surname is not capitalized");
	}
	return name_surname_to_convert;
}

//для отчества с большой буквы
std::string middle_name_convert(std::string& middle_name_to_convert)
{
	if (!std::isupper(middle_name_to_convert[0]))
		throw std::logic_error("Name or Surname is not capitalized");
	return middle_name_to_convert;
}

//дата встречи
std::string data_convert(std::string& data_to_convert)
{
	std::vector<std::string> result = split(data_to_convert, '.');

	if (result.size() != 3)
	{
		throw std::logic_error("There is incorrect data size");
	}


	auto day = is_unsigned_convert(result[0]);
	if (day <= 0 || day > 31)
	{
		throw std::logic_error("There is incorrect day");
	}

	auto month = is_unsigned_convert(result[1]);
	if (month <= 0 || month > 12)
	{
		throw std::logic_error("There is incorrect month");
	}


	auto year = is_unsigned_convert(result[2]);
	if (year < 2023)
	{
		throw std::logic_error("There is incorrect year");
	}


	if ((year % 4 == 0 && month == 2 && day > 29)
		|| (year % 4 != 0 && month == 2 && day > 28))
	{
		throw std::logic_error("There is incorrect data of Fabruary");
	}


	if ((month == 4 || month == 6 || month == 9 || month == 11)
		&& (day > 30))
	{
		throw std::logic_error("There is incorrect day of some months (day > 30)");
	}


	return data_to_convert;
}

//время встречи
std::string time_convert(std::string& time_to_convert)
{
	std::vector<std::string> result = split(time_to_convert, ':');

	if (result.size() != 2)
	{
		throw std::logic_error("There is incorrect time size");
	}


	auto hour = is_unsigned_convert(result[0]);
	if (hour < 0 || hour > 23)
	{
		throw std::logic_error("There is incorrect hour");
	}


	auto minutes = is_unsigned_convert(result[1]);
	if (minutes < 0 || minutes > 59)
	{
		throw std::logic_error("There is incorrect minutes");
	}

	return time_to_convert;
}

#endif // PARS_H