#ifndef STRING_POOL_H
#define STRING_POOL_H


#include <iostream>
#include <string>
#include <unordered_map>


class string_pool
{
private:
	string_pool()
	{
	}

	std::unordered_map<std::string, int> string_pool_;

public:

	static string_pool& instance()
	{
		static string_pool pool;
		return pool;
	}

	const std::string& get_string(const std::string& str)
	{
		auto it = string_pool_.find(str);
		if (it != string_pool_.end())
		{
			it->second++;
			return it->first;
		}
		else
		{
			auto [new_it, _] = string_pool_.emplace(str, 1);
			return new_it->first;
		}


	}

	void unget_string(const std::string& str)
	{
		auto it = string_pool_.find(str);
		if (it != string_pool_.end())
		{
			it->second--;
			if (it->second <= 0)
				string_pool_.erase(it);
		}

	}

	~string_pool() {
		string_pool_.clear();
	}
};


#endif //STRING_POOL_H