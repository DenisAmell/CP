#ifndef SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H
#define SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H

#include <vector>

template <
	typename tkey,
	typename tvalue>
class associative_container
{

public:
	struct key_and_value_pair
	{
		tkey key;
		tvalue value;
	};

public:
	virtual ~associative_container() = default;

public:
	virtual void insert(
		tkey const& key,
		tvalue&& value) = 0;

	virtual bool get(
		typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value) = 0;

	virtual tvalue& find(
		tkey const& key) = 0;

	virtual tvalue remove(
		tkey const& key) = 0;

	virtual std::tuple<tkey, tvalue> remove_node(
		tkey const& key) = 0;

	virtual bool find_to_string(
		tkey const& key) = 0;

	virtual bool find_in(
		tkey const& key) = 0;

	tvalue get_value(
		tkey const& key)
	{
		return find(key);
	}

	virtual void update(
		tkey const& key,
		tvalue&& value) = 0;

	virtual std::vector<tvalue> get_data_between(
		tkey const& left_key,
		tkey const& right_key) = 0;
};

#endif // SANDBOX_CPP_ASSOCIATIVE_CONTAINER_H