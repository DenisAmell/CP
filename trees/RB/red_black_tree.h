#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "../BST/binary_search_tree.h"

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
class red_black_tree final : public binary_search_tree<tkey, tvalue, tkey_comparer>
{
private:
	enum class color_node
	{
		RED,
		BLACK
	};

	struct red_black_node final : binary_search_tree<tkey, tvalue, tkey_comparer>::node
	{
		color_node color;

		red_black_node(tkey const& new_key, tvalue&& new_value) : binary_search_tree<tkey, tvalue, tkey_comparer>::node(new_key, std::move(new_value))
		{
		}
	};

public:
	void prefix_traverse()
	{
		prefix_traverse_inner(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(this->get_root()), 0);
	}

private:
	void prefix_traverse_inner(typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node* rb_node,
		unsigned int depth)
	{
		if (rb_node == nullptr)
		{
			return;
		}

		for (auto i = 0; i < depth; i++)
		{
			std::cout << "  ";
		}
		std::cout << "Key == " << rb_node->key << ", color == " << (rb_node->color == color_node::RED ? "red" : "black") << std::endl;

		prefix_traverse_inner(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(rb_node->left_subtree_address), depth + 1);
		prefix_traverse_inner(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(rb_node->right_subtree_address), depth + 1);
	}

protected:
	class red_black_insertion_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method
	{
	private:
		enum class balance_status
		{
			NO_BALANCE_NEEDED,
			BALANCE_AT_GP,
			BALANCE_AT_P
		};

		enum class rise_status
		{
			FROM_LEFT_SUBTREE,
			FROM_RIGHT_SUBTREE,
			NOTHING
		};

	private:
		red_black_tree<tkey, tvalue, tkey_comparer>* _tree;
		balance_status _balance;
		rise_status _rise_further_status;
		rise_status _rise_near_status;

	public:
		red_black_insertion_template_method(red_black_tree<tkey, tvalue, tkey_comparer>* tree) : _tree(tree),
			binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method(tree) {};

	protected:
		void after_insert_inner(
			tkey const& key,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;

		size_t get_size_node() override;
		void constructor_node(
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node,
			tkey const& key,
			tvalue&& value) const override;
		void initialize_node_additional_data(
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node) const override;
		void before_insert_inner() override
		{
			_balance = balance_status::BALANCE_AT_GP;
			_rise_further_status = rise_status::NOTHING;
			_rise_near_status = rise_status::NOTHING;
		}
	};

protected:
	class red_black_removing_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method
	{
	private:
		enum class rise_status_remove
		{
			FROM_LEFT_SUBTREE,
			FROM_RIGHT_SUBTREE,
			NOTHING
		};

	private:
		red_black_tree<tkey, tvalue, tkey_comparer>* _tree;
		rise_status_remove _rise_further_status;
		rise_status_remove _rise_near_status;

	public:
		red_black_removing_template_method(
			red_black_tree<tkey, tvalue, tkey_comparer>* tree);

	protected:
		void before_remove_inner() override
		{
			_rise_further_status = rise_status_remove::NOTHING;
			_rise_near_status = rise_status_remove::NOTHING;
		};

	protected:
		void after_remove_inner(
			tkey const& key,
			typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
			std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive) override;
	};

public:
	explicit red_black_tree(
		memory* allocator = nullptr,
		logger* logger = nullptr);

protected:
	color_node get_color(typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node* ptr_to_node);

public:
	red_black_tree(
		red_black_tree<tkey, tvalue, tkey_comparer> const& other);

	red_black_tree(
		red_black_tree<tkey, tvalue, tkey_comparer>&& other) noexcept;

	red_black_tree& operator=(
		red_black_tree<tkey, tvalue, tkey_comparer> const& other);

