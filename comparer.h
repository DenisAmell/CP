#ifndef comparer_H
#define comparer_H

class string_comparer
{
public:
    int operator()(
        std::string const &x,
        std::string const &y)
    {
        auto x_iterator = x.begin();
        auto y_iterator = y.begin();
        auto const x_end_iterator = x.cend();
        auto const y_end_iterator = y.cend();

        while (true)
        {
            auto const diff = *x_iterator - *y_iterator;
            if (diff != 0)
            {
                return diff;
            }

            ++x_iterator;
            ++y_iterator;

            if (x_iterator == x_end_iterator && y_iterator == y_end_iterator)
            {
                return 0;
            }
            else if (x_iterator == x_end_iterator)
            {
                return *y_iterator;
            }
            else if (y_iterator == y_end_iterator)
            {
                return *x_iterator;
            }
        }
    }
};

class key_comparer
{
public:
    int operator()(key *first, key *second)
    {
        int comparison_result = first->_id - second->_id;
        if (comparison_result != 0)
        {
            return comparison_result;
        }

        return comparison_result;
    }
};

#endif // comparer_H