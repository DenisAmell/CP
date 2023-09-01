#ifndef POOL_H
#define POOL_H

#include "../memory/memory.h"
#include "../trees/BST/associative_container.h"
#include "../trees/BST/binary_search_tree.h"
#include "../classes/scheme.h"
#include "../comparer.h"
#include "../logger_singleton.h"
#include "../trees/trees_type.h"
#include "../trees/BST/binary_search_tree.h"
#include "../trees/AVL/avl_tree.h"
#include "../trees/RB/red_black_tree.h"
#include "../trees/SPLAY/splay_tree.h"

class pool
{
private:
	memory* _allocator;
	associative_container<std::string, scheme>* _pool;
	trees_type _trees_type;

public:
	pool(memory* allocator = nullptr, trees_type trees_type = trees_type::RB) : _allocator(allocator), _trees_type(trees_type)
	{
		switch (trees_type)
		{
		case trees_type::AVL:
			_pool = new avl_tree<std::string, scheme, string_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		case trees_type::RB:
			_pool = new red_black_tree<std::string, scheme, string_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		case trees_type::SPLAY:
			_pool = new splay_tree<std::string, scheme, string_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		case trees_type::BST:
			_pool = new binary_search_tree<std::string, scheme, string_comparer>(_allocator, logger_singleton::get_instance()->get_logger());
			break;
		}
		logger_singleton::get_instance()->get_logger()->log("Pool constructor", logger::severity::trace);
	}
	~pool()
	{
		logger_singleton::get_instance()->get_logger()->log("Pool distructor", logger::severity::trace);
		delete _pool;
	}

	void add(std::string const& name_scheme, scheme&& scheme);
	scheme& find(std::string const& name_scheme);
	memory* get_allocator() { return _allocator; }
	bool find_to_string(std::string const& name_scheme);
	void remove(std::string const& name_scheme);

public:
	pool(const pool& other) : _allocator(other._allocator), _trees_type(other._trees_type)
	{
		switch (_trees_type)
		{
		case trees_type::AVL:
			_pool = new avl_tree<std::string, scheme, string_comparer>(*reinterpret_cast<avl_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		case trees_type::RB:
			_pool = new red_black_tree<std::string, scheme, string_comparer>(*reinterpret_cast<red_black_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		case trees_type::SPLAY:
			_pool = new splay_tree<std::string, scheme, string_comparer>(*reinterpret_cast<splay_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		case trees_type::BST:
			_pool = new binary_search_tree<std::string, scheme, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		}
	}

	pool(pool&& other) noexcept
	{
		this->_pool = other._pool;
		this->_allocator = other._allocator;
		this->_trees_type = other._trees_type;

		other._pool = nullptr;
		other._allocator = nullptr;
		other._trees_type = trees_type::RB;
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

		switch (_trees_type)
		{
		case trees_type::AVL:
			this->_pool = new avl_tree<std::string, scheme, string_comparer>(*reinterpret_cast<avl_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		case trees_type::RB:
			this->_pool = new red_black_tree<std::string, scheme, string_comparer>(*reinterpret_cast<red_black_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		case trees_type::SPLAY:
			this->_pool = new splay_tree<std::string, scheme, string_comparer>(*reinterpret_cast<splay_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		case trees_type::BST:
			this->_pool = new binary_search_tree<std::string, scheme, string_comparer>(*reinterpret_cast<binary_search_tree<std::string, scheme, string_comparer> *>(other._pool));
			break;
		}
		this->_trees_type = other._trees_type;

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
		this->_trees_type = other._trees_type;

		other._pool = nullptr;
		other._allocator = nullptr;
		other._trees_type = trees_type::RB;

		return *this;
	}
};

void pool::add(std::string const& name_scheme, scheme&& scheme)
{
	_pool->insert(name_scheme, std::move(scheme));
}

scheme& pool::find(std::string const& name_scheme)
{
	return _pool->find(name_scheme);
}

bool pool::find_to_string(std::string const& name_scheme)
{
	return _pool->find_to_string(name_scheme);
}

void pool::remove(std::string const& name_scheme)
{
	_pool->remove(name_scheme);
}

#endif // POOL_H