	red_black_tree& operator=(
		red_black_tree<tkey, tvalue, tkey_comparer>&& other) noexcept;
};

// begin region insertion implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::after_insert_inner(
	tkey const& key,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address->left_subtree_address == nullptr &&
		subtree_root_address->right_subtree_address == nullptr)
	{
		reinterpret_cast<red_black_node*>(subtree_root_address)->color = path_to_subtree_root_exclusive.empty()
			? red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK
			: red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

		_rise_further_status = _rise_near_status;
		if (!path_to_subtree_root_exclusive.empty())
		{
			_rise_near_status =
				(*path_to_subtree_root_exclusive.top())->left_subtree_address == subtree_root_address
				? rise_status::FROM_LEFT_SUBTREE
				: rise_status::FROM_RIGHT_SUBTREE;
		}

		return;
	}

	switch (_balance)
	{
	case balance_status::NO_BALANCE_NEEDED:
		if (path_to_subtree_root_exclusive.empty())
		{
			reinterpret_cast<red_black_node*>(subtree_root_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
		}
		return;
	case balance_status::BALANCE_AT_GP:
		_balance = balance_status::BALANCE_AT_P;
		_rise_further_status = _rise_near_status;
		if (!path_to_subtree_root_exclusive.empty())
		{
			_rise_near_status =
				(*path_to_subtree_root_exclusive.top())->left_subtree_address == subtree_root_address
				? rise_status::FROM_LEFT_SUBTREE
				: rise_status::FROM_RIGHT_SUBTREE;
		}

		return;
	}

	red_black_node** parent = nullptr;
	red_black_node* grandson = nullptr;
	red_black_node* uncle = nullptr;

	uncle = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(
		_rise_near_status == rise_status::FROM_LEFT_SUBTREE
		? subtree_root_address->right_subtree_address
		: subtree_root_address->left_subtree_address);

	parent = _rise_near_status == rise_status::FROM_LEFT_SUBTREE
		? reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node**>(&subtree_root_address->left_subtree_address)
		: reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node**>(&subtree_root_address->right_subtree_address);

	if (*parent != nullptr)
	{
		grandson = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(
			_rise_further_status == rise_status::FROM_LEFT_SUBTREE
			? (*parent)->left_subtree_address
			: (*parent)->right_subtree_address);
	}

	if (_tree->get_color(grandson) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK ||
		_tree->get_color(*parent) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK)
	{
		_balance = balance_status::NO_BALANCE_NEEDED;
		return;
	}

	if (_rise_further_status != _rise_near_status && uncle == nullptr)
	{
		if (_rise_near_status == rise_status::FROM_LEFT_SUBTREE)
		{
			_tree->left_rotation(
				reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(parent));
			grandson = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->left_subtree_address);
		}
		else
		{
			_tree->right_rotation(
				reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(parent));
			grandson = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->right_subtree_address);
		}
	}

	if (_tree->get_color(uncle) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK)
	{
		(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(subtree_root_address))->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

		if (_rise_near_status == rise_status::FROM_LEFT_SUBTREE)
		{
			_tree->right_rotation(&subtree_root_address);
		}
		else
		{
			_tree->left_rotation(&subtree_root_address);
		}

		(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(subtree_root_address))->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;

		_balance = balance_status::NO_BALANCE_NEEDED;
	}
	else
	{
		uncle->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
		(*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
		(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(subtree_root_address))->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

		_balance = balance_status::BALANCE_AT_GP;
	}

	if (path_to_subtree_root_exclusive.empty())
	{
		reinterpret_cast<red_black_node*>(subtree_root_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
size_t red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::get_size_node()
{
	return sizeof(typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node);
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::initialize_node_additional_data(
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node) const
{
	reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(ptr_node)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_insertion_template_method::constructor_node(
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node* ptr_node,
	tkey const& key,
	tvalue&& value) const
{
	new (ptr_node) typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node(key, std::move(value));
}

// end region insertion implementation

// begin region removing implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
void red_black_tree<tkey, tvalue, tkey_comparer>::red_black_removing_template_method::after_remove_inner(
	tkey const& key,
	typename binary_search_tree<tkey, tvalue, tkey_comparer>::node*& subtree_root_address,
	std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>& path_to_subtree_root_exclusive)
{
	if (subtree_root_address == nullptr)
		return;

	if (!path_to_subtree_root_exclusive.empty())
	{
		auto pop_back_stack = **path_to_subtree_root_exclusive.rbegin();
		_rise_near_status =
			pop_back_stack->left_subtree_address == subtree_root_address
			? rise_status_remove::FROM_LEFT_SUBTREE
			: rise_status_remove::FROM_RIGHT_SUBTREE;
	}

	if (path_to_subtree_root_exclusive.empty() &&
		subtree_root_address->left_subtree_address == nullptr &&
		subtree_root_address->right_subtree_address == nullptr)
		return;

	red_black_node** parent = nullptr;
	red_black_node* brother = nullptr;

	parent = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node**>(*path_to_subtree_root_exclusive.rbegin());

	if (!path_to_subtree_root_exclusive.empty() &&
		_tree->get_color(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(subtree_root_address)) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK)
	{
		if (subtree_root_address == (*parent)->left_subtree_address)
		{
			brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->right_subtree_address);
			if (_tree->get_color(brother) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED)
			{
				brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
				(*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
				_tree->left_rotetion(reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(parent));

				brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->right_subtree_address);
			}

			if (_tree->get_color(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->left_subtree_address)) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK &&
				_tree->get_color(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->right_subtree_address)) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK)
			{
				brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
				subtree_root_address = *parent;
			}
			else if (_tree->get_color(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->left_subtree_address)) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK)
			{
				reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->left_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
				brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

				_tree->right_rotation(reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(brother));
				brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->right_subtree_address);
			}
			else
			{
				brother->color = (*parent)->color;
				(*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
				reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->right_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
				_tree->left_rotation(reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(parent));
			}
		}
		else
		{
			if (subtree_root_address == (*parent)->right_subtree_address)
			{
				brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->left_subtree_address);
				if (_tree->get_color(brother) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED)
				{
					brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
					(*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
					_tree->right_rotation(reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(parent));

					brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->right_subtree_address);
				}

				if (_tree->get_color(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->right_subtree_address)) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK &&
					_tree->get_color(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->left_subtree_address)) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK)
				{
					brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;
					subtree_root_address = *parent;
				}
				else if (_tree->get_color(reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->left_subtree_address)) == red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK) // почему здесь не свапнулся left на right?
				{
					reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->right_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
					brother->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::RED;

					_tree->left_rotation(reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(brother));
					brother = reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>((*parent)->left_subtree_address);
				}
				else
				{
					brother->color = (*parent)->color;
					(*parent)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
					reinterpret_cast<typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node*>(brother->left_subtree_address)->color = red_black_tree<tkey, tvalue, tkey_comparer>::color_node::BLACK;
					_tree->right_rotation(reinterpret_cast<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node**>(parent));
				}
			}
		}
	}
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_removing_template_method::red_black_removing_template_method(
	red_black_tree<tkey, tvalue, tkey_comparer>* tree)
	: _tree(tree),
	binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(tree)
{
}

