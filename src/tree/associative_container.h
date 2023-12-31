#ifndef DATA_STRUCTURES_CPP_ASSOCIATIVE_CONTAINER_H
#define DATA_STRUCTURES_CPP_ASSOCIATIVE_CONTAINER_H

#include <iostream>
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

	virtual bool find(
		typename associative_container<tkey, tvalue>::key_and_value_pair* target_key_and_result_value) = 0;

	virtual tvalue& find(
		tkey const& key) = 0;

	virtual bool find_to_string(tkey const& key) = 0;

	virtual tvalue remove(
		tkey const& key) = 0;

	virtual std::tuple<tkey, tvalue> remove_node(tkey const& key) = 0;

	virtual bool find_in(tkey const& key) = 0;

	virtual void update(tkey const& key, tvalue&& value) = 0;

	virtual std::vector<tvalue> find_in_range(tkey const& min_bound, tkey const& max_bound) = 0;

	tvalue get_value(tkey const& key)
	{
		return find(key);
	}

public:
	void operator+=(key_and_value_pair& pair);

	bool operator[](key_and_value_pair* target_key_and_result_value);

	tvalue operator-=(tkey const& key);
};

template <
	typename tkey,
	typename tvalue>
void associative_container<tkey, tvalue>::operator+=(key_and_value_pair& pair)
{
	insert(pair.key, std::move(pair.value));
}

template <
	typename tkey,
	typename tvalue>
bool associative_container<tkey, tvalue>::operator[](key_and_value_pair* target_key_and_result_value)
{
	return find(target_key_and_result_value);
}

template <
	typename tkey,
	typename tvalue>
tvalue associative_container<tkey, tvalue>::operator-=(const tkey& key)
{
	return remove(key);
}

#endif // DATA_STRUCTURES_CPP_ASSOCIATIVE_CONTAINER_H