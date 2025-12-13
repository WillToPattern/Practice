
#ifndef SET_HPP
#define SET_HPP

#include "searchable_bag.hpp"

class set
{
    private:
        searchable_bag& bag;
    public:
        set(searchable_bag& bag) : bag(bag) {}
        set(const set& other) : bag(other.bag) {}
        ~set() {};
        set& operator=(const set& other)
        {
            (void)other;
            return *this;
        }

        void insert(int val);
        void insert(int* array, int size);
        void print() const;
        void clear();
        bool has(int val) const;
        searchable_bag& get_bag() const;
};


#endif