// end region removing implementation

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
typename red_black_tree<tkey, tvalue, tkey_comparer>::color_node red_black_tree<tkey, tvalue, tkey_comparer>::get_color(
	typename red_black_tree<tkey, tvalue, tkey_comparer>::red_black_node* ptr_to_node)
{
	return (ptr_to_node != nullptr) ? ptr_to_node->color : color_node::BLACK;
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_tree(
	memory* allocator,
	logger* logger) : binary_search_tree<tkey, tvalue, tkey_comparer>(new red_black_insertion_template_method(this),
		new typename binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method(this),
		new typename binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(this),
		allocator,
		logger)
{
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_tree(
	red_black_tree<tkey, tvalue, tkey_comparer> const& other)
{
	binary_search_tree<tkey, tvalue, tkey_comparer>::_root = other.copy();
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>::red_black_tree(
	red_black_tree<tkey, tvalue, tkey_comparer>&& other) noexcept
{
	this->move(static_cast<binary_search_tree<tkey, tvalue, tkey_comparer>&&>(std::move(other)));
}

template <
	typename tkey,
	typename tvalue,
	typename tkey_comparer>
red_black_tree<tkey, tvalue, tkey_comparer>& red_black_tree<tkey, tvalue, tkey_comparer>::operator=(
	red_black_tree<tkey, tvalue, tkey_comparer> const& other)
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
red_black_tree<tkey, tvalue, tkey_comparer>& red_black_tree<tkey, tvalue, tkey_comparer>::operator=(
	red_black_tree<tkey, tvalue, tkey_comparer>&& other) noexcept
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

#endif // RED_BLACK_TREE_H