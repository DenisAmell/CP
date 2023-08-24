#ifndef SANDBOX_CPP_BINARY_SEARCH_TREE_H
#define SANDBOX_CPP_BINARY_SEARCH_TREE_H

#include <stack>
#include "associative_container.h"
#include "../../logger/logger.h"
#include "../../logger/logger_holder.h"
#include "../../memory/memory.h"
#include "../../memory/memory_holder.h"
#include <vector>
#include <list>

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class binary_search_tree : public associative_container<tkey, tvalue>,
	private logger_holder,
	protected memory_holder
{

protected:
	struct node
	{
		tkey key;

		tvalue value;

		node* left_subtree_address;

		node* right_subtree_address;

		explicit node(tkey new_key, tvalue&& new_value) : key(new_key), value(std::move(new_value))
		{
		}

		virtual ~node() = default;
	};

public:
	class prefix_iterator final
	{

	private:
		node* _current_node;
		std::stack<node*> _way;

	public:
		explicit prefix_iterator(
			node* tree_root);

	public:
		bool operator==(
			prefix_iterator const& other) const;

		bool operator!=(
			binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator const& other) const;

		prefix_iterator& operator++();

		prefix_iterator operator++(
			int not_used);

		std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;
	};

	class infix_iterator final
	{

	private:
		binary_search_tree<tkey, tvalue, tkey_comparer>::node* _current_node;
		std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node*> _way;

	public:
		explicit infix_iterator(
			node* tree_root);

	public:
		bool operator==(
			infix_iterator const& other) const;

		bool operator!=(
			binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const& other) const;

		infix_iterator& operator++();

		infix_iterator operator++(
			int not_used);

		std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;
	};

	class postfix_iterator final
	{

	private:
		node* _current_node;
		std::stack<node*> _way;

	public:
		explicit postfix_iterator(
			node* tree_root);

	public:
		bool operator==(
			postfix_iterator const& other) const;

		bool operator!=(
			binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const& other) const;

		postfix_iterator& operator++();

		postfix_iterator operator++(
			int not_used);

		std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;
	};

protected:
	class insertion_template_method : protected memory_holder,
		protected logger_holder
	{
		friend class binary_search_tree<tkey, tvalue, tkey_comparer>;
		binary_search_tree<tkey, tvalue, tkey_comparer>* _tree;

	public:
		insertion_template_method(binary_search_tree<tkey, tvalue, tkey_comparer>* tree) : _tree(tree) {};

		virtual ~insertion_template_method() = default;

	public:
		void insert(
			tkey const& key,
			tvalue&& value,
			node*& tree_root_address);

		void update(
			tkey const& key,
			tvalue&& value,
			node*& tree_root_address);

	protected:
		virtual void insert_inner(
			tkey const& key,
			tvalue&& value,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		void update_inner(
			tkey const& key,
			tvalue&& value,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

	protected:
		virtual void before_insert_inner();

		virtual void after_insert_inner(
			tkey const& key,
			binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		virtual size_t get_size_node();
		virtual void initialization_node(binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node, tkey const& key, tvalue&& value);
		memory* get_memory() const override;
		logger* get_logger() const override;
		virtual void inject_additional_data(
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* from,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* to) const;
		virtual void initialize_node_additional_data(
			binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node) const;
		virtual void constructor_node(binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node,
			tkey const& key,
			tvalue&& value) const;
	};

	class reading_template_method : protected logger_holder
	{
		friend class binary_search_tree<tkey, tvalue, tkey_comparer>;
		binary_search_tree<tkey, tvalue, tkey_comparer>* _tree;

	public:
		reading_template_method(binary_search_tree<tkey, tvalue, tkey_comparer>* tree) : _tree(tree) {};

		virtual ~reading_template_method() = default;

	public:
		bool read(
			typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value,
			node*& tree_root_address);

		tvalue& read(
			tkey const& key,
			node*& tree_root_address);

		bool find_in(
			tkey const& key,
			node*& tree_root_address);

		tvalue& find(
			tkey const& key,
			node*& tree_root_address);

		bool read_to_string(
			tkey const& key,
			node*& tree_root_address);

	private:
		tvalue& read_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		bool read_inner(
			typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		tvalue& find_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		bool find_in_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		bool read_to_string_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

	protected:
		virtual void before_read_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		virtual void after_read_inner(
			typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		logger* get_logger() const override;
	};

	class removing_template_method : protected memory_holder,
		protected logger_holder
	{
		binary_search_tree<tkey, tvalue, tkey_comparer>* _tree;

	public:
		removing_template_method(binary_search_tree<tkey, tvalue, tkey_comparer>* tree) : _tree(tree) {};

		virtual ~removing_template_method() = default;

	public:
		tvalue remove(
			tkey const& key,
			node*& tree_root_address);

		std::tuple<tkey, tvalue> remove_node(
			tkey const& key,
			binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_root_address);

	protected:
		virtual tvalue remove_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		virtual std::tuple<tkey, tvalue> remove_node_inner(
			const tkey& key,
			node*& subtree_root_address,
			std::list<node**>& path_to_subtree_root_exclusive);

	protected:
		virtual void before_remove_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		virtual void after_remove_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::stack<node**>& path_to_subtree_root_exclusive);

		virtual void after_remove_inner(
			tkey const& key,
			node*& subtree_root_address,
			std::list<node**>& path_to_subtree_root_exclusive);

		memory* get_memory() const override;
		logger* get_logger() const override;

	private:
		template <typename T>
		void swap(T** value, T** another_value)
		{
			T* value_ptr_copy = *value;
			*value = *another_value;
			*another_value = value_ptr_copy;
		}

		void swap_nodes(node** one_node, node** another_node);
	};

protected:
	node* _root;
	memory* _allocator;
	logger* _logger;
	insertion_template_method* _insertion;
	reading_template_method* _reading;
	removing_template_method* _removing;
	tkey_comparer _comparator;

protected:
	node* get_root() const noexcept { return _root; }

protected:
	explicit binary_search_tree(
		insertion_template_method* insertion,
		reading_template_method* reading,
		removing_template_method* removing,
		memory* allocator = nullptr,
		logger* logger = nullptr);

public:
	explicit binary_search_tree(
		memory* allocator = nullptr,
		logger* logger = nullptr);

	binary_search_tree(
		binary_search_tree const& other);

	binary_search_tree(
		binary_search_tree&& other) noexcept;

	binary_search_tree& operator=(
		binary_search_tree const& other);

	binary_search_tree& operator=(
		binary_search_tree&& other) noexcept;

	~binary_search_tree();

public:
	void insert(
		tkey const& key,
		tvalue&& value) override;

	bool get(
		typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value) final;

	tvalue& find(
		tkey const& key) final;

	tvalue remove(
		tkey const& key) override;

	std::tuple<tkey, tvalue> remove_node(
		tkey const& key) override;

	bool find_to_string(
		tkey const& key) override;

	bool find_in(
		tkey const& key) override;

	void update(
		tkey const& key,
		tvalue&& value) override;

	std::vector<tvalue> get_data_between(
		tkey const& left_key,
		tkey const& right_key) override;

private:
	logger* get_logger() const final;
	memory* get_memory() const override;

protected:
	node* copy() const;

	void move(binary_search_tree<tkey, tvalue, tkey_comparer>&& other);

	void clear();

private:
	node* copy_inner(node* to_copy) const;

	void clear_inner(node* to_clear) const;

protected:
	void left_rotation(binary_search_tree<tkey, tvalue, tkey_comparer>::node** sub_tree_root);
	void right_rotation(binary_search_tree<tkey, tvalue, tkey_comparer>::node** sub_tree_root);

public:
	prefix_iterator begin_prefix() const noexcept;

	prefix_iterator end_prefix() const noexcept;

	infix_iterator begin_infix() const noexcept;

	infix_iterator end_infix() const noexcept;

	postfix_iterator begin_postfix() const noexcept;

	postfix_iterator end_postfix() const noexcept;
};

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::left_rotation(binary_search_tree<tkey, tvalue, tkey_comparer>::node** sub_tree_root)
{
	node* tmp = *(sub_tree_root);
	(*sub_tree_root) = (*sub_tree_root)->right_subtree_address;
	tmp->right_subtree_address = (*sub_tree_root)->left_subtree_address;
	(*sub_tree_root)->left_subtree_address = tmp;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::right_rotation(binary_search_tree<tkey, tvalue, tkey_comparer>::node** sub_tree_root)
{
	node* tmp = *(sub_tree_root);
	(*sub_tree_root) = (*sub_tree_root)->left_subtree_address;
	tmp->left_subtree_address = (*sub_tree_root)->right_subtree_address;
	(*sub_tree_root)->right_subtree_address = tmp;
}

// region iterators implementation

// region prefix_iterator implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::prefix_iterator(
	binary_search_tree<tkey, tvalue, tkey_comparer>::node* tree_root)
{
	_current_node = tree_root;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator==(
	binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator const& other) const
{
	if (_current_node == other._current_node && _way == other._way)
		return true;

	return false;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator!=(
	binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator const& other) const
{
	return !(*this == other);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator& binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++()
{
	if (_current_node == nullptr)
		return *this;

	if (_current_node->left_subtree_address)
	{
		_way.push(_current_node);
		_current_node = _current_node->left_subtree_address;
		return *this;
	}
	else if (_current_node->right_subtree_address)
	{
		_way.push(_current_node);
		_current_node = _current_node->right_subtree_address;
		return *this;
	}
	else
	{
		while (true)
		{
			if (_way.empty())
			{
				_current_node = nullptr;
				return *this;
			}
			else if (_way.top()->right_subtree_address == _current_node)
			{
				_current_node = _way.top();
				_way.pop();
			}
			else
			{
				if (_way.top()->right_subtree_address == nullptr)
					_current_node = _way.top()->right_subtree_address;
				else
				{
					_current_node = _way.top()->right_subtree_address;
					return *this;
				}
			}
		}
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++(
	int not_used)
{
	auto prew_state = *this;
	++(*this);
	return prew_state;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator*() const
{
	return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current_node->key, _current_node->value);
}

// endregion prefix_iterator implementation

// region infix_iterator implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::infix_iterator(
	binary_search_tree<tkey, tvalue, tkey_comparer>::node* tree_root)
{
	_current_node = tree_root;
	while (_current_node && _current_node->left_subtree_address)
	{
		_way.push(_current_node);
		_current_node = _current_node->left_subtree_address;
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator==(
	binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const& other) const
{
	if (_current_node == other._current_node && _way == other._way)
		return true;

	return false;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator!=(
	binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const& other) const
{
	return !(*this == other);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator& binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++()
{
	if (_current_node == nullptr)
		return *this;
	if (_current_node->right_subtree_address == nullptr)
	{
		while (!_way.empty()) // достаем левое поддерево корня
		{
			if (_way.top()->left_subtree_address == _current_node)
				break;

			_current_node = _way.top();
			_way.pop();
		}

		if (_way.empty()) // достаем или нет корень
			_current_node = nullptr;
		else
		{
			_current_node = _way.top();
			_way.pop();
		}
	}
	else
	{
		_way.push(_current_node);
		_current_node = _current_node->right_subtree_address;
		while (_current_node->left_subtree_address != nullptr)
		{
			_way.push(_current_node);
			_current_node = _current_node->left_subtree_address;
		}
	}
	return *this;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++(
	int not_used)
{
	auto prew_state = *this;
	++(*this);
	return prew_state;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator*() const
{
	return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current_node->key, _current_node->value);
}

// endregion infix_iterator implementation

// region postfix_iterator implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::postfix_iterator(
	binary_search_tree<tkey, tvalue, tkey_comparer>::node* tree_root)
{
	_current_node = tree_root;
	while (_current_node != nullptr && (_current_node->left_subtree_address || _current_node->right_subtree_address))
	{
		_way.push(_current_node);
		if (_current_node->left_subtree_address == nullptr)
			_current_node = _current_node->right_subtree_address;
		else
			_current_node = _current_node->left_subtree_address;
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator==(
	binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const& other) const
{
	if (_current_node == other._current_node && _way == other._way)
		return true;

	return false;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator!=(
	binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const& other) const
{
	return !(*this == other);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator& binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++()
{
	if (_current_node == nullptr)
		return *this;

	if (_way.empty())
		_current_node = nullptr;
	else
	{
		if (_way.top()->right_subtree_address == _current_node)
		{
			_current_node = _way.top();
			_way.pop();
		}
		else
		{
			if (_way.top()->right_subtree_address == nullptr)
			{
				_current_node = _way.top();
				_way.pop();
			}
			else
			{
				_current_node = _way.top()->right_subtree_address;
				while (_current_node->left_subtree_address || _current_node->right_subtree_address)
				{
					_way.push(_current_node);
					if (_current_node->left_subtree_address == nullptr)
						_current_node = _current_node->right_subtree_address;
					else
						_current_node = _current_node->left_subtree_address;
				}
			}
		}
	}
	return *this;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++(
	int not_used)
{
	auto prew_state = *this;
	++(*this);
	return prew_state;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator*() const
{
	return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current_node->key, _current_node->value);
}

// endregion prefix_iterator implementation

// endregion iterators implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
memory* binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_memory() const
{
	return _tree->get_memory();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
logger* binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_logger() const
{
	return _tree->get_logger();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::inject_additional_data(
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* from,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* to) const
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
size_t binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_size_node()
{
	return sizeof(binary_search_tree<tkey, tvalue, tkey_comparer>::node);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::initialize_node_additional_data(
	binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node) const
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::constructor_node(
	binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node,
	tkey const& key,
	tvalue&& value) const
{
	new (ptr_node) binary_search_tree<tkey, tvalue, tkey_comparer>::node(key, std::move(value));
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::initialization_node(binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node,
	tkey const& key,
	tvalue&& value)
{
	constructor_node(ptr_node, key, std::move(value));
	ptr_node->key = key;
	ptr_node->value = std::move(value);
	ptr_node->left_subtree_address = nullptr;
	ptr_node->right_subtree_address = nullptr;
	initialize_node_additional_data(ptr_node);
}

// region template methods implementation

// region insertion implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert(
	tkey const& key,
	tvalue&& value,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_root_address)
{
	before_insert_inner();

	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;

	return insert_inner(key, std::move(value), tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::update(
	tkey const& key,
	tvalue&& value,
	node*& tree_root_address)
{
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;

	return update_inner(key, std::move(value), tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert_inner(
	tkey const& key,
	tvalue&& value,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		subtree_root_address = reinterpret_cast<binary_search_tree<tkey, tvalue, tkey_comparer>::node*>(allocate_with_guard(get_size_node()));
		// this->trace_with_guard("node is insert " + std::to_string(key));
		initialization_node(subtree_root_address, key, std::move(value));
	}
	else
	{
		int result_of_comparer = _tree->_comparator(key, subtree_root_address->key);

		if (result_of_comparer == 0)
		{
			throw new std::exception();
		}

		path_to_subtree_root_exclusive.push(&subtree_root_address);

		if (result_of_comparer > 0)
			insert_inner(key, std::move(value), subtree_root_address->right_subtree_address, path_to_subtree_root_exclusive);
		else
			insert_inner(key, std::move(value), subtree_root_address->left_subtree_address, path_to_subtree_root_exclusive);

		path_to_subtree_root_exclusive.pop();
	}

	after_insert_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::update_inner(
	tkey const& key,
	tvalue&& value,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	auto insert_node = &subtree_root_address;

	while (*insert_node != nullptr)
	{
		int compare_result = _tree->_comparator(key, (*insert_node)->key);

		if (compare_result == 0)
		{
			(*insert_node)->value.~tvalue();

			(*insert_node)->value = std::move(value);

			break;
		}

		path_to_subtree_root_exclusive.push(insert_node);
		insert_node = &(compare_result > 0 ? (*insert_node)->right_subtree_address : (*insert_node)->left_subtree_address);
	}

	if (*insert_node == nullptr)
	{
		std::string message = "Key not found";
		this->warning_with_guard(message + ".");

		throw std::invalid_argument(message);
	}

	// after_insert_inner(key, *insert_node, path_to_subtree_root_exclusive);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::before_insert_inner()
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::after_insert_inner(
	tkey const& key,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
}

// endregion insertion implementation

// region reading implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
logger* binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::get_logger() const
{
	return _tree->get_logger();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read(
	typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value,
	node*& tree_root_address)
{
	std::stack<binary_search_tree::node**> path_to_subtree_root_exclusive;
	return read_inner(target_key_and_result_value, tree_root_address, path_to_subtree_root_exclusive);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue& binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read(
	tkey const& key,
	node*& tree_root_address)
{
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;
	return read(key, tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::find_in(
	tkey const& key,
	node*& tree_root_address)
{
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;
	return find_in_inner(key, tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue& binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::find(
	tkey const& key,
	node*& tree_root_address)
{
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;
	return find_inner(key, tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read_to_string(
	tkey const& key,
	node*& tree_root_address)
{
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;
	return read_to_string_inner(key, tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue& binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read_inner(
	tkey const& key,
	node*& subtree_root_address,
	std::stack<node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		this->trace_with_guard("Key not found");
	}

	auto find_node = &subtree_root_address;
	// tvalue return_value;

	while ((*find_node) != nullptr)
	{
		int result_of_comparer = _tree->_comparator(key, (*find_node)->key);

		if (result_of_comparer == 0)
		{
			// TODO: after_read_inner();
			tvalue return_value = std::move((*find_node)->value);
			// this->trace_with_guard("There is node with key " + std::to_string(key));
			return return_value;
		}
		else
		{
			if (result_of_comparer < 0)
			{
				path_to_subtree_root_exclusive.push(find_node);
				find_node = &(*find_node)->left_subtree_address;
			}
			else
			{
				path_to_subtree_root_exclusive.push(find_node);
				find_node = &(*find_node)->right_subtree_address;
			}
		}
	}

	this->trace_with_guard("Key not found");
	throw std::exception();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read_inner(
	typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value,
	node*& subtree_root_address,
	std::stack<node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		this->trace_with_guard("Key not found");
	}

	tkey_comparer comparator;

	auto find_node = &subtree_root_address;

	while (*find_node != nullptr)
	{
		int compare_result = comparator(target_key_and_result_value->key, (*find_node)->key);

		if (compare_result == 0)
		{
			target_key_and_result_value->value = std::move((*find_node)->value);
			after_read_inner(target_key_and_result_value, subtree_root_address, path_to_subtree_root_exclusive);
			return true;
		}
		else
		{
			path_to_subtree_root_exclusive.push(find_node);
			find_node = &(compare_result > 0 ? (*find_node)->right_subtree_address
				: (*find_node)->left_subtree_address);
		}
	}

	return false;

	// before_read_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue& binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::find_inner(
	tkey const& key,
	node*& subtree_root_address,
	std::stack<node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		std::string message = "Key not found";
		this->warning_with_guard(message);

		throw std::invalid_argument(message + ".");
	}

	tkey_comparer comparator;

	auto find_node = &subtree_root_address;

	while (*find_node != nullptr)
	{
		int compare_result = comparator(key, (*find_node)->key);

		if (compare_result == 0)
		{
			tvalue& returned_value = (*find_node)->value;
			// after_read_inner(*find_node, path_to_subtree_root_exclusive);
			return returned_value;
		}
		else
		{
			path_to_subtree_root_exclusive.push(find_node);
			find_node = &(compare_result > 0 ? (*find_node)->right_subtree_address : (*find_node)->left_subtree_address);
		}
	}

	std::string message = "Key not found";
	this->warning_with_guard(message);

	throw std::invalid_argument(message + ".");
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::find_in_inner(
	tkey const& key,
	node*& subtree_root_address,
	std::stack<node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		std::string message = "Key not found";
		this->warning_with_guard(message);

		throw std::invalid_argument(message + ".");
	}

	tkey_comparer comparator;

	auto find_node = &subtree_root_address;

	while (*find_node != nullptr)
	{
		int compare_result = comparator(key, (*find_node)->key);

		if (compare_result == 0)
		{
			// tvalue &returned_value = (*find_node)->value;
			//  after_read_inner(*find_node, path_to_subtree_root_exclusive);
			return true;
		}
		else
		{
			path_to_subtree_root_exclusive.push(find_node);
			find_node = &(compare_result > 0
				? (*find_node)->right_subtree_address
				: (*find_node)->left_subtree_address);
		}
	}

	std::string message = "Key not found";
	this->warning_with_guard(message);

	return false;

	throw std::invalid_argument(message + ".");
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read_to_string_inner(
	tkey const& key,
	node*& subtree_root_address,
	std::stack<node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		this->trace_with_guard("Key not found");
	}

	tkey_comparer comparator;

	auto find_node = &subtree_root_address;

	while (*find_node != nullptr)
	{
		int compare_result = comparator(key, (*find_node)->key);

		if (compare_result == 0)
		{
			return true;
		}
		else
		{
			path_to_subtree_root_exclusive.push(find_node);
			find_node = &(compare_result > 0 ? (*find_node)->right_subtree_address
				: (*find_node)->left_subtree_address);
		}
	}

	return false;

	// before_read_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::before_read_inner(
	tkey const& key,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::after_read_inner(
	typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
}

// endregion reading implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
memory* binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::get_memory() const
{
	return _tree->get_memory();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
logger* binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::get_logger() const
{
	return _tree->get_logger();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::swap_nodes(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node** one_node, typename binary_search_tree<tkey, tvalue, tkey_comparer>::node** another_node)
{
	swap(one_node, another_node);
	swap(&(*one_node)->left_subtree_address, &(*another_node)->left_subtree_address);
	swap(&(*one_node)->right_subtree_address, &(*another_node)->right_subtree_address);
	// swap_additional_nodes_data(*one_node, *another_node);
}

// region removing implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove(
	tkey const& key,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_root_address)
{
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;
	return remove_inner(key, tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<tkey, tvalue> binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove_node(
	tkey const& key,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_root_address)
{
	std::list<binary_search_tree<tkey, tvalue, tkey_comparer>::node**> stack;
	return remove_node_inner(key, tree_root_address, stack);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove_inner(
	tkey const& key,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		this->trace_with_guard("Tree is empty");

		throw std::exception();
	}

	auto current_node = &subtree_root_address;

	node** removed_node = nullptr;

	while (*current_node != nullptr)
	{

		int result_of_comparer = _tree->_comparator(key, (*current_node)->key);

		if (result_of_comparer == 0)
		{

			removed_node = current_node;

			break;
		}

		path_to_subtree_root_exclusive.push(current_node);
		if (result_of_comparer > 0)
			current_node = &(*current_node)->right_subtree_address;
		else
			current_node = &(*current_node)->left_subtree_address;
	}

	if (*removed_node == nullptr)
	{
		this->trace_with_guard("There is no removed node");
		throw std::exception();
	}

	tvalue removed_value = std::move((*removed_node)->value);

	bool flag_removed = false;

	if ((*removed_node)->right_subtree_address != nullptr && (*removed_node)->left_subtree_address != nullptr)
	{
		auto successor = (*removed_node)->left_subtree_address;

		path_to_subtree_root_exclusive.push(removed_node);
		path_to_subtree_root_exclusive.push(&((*removed_node)->left_subtree_address));

		while (successor->right_subtree_address != nullptr)
		{
			path_to_subtree_root_exclusive.push(&(successor->right_subtree_address));
			successor = successor->right_subtree_address;
		}

		auto tmp_node = removed_node;
		removed_node = path_to_subtree_root_exclusive.top();
		path_to_subtree_root_exclusive.pop();

		tkey swap_key = (*removed_node)->key;
		(*removed_node)->key = (*tmp_node)->key;
		(*tmp_node)->key = swap_key;

		tvalue swap_value = std::move((*removed_node)->value);
		(*removed_node)->value = std::move((*tmp_node)->value);
		(*tmp_node)->value = std::move(swap_value);
	}

	if (!flag_removed)
	{

		if ((*removed_node)->right_subtree_address == nullptr && (*removed_node)->left_subtree_address == nullptr)
		{
			(*removed_node)->~node();
			deallocate_with_guard(*removed_node);
			*removed_node = nullptr;
		}
		else
		{
			auto tmp = (*removed_node)->left_subtree_address != nullptr
				? (*removed_node)->left_subtree_address
				: (*removed_node)->right_subtree_address;

			(*removed_node)->~node();
			deallocate_with_guard(*removed_node);
			*removed_node = tmp;
		}
	}

	after_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
	// this->trace_with_guard("The node is removed by key " + std::to_string(key));
	return removed_value;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<tkey, tvalue> binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove_node_inner(
	const tkey& key,
	node*& subtree_root_address,
	std::list<node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		std::string message = "Tree is empty";
		this->warning_with_guard(message);

		throw std::invalid_argument(message + ".");
	}

	auto current_node = &subtree_root_address;
	node** removed_node = nullptr;

	while (*current_node != nullptr)
	{
		int compare_result = _tree->_comparator(key, (*current_node)->key);

		if (compare_result == 0)
		{
			removed_node = current_node;
			break;
		}
		else
		{
			path_to_subtree_root_exclusive.push_back(current_node);
			current_node = &(compare_result > 0 ? (*current_node)->right_subtree_address : (*current_node)->left_subtree_address);
		}
	}

	if (*removed_node == nullptr)
	{
		std::string message = "Key not found";
		this->warning_with_guard(message);

		throw std::invalid_argument(message + ".");
	}

	std::tuple<tkey, tvalue> removed_value((*removed_node)->key, (*removed_node)->value);

	auto removal_completed = false;

	if ((*removed_node)->left_subtree_address != nullptr && (*removed_node)->right_subtree_address != nullptr)
	{
		auto successor = (*removed_node)->right_subtree_address;
		auto right_subtree_root = &(*removed_node)->right_subtree_address;

		if (successor->left_subtree_address == nullptr)
		{
			successor->left_subtree_address = (*removed_node)->left_subtree_address;
			(*removed_node)->~node();
			deallocate_with_guard(*removed_node);
			*removed_node = successor;
			removal_completed = true;
		}
		else
		{
			path_to_subtree_root_exclusive.push_back(removed_node);
			auto removed_node_list_id = path_to_subtree_root_exclusive.size() - 1;
			path_to_subtree_root_exclusive.push_back(&(*removed_node)->right_subtree_address);

			while (successor->left_subtree_address != nullptr)
			{
				path_to_subtree_root_exclusive.push_back(&(successor->left_subtree_address));
				successor = successor->left_subtree_address;
			}

			auto it1 = path_to_subtree_root_exclusive.begin();
			std::advance(it1, removed_node_list_id);
			auto it2 = path_to_subtree_root_exclusive.rbegin();
			swap_nodes(*it1, *it2);
			std::advance(it1, 1);
			*it1 = right_subtree_root;

			removed_node = *path_to_subtree_root_exclusive.rbegin();
			path_to_subtree_root_exclusive.pop_back();
		}
	}

	if (!removal_completed)
	{
		if ((*removed_node)->left_subtree_address == nullptr && (*removed_node)->right_subtree_address == nullptr)
		{
			(*removed_node)->~node();
			deallocate_with_guard((*removed_node));
			(*removed_node) = nullptr;
		}
		else
		{
			auto tmp = (*removed_node)->left_subtree_address != nullptr ? (*removed_node)->left_subtree_address : (*removed_node)->right_subtree_address;
			(*removed_node)->~node();
			deallocate_with_guard((*removed_node));
			(*removed_node) = tmp;
		}
	}

	// after_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);

	return removed_value;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::before_remove_inner(
	tkey const& key,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::after_remove_inner(
	tkey const& key,
	binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::after_remove_inner(
	tkey const& key,
	node*& subtree_root_address,
	std::list<node**>& path_to_subtree_root_exclusive)
{
}
// endregion implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* binary_search_tree<tkey, tvalue, tkey_comparer>::copy() const
{
	return copy_inner(_root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* binary_search_tree<tkey, tvalue, tkey_comparer>::copy_inner(
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* to_copy) const
{
	if (to_copy == nullptr)
	{
		return nullptr;
	}

	auto* node_copy = reinterpret_cast<binary_search_tree<tkey, tvalue, tkey_comparer>::node*>(allocate_with_guard(_insertion->get_size_node()));

	_insertion->initialization_node(node_copy, to_copy->key, std::move(tvalue(to_copy->value)));
	_insertion->inject_additional_data(to_copy, node_copy);
TODO:

	node_copy->left_subtree_address = copy_inner(to_copy->left_subtree_address);
	node_copy->right_subtree_address = copy_inner(to_copy->right_subtree_address);

	return node_copy;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::clear()
{
	clear_inner(_root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::clear_inner(
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* to_clear) const
{
	if (to_clear == nullptr)
	{
		return;
	}

	clear_inner(to_clear->left_subtree_address);
	clear_inner(to_clear->right_subtree_address);

	to_clear->~node();
	deallocate_with_guard(to_clear);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::move(binary_search_tree<tkey, tvalue, tkey_comparer>&& other)
{
	_root = other._root;
	other._root = nullptr;

	_allocator = other._allocator;
	other._allocator = nullptr;

	_logger = other._logger;
	other._logger = nullptr;

	_insertion = other._insertion;
	other._insertion = nullptr;

	_reading = other._reading;
	other._reading = nullptr;

	_removing = other._removing;
	other._removing = nullptr;
}

// endregion template methods

// region construction, assignment, destruction implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
	binary_search_tree::insertion_template_method* insertion,
	binary_search_tree::reading_template_method* reading,
	binary_search_tree::removing_template_method* removing,
	memory* allocator,
	logger* logger)
	: _insertion(insertion),
	_reading(reading),
	_removing(removing),
	_allocator(allocator),
	_logger(logger),
	_root(nullptr),
	_comparator()
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
	memory* allocator,
	logger* logger) : binary_search_tree(new insertion_template_method(this),
		new reading_template_method(this),
		new removing_template_method(this),
		allocator,
		logger)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
	const binary_search_tree& other) : binary_search_tree<tkey, tvalue, tkey_comparer>(other._allocator, other._logger) // конструктор копирования
{
	_root = other.copy();

	this->trace_with_guard("The tree has been copy");
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
	binary_search_tree&& other) noexcept // конструктор перемещения
{
	move(std::move(other));
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>& binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
	const binary_search_tree& other) // конструктор присваивания
{
	if (this == &other)
	{
		return *this;
	}

	clear();

	_allocator = other._allocator;
	_logger = other._logger;

	_root = other.copy();

	return *this;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>& binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
	binary_search_tree&& other) noexcept // конструктор перемещения-присваивания
{
	if (this == &other)
	{
		return *this;
	}

	clear();

	delete _insertion;
	delete _reading;
	delete _removing;

	move(std::move(other));

	return *this;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::~binary_search_tree()
{
	clear();

	delete _insertion;
	delete _reading;
	delete _removing;
}

// endregion construction, assignment, destruction implementation

// region associative_container contract implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insert(
	tkey const& key,
	tvalue&& value)
{
	_insertion->insert(key, std::move(value), _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::get(
	typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value)
{
	return _reading->read(target_key_and_result_value, _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue& binary_search_tree<tkey, tvalue, tkey_comparer>::find(
	tkey const& key)
{
	return _reading->find(key, _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue binary_search_tree<tkey, tvalue, tkey_comparer>::remove(
	tkey const& key)
{
	return _removing->remove(key, _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<tkey, tvalue> binary_search_tree<tkey, tvalue, tkey_comparer>::remove_node(
	tkey const& key)
{
	return _removing->remove_node(key, _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::find_to_string(
	tkey const& key)
{
	return _reading->read_to_string(key, _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::find_in(
	tkey const& key)
{
	return _reading->find_in(key, _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::update(
	tkey const& key,
	tvalue&& value)
{
	return _insertion->update(key, std::move(value), _root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::vector<tvalue> binary_search_tree<tkey, tvalue, tkey_comparer>::get_data_between(
	tkey const& left_key,
	tkey const& right_key)
{
	if (_comparator(left_key, right_key) > 0)
	{
		return std::vector<tvalue>();
	}

	std::vector<tvalue> result;

	auto it = begin_infix();
	auto end_infix = this->end_infix();

	while (it != end_infix)
	{
		if (_comparator(std::get<1>(*it), left_key) >= 0)
		{
			break;
		}

		++it;
	}

	while (it != end_infix)
	{
		if (_comparator(std::get<1>(*it), right_key) > 0)
		{
			break;
		}

		result.push_back(std::get<2>(*it));
		++it;
	}

	return result;
}

// endregion associative_container contract implementation

// region logger_holder contract implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
logger* binary_search_tree<tkey, tvalue, tkey_comparer>::get_logger() const
{
	return _logger;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
memory* binary_search_tree<tkey, tvalue, tkey_comparer>::get_memory() const
{
	return _allocator;
}

// endregion logger_holder contract implementation

// region iterators requesting implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_prefix() const noexcept
{
	return prefix_iterator(_root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_prefix() const noexcept
{
	return prefix_iterator(nullptr);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_infix() const noexcept
{
	return infix_iterator(_root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_infix() const noexcept
{
	return infix_iterator(nullptr);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_postfix() const noexcept
{
	return postfix_iterator(_root);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_postfix() const noexcept
{
	return postfix_iterator(nullptr);
}

// endregion iterators requesting implementation

#endif // SANDBOX_CPP_BINARY_SEARCH_TREE_H
