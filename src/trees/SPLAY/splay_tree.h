#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "../BST/binary_search_tree.h"

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class splay_tree final : public binary_search_tree<tkey, tvalue, tkey_comparer>
{
protected:
	class splay_insertion_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method
	{
	private:
		splay_tree<tkey, tvalue, tkey_comparer>* _tree;

	protected:
		void after_insert_inner(
			tkey const& key,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;

		void insert_inner(
			tkey const& key,
			tvalue&& value,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;

	private:
		size_t get_size_node() override;

	public:
		explicit splay_insertion_template_method(
			splay_tree<tkey, tvalue, tkey_comparer>* tree);
	};

protected:
	class splay_reading_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method
	{
	private:
		splay_tree<tkey, tvalue, tkey_comparer>* _tree;

	protected:
		void after_read_inner(
			tkey const& key,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;

	public:
		explicit splay_reading_template_method(
			splay_tree<tkey, tvalue, tkey_comparer>* tree);
	};

protected:
	class splay_removing_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method
	{
	private:
		splay_tree<tkey, tvalue, tkey_comparer>* _tree;

	protected:
		void after_remove_inner(
			tkey const& key,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::list<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;

		tvalue remove_inner(
			tkey const& key,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;

		std::tuple<tkey, tvalue> remove_node_inner(
			const tkey& key,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::list<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;

	public:
		explicit splay_removing_template_method(
			splay_tree<tkey, tvalue, tkey_comparer>* tree);
	};

protected:
	void splay(
		typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
		std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive);

	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* merge(
		typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_first,
		typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_second);

public:
	explicit splay_tree(memory* allocator = nullptr,
		logger* logger = nullptr);

	~splay_tree() final = default;

public:
	splay_tree(
		splay_tree<tkey, tvalue, tkey_comparer> const& other);

	splay_tree(
		splay_tree<tkey, tvalue, tkey_comparer>&& other) noexcept;

	splay_tree& operator=(
		splay_tree<tkey, tvalue, tkey_comparer> const& other);

	splay_tree& operator=(
		splay_tree<tkey, tvalue, tkey_comparer>&& other) noexcept;
};

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(memory* allocator,
	logger* logger) : binary_search_tree<tkey, tvalue, tkey_comparer>(new splay_insertion_template_method(this),
		new splay_reading_template_method(this),
		new splay_removing_template_method(this),
		allocator,
		logger)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_insertion_template_method::splay_insertion_template_method(
	splay_tree<tkey, tvalue, tkey_comparer>* tree) : _tree(tree),
	binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method(tree)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay_insertion_template_method::after_insert_inner(
	tkey const& key,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	_tree->splay(subtree_root_address, path_to_subtree_root_exclusive);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay_insertion_template_method::insert_inner(
	tkey const& key,
	tvalue&& value,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		subtree_root_address = reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*>(this->allocate_with_guard(get_size_node()));
		// this->trace_with_guard("node is insert " + std::to_string(key));
		this->initialization_node(subtree_root_address, key, std::move(value));
		after_insert_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
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

		//		path_to_subtree_root_exclusive.pop();
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
size_t splay_tree<tkey, tvalue, tkey_comparer>::splay_insertion_template_method::get_size_node()
{
	return sizeof(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay(
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* current_node = subtree_root_address;
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node** parent = nullptr;
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node** grandparent = nullptr;

	while (!path_to_subtree_root_exclusive.empty())
	{
		parent = path_to_subtree_root_exclusive.top();
		path_to_subtree_root_exclusive.pop();

		if (path_to_subtree_root_exclusive.size() > 1)
		{
			grandparent = path_to_subtree_root_exclusive.top();
			path_to_subtree_root_exclusive.pop();
		}

		if ((*parent)->left_subtree_address == current_node)
		{
			if (grandparent == nullptr)
			{
				this->right_rotation(parent);
			}
			else if ((*grandparent)->left_subtree_address == (*parent))
			{
				this->right_rotation(grandparent);
				this->right_rotation(parent);
			}
			else
			{
				this->right_rotation(parent);
				this->left_rotation(parent);
			}
		}
		else
		{
			if (grandparent == nullptr)
			{
				this->left_rotation(parent);
			}
			else if ((*grandparent)->right_subtree_address == (*parent))
			{
				this->left_rotation(grandparent);
				this->left_rotation(parent);
			}
			else
			{
				this->left_rotation(parent);
				this->right_rotation(parent);
			}
		}
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_reading_template_method::splay_reading_template_method(
	splay_tree<tkey, tvalue, tkey_comparer>* tree) : _tree(tree),
	binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method(tree)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay_reading_template_method::after_read_inner(
	tkey const& key,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	_tree->splay(subtree_root_address, path_to_subtree_root_exclusive);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_removing_template_method::splay_removing_template_method(
	splay_tree<tkey, tvalue, tkey_comparer>* tree) : _tree(tree),
	binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(tree)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
std::tuple<tkey, tvalue> splay_tree<tkey, tvalue, tkey_comparer>::splay_removing_template_method::remove_node_inner(
	const tkey& key,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::list<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		std::string message = "Tree is empty";
		this->warning_with_guard(message);

		throw std::invalid_argument("[SPLAY TREE] " + message + ".");
	}

	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**> path;
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node** current_node = &subtree_root_address;

	tkey_comparer comparator;

	while (*current_node != nullptr)
	{
		int compare_result = comparator(key, (*current_node)->key);

		if (compare_result == 0)
		{
			break;
		}
		else
		{
			path.push(current_node);
			current_node = &(compare_result > 0 ? (*current_node)->right_subtree_address : (*current_node)->left_subtree_address);
		}
	}

	if ((*current_node) == nullptr)
	{
		std::string message = "Key not found";
		this->warning_with_guard(message);

		throw std::invalid_argument("[SPLAY TREE] " + message + ".");
	}

	std::tuple<tkey, tvalue> removed_value((*current_node)->key, (*current_node)->value);

	_tree->splay(*current_node, path);

	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* left_subtree = subtree_root_address->left_subtree_address;
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* right_subtree = subtree_root_address->right_subtree_address;

	subtree_root_address->~node();

	_tree->deallocate_with_guard(subtree_root_address);

	this->trace_with_guard("[SPLAY TREE] Node has been deleted.");

	_tree->_root = _tree->merge(left_subtree, right_subtree);

	return removed_value;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay_removing_template_method::after_remove_inner(
	tkey const& key,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::list<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
tvalue splay_tree<tkey, tvalue, tkey_comparer>::splay_removing_template_method::remove_inner(
	tkey const& key,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
	{
		throw std::invalid_argument("Key not found");
	}

	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**> path;
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node** current_node = &subtree_root_address;

	while (current_node != nullptr)
	{
		if (_tree->_comparator(key, (*current_node)->key) == 0)
		{
			tvalue removed_value = std::move((*current_node)->value);
			_tree->splay((*current_node), path);

			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* left_subtree = subtree_root_address->left_subtree_address;
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* right_subtree = subtree_root_address->right_subtree_address;

			subtree_root_address->~node();
			_tree->deallocate_with_guard(subtree_root_address);

			_tree->_root = _tree->merge(left_subtree, right_subtree);

			return removed_value;
			//break;
		}
		else
		{
			path.push(current_node);
			if (_tree->_comparator(key, (*current_node)->key) > 0)
				current_node = &((*current_node)->right_subtree_address);
			else
				current_node = &((*current_node)->left_subtree_address);
		}
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* splay_tree<tkey, tvalue, tkey_comparer>::merge(
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_first,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& tree_second)
{
	if (tree_first == nullptr && tree_second != nullptr)
		return tree_second;

	if (tree_first != nullptr && tree_second == nullptr)
		return tree_first;

	if (tree_first != nullptr && tree_second != nullptr)
	{
		std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**> path;
		typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* max_node = tree_first;
		typename binary_search_tree<tkey, tvalue, tkey_comparer>::node** parent = &tree_first;

		while (max_node->right_subtree_address != nullptr)
		{
			path.push(parent);
			parent = &(max_node->right_subtree_address);
			max_node = max_node->right_subtree_address;
		}

		splay(max_node, path);
		tree_first->right_subtree_address = tree_second;
		return tree_first;
	}

	return nullptr;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(
	splay_tree<tkey, tvalue, tkey_comparer> const& other)
{
	binary_search_tree<tkey, tvalue, tkey_comparer>::_root = other.copy();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(
	splay_tree<tkey, tvalue, tkey_comparer>&& other) noexcept
{
	this->move(static_cast<binary_search_tree<tkey, tvalue, tkey_comparer>&&>(std::move(other)));
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>& splay_tree<tkey, tvalue, tkey_comparer>::operator=(
	splay_tree<tkey, tvalue, tkey_comparer> const& other)
{
	if (this == &other)
	{
		return *this;
	}

	this->clear();

	this->_allocator = other._allocator;
	this->_logger = other._logger;
	this->_root = other.copy();

	return *this;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>& splay_tree<tkey, tvalue, tkey_comparer>::operator=(
	splay_tree<tkey, tvalue, tkey_comparer>&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	this->clear();

	delete this->_insertion;
	delete this->_reading;
	delete this->_removing;

	this->move(std::move(other));

	return *this;
}

#endif // SPLAY_TREE_H