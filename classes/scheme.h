#ifndef SCHEME_H
#define SCHEME_H

#include "memory/memory.h"
#include "classes/collection.h"
#include "../comparer.h"
#include "logger_singleton.h"
#include "../trees/trees_type.h"
#include "trees/BST/binary_search_tree.h"
#include "trees/AVL/avl_tree.h"
#include "trees/RB/red_black_tree.h"
// #include "trees/SPLAY/splay_tree.h"
#include <iostream>

class scheme
{
	friend class database_singleton;

private:
	associative_container<std::string, collection>* _scheme;
	//trees_type _trees_type;

public:
	scheme(trees_type trees_type = trees_type::RB) :
		_scheme(new red_black_tree<std::string, collection, string_comparer>(nullptr, logger_singleton::get_instance()->get_logger()))

	{
		//switch (trees_type)
		//{
		//case trees_type::AVL:
		//	_scheme = new avl_tree<std::string, collection, string_comparer>(nullptr, logger_singleton::get_instance()->get_logger());
		//	break;
		//case trees_type::RB:
		//	_scheme = new red_black_tree<std::string, collection, string_comparer>(nullptr, logger_singleton::get_instance()->get_logger());
		//	break;
		//	// case trees_type::SPLAY:
		//	// 	_scheme = new splay_tree<std::string, collection, string_comparer>(nullptr, logger_singleton::get_instance()->get_logger());
		//	// 	break;
		//case trees_type::BST:
		//	_scheme = new binary_search_tree<std::string, collection, string_comparer>();
		//	break;
		//}
		logger_singleton::get_instance()->get_logger()->log("Scheme constructor", logger::severity::trace);
	}
	~scheme()
	{
		logger_singleton::get_instance()->get_logger()->log("Scheme distructor", logger::severity::trace);

		delete _scheme;
	}

	void add(std::string const& name_collection, collection&& collection);
	collection& find(std::string const& name_collection);
	bool find_to_string(std::string const& name_collection);
	void remove(std::string const& name_collection);

public:
	scheme(scheme const& other) :
		_scheme(new red_black_tree<std::string, collection, string_comparer>(*reinterpret_cast<red_black_tree<std::string, collection, string_comparer>*>(other._scheme)))
	{
		//switch (_trees_type)
		//{
		//case trees_type::AVL:
		//	_scheme = new avl_tree<std::string, collection, string_comparer>(*reinterpret_cast<avl_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	break;
		//case trees_type::RB:
		//	_scheme = new red_black_tree<std::string, collection, string_comparer>(*reinterpret_cast<red_black_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	break;
		//	// case trees_type::SPLAY:
		//	// 	_scheme = new splay_tree<std::string, collection, string_comparer>(*reinterpret_cast<splay_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	// 	break;
		//case trees_type::BST:
		//	_scheme = new binary_search_tree<std::string, collection, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	break;
		//}
	}

	scheme& operator=(scheme const& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete this->_scheme;
		this->_scheme = new red_black_tree<std::string, collection, string_comparer>(*reinterpret_cast<red_black_tree<std::string, collection, string_comparer> *>(other._scheme));


		//switch (_trees_type)
		//{
		//case trees_type::AVL:
		//	this->_scheme = new avl_tree<std::string, collection, string_comparer>(*reinterpret_cast<avl_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	break;
		//case trees_type::RB:
		//	this->_scheme = new red_black_tree<std::string, collection, string_comparer>(*reinterpret_cast<red_black_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	break;
		//	// case trees_type::SPLAY:
		//	// 	this->_scheme = new splay_tree<std::string, collection, string_comparer>(*reinterpret_cast<splay_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	// 	break;
		//case trees_type::BST:
		//	this->_scheme = new binary_search_tree<std::string, collection, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, collection, string_comparer> *>(other._scheme));
		//	break;
		//}
		// this->_trees_type = other._trees_type;

		return *this;
	}

	scheme(scheme&& other) noexcept
	{
		this->_scheme = other._scheme;
		other._scheme = nullptr;
		/*this->_trees_type = other._trees_type;
		other._trees_type = trees_type::RB;*/
	}

	scheme& operator=(scheme&& other) noexcept
	{

		if (this == &other)
		{
			return *this;
		}

		delete this->_scheme;

		this->_scheme = other._scheme;
		other._scheme = nullptr;

		//this->_trees_type = other._trees_type;
		//other._trees_type = trees_type::RB;

		return *this;
	}
};

void scheme::add(std::string const& name_collection, collection&& collection)
{
	_scheme->insert(name_collection, std::move(collection));
}

collection& scheme::find(std::string const& name_collection)
{
	return _scheme->find(name_collection);
}

bool scheme::find_to_string(std::string const& name_collection)
{
	return _scheme->find_to_string(name_collection);
}

void scheme::remove(std::string const& name_collection)
{
	_scheme->remove(name_collection);
}

#endif // SCHEME_H