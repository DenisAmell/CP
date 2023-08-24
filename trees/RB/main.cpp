#include "red_black_tree.h"
#include "../../allocators/memory_list/memory_list.h"
#include "../BST/binary_search_tree.h"
#include <iostream>

class key_comparer
{
public:
	int operator()(int first, int second)
	{
		return first - second;
	}

	int operator()(std::string first, std::string second)
	{
		if (first > second)
			return 1;
		else if (first < second)
			return -1;
		else
			return 0;
	}
};

int main()
{
	logger_builder* builder = new logger_builder_concrete();
	logger* log = builder
		->add_stream("file1.txt", logger::severity::trace)
		->add_stream("file2.txt", logger::severity::debug)
		->construct();

	memory* allocator = new memory_list(nullptr, log, 10000, memory::allocate_mode::first_fit);

	auto* rb_tree = new red_black_tree<int, std::string, key_comparer>(allocator, log);

	// // *rb_tree += associative_container<int, std::string>::key_and_value_pair{3, std::move(std::string("1234"))};
	rb_tree->insert(1, "a");
	rb_tree->prefix_traverse();
	std::cout << std::endl;
	rb_tree->insert(25, "b");
	rb_tree->prefix_traverse();
	std::cout << std::endl;
	rb_tree->insert(14, "x");
	rb_tree->prefix_traverse();
	std::cout << std::endl;
	rb_tree->insert(4, "g");
	rb_tree->prefix_traverse();
	std::cout << std::endl;
	rb_tree->insert(16, "l");
	rb_tree->prefix_traverse();
	std::cout << std::endl;
	rb_tree->remove(14);
	rb_tree->prefix_traverse();
	std::cout << std::endl;

	// auto tree = *reinterpret_cast<binary_search_tree<int, std::string, key_comparer> *>(rb_tree);
	// auto end_infix = tree.end_infix();
	// for (auto it = tree.begin_infix(); it != end_infix; ++it)
	// {
	//     for (auto i = 0; i < std::get<0>(*it); i++)
	//     {
	//         std::cout << "  ";
	//     }
	//     std::cout << "Key = \"" << std::get<1>(*it) << "\", Value = \"" << std::get<2>(*it) << "\"" << std::endl;
	// }
	// std::cout << std::endl;

	// delete rb_tree;
	// delete allocator;
	// delete log;
	// delete builder;
}