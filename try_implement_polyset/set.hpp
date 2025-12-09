#include "searchable_bag.hpp"
#include "bag.hpp"

class set{// the set class does not inherit 
    private:
        searchable_bag &bag;
    public:
        set(searchable_bag &bg) : bag(bg){}
        ~set(){}
        

};

