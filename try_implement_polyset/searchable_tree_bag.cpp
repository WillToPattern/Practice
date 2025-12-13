#include "searchable_tree_bag.hpp"

bool searchable_tree_bag::has(int val) const
{
    return (search_node(this->tree, val));
}

bool searchable_tree_bag::search_node(node* n, int val) const
{
    if (!n)
        return false;
    if (val == n->value)
        return true;
    if (val < n->value)
        return search_node(n->l, val);
    return search_node(n->r, val);


}
