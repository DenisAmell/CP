#ifndef SCHEME_H
#define SCHEME_H

#include <iostream>

#include "tree/tree_type.h"
#include "tree/avl_tree.h"
#include "tree/binary_search_tree.h"
//#include "tree/splay_tree.h"
#include "tree/red_black_tree.h"
#include "comparers.h"
#include "collection.h"

class scheme final
{

	friend class database_singlton;

private:
	memory* _allocator;
	associative_container<std::string, collection>* _scheme;
	tree_type _tree_type;


public:
	scheme(tree_type tree_type) : _tree_type(tree_type)
	{
		switch (tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			_scheme = new binary_search_tree<std::string, collection, stdstring_comparer>();
			break;
		case tree_type::RED_BLACK_TREE:
			_scheme = new red_black_tree<std::string, collection, stdstring_comparer>();
			break;
		case tree_type::AVL_TREE:
			_scheme = new avl_tree<std::string, collection, stdstring_comparer>();
			break;
			/*case tree_type::SPALY_TREE:
				_scheme = new splay_tree<std::string, collection, stdstring_comparer>();
				break;*/
		}
	}

	~scheme()
	{
		delete _scheme;
	}

public:
	void add(std::string const& collection_name, collection&& target)
	{
		return _scheme->insert(collection_name, std::move(target));
	}

	void remove(std::string const& key)
	{
	}

	collection& find(std::string const& collection_name) const
	{
		return _scheme->find(collection_name);
	}

	bool find_to_string(std::string const& collection_name) const
	{
		return _scheme->find_to_string(collection_name);
	}

public:
	scheme(scheme const& other) : _tree_type(other._tree_type)

	{
		switch (_tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			_scheme = new binary_search_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<binary_search_tree<std::string, collection, stdstring_comparer>*>(other._scheme));
			break;
		case tree_type::RED_BLACK_TREE:
			_scheme = new red_black_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<red_black_tree<std::string, collection, stdstring_comparer>*>(other._scheme));

			break;
		case tree_type::AVL_TREE:
			_scheme = new avl_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<avl_tree<std::string, collection, stdstring_comparer>*>(other._scheme));
			break;
			/*case tree_type::SPALY_TREE:
				_scheme = new splay_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<splay_tree<std::string, collection, stdstring_comparer>*>(other._scheme));
				break;*/
		}
	}

	scheme& operator=(scheme const& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete this->_scheme;

		//this->_scheme = new red_black_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<red_black_tree<std::string, collection, stdstring_comparer>*>(other._scheme));


		switch (_tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			this->_scheme = new binary_search_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<binary_search_tree<std::string, collection, stdstring_comparer>*>(other._scheme));
			break;
		case tree_type::RED_BLACK_TREE:
			this->_scheme = new red_black_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<red_black_tree<std::string, collection, stdstring_comparer>*>(other._scheme));
			break;
		case tree_type::AVL_TREE:
			this->_scheme = new avl_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<avl_tree<std::string, collection, stdstring_comparer>*>(other._scheme));
			break;
			/*	case tree_type::SPALY_TREE:
					this->_scheme = new splay_tree<std::string, collection, stdstring_comparer>(*reinterpret_cast<splay_tree<std::string, collection, stdstring_comparer>*>(other._scheme));
					break*/;
		}
		this->_tree_type = other._tree_type;


		return *this;
	}

	scheme(scheme&& other) noexcept
	{
		this->_scheme = other._scheme;
		other._scheme = nullptr;
		this->_tree_type = other._tree_type;
		other._tree_type = tree_type::RED_BLACK_TREE;
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

		this->_tree_type = other._tree_type;
		other._tree_type = tree_type::RED_BLACK_TREE;


		return *this;
	}
};

#endif // SCHEME_H