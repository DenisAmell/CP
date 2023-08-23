#ifndef POOL_H
#define POOL_H

#include "scheme.h"
#include "tree/tree_type.h"
#include "tree/avl_tree.h"
#include "tree/binary_search_tree.h"
//#include "tree/splay_tree.h"
#include "tree/red_black_tree.h"
#include "tree/associative_container.h"
#include "comparers.h"

class pool
{

private:
	memory* _allocator;
	associative_container<std::string, scheme>* _pool;
	tree_type _tree_type;

public:
	pool(memory* allocator = nullptr, tree_type tree_type = tree_type::RED_BLACK_TREE) : _allocator(allocator), _tree_type(tree_type)
	{
		switch (tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			_pool = new binary_search_tree<std::string, scheme, stdstring_comparer>();
			break;
		case tree_type::RED_BLACK_TREE:
			_pool = new red_black_tree<std::string, scheme, stdstring_comparer>();
			break;
		case tree_type::AVL_TREE:
			_pool = new avl_tree<std::string, scheme, stdstring_comparer>();
			break;
			/*case tree_type::SPALY_TREE:
				_pool = new splay_tree<std::string, scheme, stdstring_comparer>();
				break*/;
		}
	}

	~pool()
	{
		delete _pool;
	}

public:
	void add(std::string const& key, scheme&& target)
	{
		_pool->insert(key, std::move(target));
	}

	void remove(std::string const& key)
	{
		_pool->remove(key);
	}

	scheme& find(std::string const& scheme_name) const
	{
		return _pool->find(scheme_name);
	}

	bool find_to_string(std::string const& scheme_name) const
	{
		return _pool->find_to_string(scheme_name);
	}

	memory* get_allocator() const
	{
		return _allocator;
	}

public:
	pool(const pool& other) : _allocator(other._allocator), _tree_type(other._tree_type)
	{
		switch (_tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			_pool = new binary_search_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<binary_search_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
			break;
		case tree_type::RED_BLACK_TREE:
			_pool = new red_black_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<red_black_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
			break;
		case tree_type::AVL_TREE:
			_pool = new avl_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<avl_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
			break;
			//case tree_type::SPALY_TREE:
			//	_pool = new splay_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<splay_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
			//	break;
		}
	}

	pool(pool&& other) noexcept
	{
		this->_pool = other._pool;
		this->_allocator = other._allocator;
		this->_tree_type = other._tree_type;

		other._pool = nullptr;
		other._allocator = nullptr;
		other._tree_type = tree_type::RED_BLACK_TREE;
	}

	pool& operator=(const pool& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete this->_pool;

		if (this->_allocator != other._allocator)
		{
			delete this->_allocator;
			this->_allocator = other._allocator;
		}

		//this->_pool = new red_black_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<red_black_tree<std::string, scheme, stdstring_comparer>*>(other._pool));

		switch (_tree_type) {
		case tree_type::BINARY_SEARCH_TREE:
			this->_pool = new binary_search_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<binary_search_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
			break;
		case tree_type::RED_BLACK_TREE:
			this->_pool = new red_black_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<red_black_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
			break;
		case tree_type::AVL_TREE:
			this->_pool = new avl_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<avl_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
			break;
			/*case tree_type::SPALY_TREE:
				this->_pool = new splay_tree<std::string, scheme, stdstring_comparer>(*reinterpret_cast<splay_tree<std::string, scheme, stdstring_comparer>*>(other._pool));
				break;*/
		}

		this->_tree_type = other._tree_type;


		return *this;
	}

	pool& operator=(pool&& other) noexcept
	{
		if (this == &other)
		{
			return *this;
		}

		delete this->_pool;
		delete this->_allocator;

		this->_pool = other._pool;
		this->_allocator = other._allocator;
		this->_tree_type = other._tree_type;

		other._pool = nullptr;
		other._allocator = nullptr;
		other._tree_type = tree_type::RED_BLACK_TREE;

		return *this;
	}
};

#endif // POOL_H