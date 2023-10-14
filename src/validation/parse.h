#ifndef FUNDAMENTAL_ALGO_PARSE_H
#define FUNDAMENTAL_ALGO_PARSE_H
#include <iostream>
#include <vector>
#include <map>
#include "../allocators/allocator_type.h"
#include "../memory/memory.h"
#include "../exception/doesnt_exist.h"
#include "../type_data/student_definition.h"
#include "../tree/tree_type.h"
#include <string>
#include <sstream>
//
//std::vector<std::string> chop_string_to_vector(
//    std::string::iterator const &begin,
//    std::string::iterator const &end,
//    const char delim)
//{
//    std::vector<std::string> out;
//    auto it = begin;
//    std::string lexem;
//    size_t start;
//    size_t finish = 0;
//
//    while (it != end)
//    {
//        if (*it == delim && !lexem.empty())
//        {
//            out.push_back(std::move(lexem));
//        }
//        else
//        {
//            lexem += *it;
//        }
//
//        ++it;
//    }
//
//    if (!lexem.empty())
//    {
//        out.push_back(std::move(lexem));
//    }
//
//    return out;
//}

// bool prefix_validation(std::string const &prefix, std::string const &request)
// {
//     return (request.starts_with(prefix + '(') && request.ends_with(")"));
//     // return true;
// }

std::vector<std::string> validation(std::string const& prefix, char delim)
{
	// std::string *non_const_request = const_cast<std::string *>(&request);

	// std::vector<std::string> chopped_string = chop_string_to_vector(
	//     non_const_request->begin() + std::string(prefix).length(),
	//     non_const_request->end(),
	//     ' ');
	// return chopped_string;

	std::vector<std::string> result;
	std::string token;
	std::istringstream tokenStream(prefix);
	while (std::getline(tokenStream, token, delim))
	{
		result.push_back(token);
	}
	return result;
}

std::string convert_allocator_type_to_string(allocator_type allocator_type) {
    std::string allocator_type_string;
    switch(allocator_type) {
        case allocator_type::list_memory:
            allocator_type_string = "list_memory";
            break;
        case allocator_type::global_heap:
            allocator_type_string = "global_heap";
            break;
        case allocator_type::border_descriptors:
            allocator_type_string = "border_descriptors";
            break;
        case allocator_type::buddy_allocator:
            allocator_type_string = "buddy_allocator";
            break;

    }
    return allocator_type_string;
}

std::string convert_allocator_mode_to_string(memory::allocate_mode allocate_mode) {
    std::string allocate_mode_string;
    switch(allocate_mode) {
        case memory::allocate_mode::best_fit:
            allocate_mode_string = "best_fit";
            break;
        case memory::allocate_mode::first_fit:
            allocate_mode_string = "first_fit";
            break;
        case memory::allocate_mode::worst_fit:
            allocate_mode_string = "worst_fit";
            break;
    }
    return allocate_mode_string;

}

std::string convert_tree_type_to_string(tree_type treetype) {
    std::string tree_type_string;
    switch(treetype) {
        case tree_type::RED_BLACK_TREE:
            tree_type_string = "red_black_tree";
            break;
        case tree_type::BINARY_SEARCH_TREE:
            tree_type_string = "binary_search_tree";
            break;
        case tree_type::AVL_TREE:
            tree_type_string = "avl_tree";
            break;
        case tree_type::SPALY_TREE:
            tree_type_string = "splay_tree";
            break;
    }
    return tree_type_string;

}

allocator_type string_to_allocator_type(std::string const& string_allocator_type)
{
	if (string_allocator_type == "global_heap")
		return allocator_type::global_heap;
	if (string_allocator_type == "border_descriptors")
		return allocator_type::border_descriptors;
	if (string_allocator_type == "buddy_allocator")
		return allocator_type::buddy_allocator;
	if (string_allocator_type == "list_memory")
		return allocator_type::list_memory;
	throw doesnt_exist("string_to_allocator_type");
}

unsigned int is_unsigned_with_convert(std::string& current_line)
{
	size_t check_size = -1;
	try
	{
		std::stoi(current_line, &check_size);
	}
	catch (std::invalid_argument&)
	{
		throw doesnt_exist("is_unsigned_with_convert");
	}
	catch (std::out_of_range&)
	{
		throw doesnt_exist("is_unsigned_with_convert");
	}
	if (check_size != current_line.size())
	{
		throw doesnt_exist("is_unsigned_with_convert");
	}
	return std::stoi(current_line);
}

memory::allocate_mode allocation_mode_convert(std::string& string_allocation_mode)
{
	if (string_allocation_mode == "first_fit")
		return memory::allocate_mode::first_fit;
	if (string_allocation_mode == "best_fit")
		return memory::allocate_mode::best_fit;
	if (string_allocation_mode == "worst_fit")
		return memory::allocate_mode::worst_fit;
	throw doesnt_exist("allocation_mode_convert");
}

reporting_format reporting_format_convert(std::string& string_reporting_format)
{
	if (string_reporting_format == "course_project")
		return reporting_format::course_project;
	if (string_reporting_format == "credit")
		return reporting_format::credit;
	if (string_reporting_format == "exam")
		return reporting_format::exam;
	throw doesnt_exist("reporting_format_convert");
}

unsigned int is_valid_grade(reporting_format reporting_format_for_validate, std::string& string_grade)
{
	unsigned int grade;
	try
	{
		std::stringstream size(string_grade);
		size >> grade;
		// grade = is_unsigned_with_convert(string_grade);
	}
	catch (doesnt_exist())
	{
		throw doesnt_exist("is_valid_grade");
	}
	if ((grade >= 2 && grade <= 5) &&
		((reporting_format_for_validate == reporting_format::exam) ||
			(reporting_format_for_validate == reporting_format::course_project)))
	{
		return grade;
	}
	else if ((grade == 0 || grade == 1) &&
		(reporting_format_for_validate == reporting_format::credit))
	{
		return grade;
	}
	else
	{
		throw doesnt_exist("is_valid_grade");
	}
}

#endif // FUNDAMENTAL_ALGO_PARSE_H