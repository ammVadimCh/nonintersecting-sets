#pragma once
#include <vector>
#include <list>

struct setpair
{
    size_t elem_index;
    size_t set_index;
};

template<class type>
class Sets{
    std::vector<type> data;
    std::vector<std::list<size_t>> set_index;
    std::vector<size_t> element_index;
    std::vector<size_t> empty_sets = {};
    size_t sets_number = 0;
public:

    setpair make_set(const type&);
    std::list<size_t> find_set(const size_t &);
    size_t union_sets(const size_t, const size_t);
    const type& get_elem_value_by_index(size_t);
    int get_elem_index_by_value(const type &);
    size_t get_set_by_elem_ind(size_t );
};

template<class type>
int Sets<type>::get_elem_index_by_value(const type& searched){
    for(int i =0; i< data.size(); i++)
        if(data[i] == searched)
            return i;
    return -1;
}

template<class type>
size_t Sets<type>::get_set_by_elem_ind(size_t ind){
    return element_index[ind];
}

template<class type>
const type& Sets<type>::get_elem_value_by_index(size_t ind){
    return data[ind];
}

template<class type>
size_t Sets<type>::union_sets(const size_t first, const size_t second){
    if(second >= set_index.size() || first >= set_index.size()) return 90000u;//whatever
    while(set_index[second].empty() == false){
        size_t buffer = set_index[second].front();
        set_index[second].pop_front();
        element_index[buffer] = first;
        set_index[first].push_front(buffer);
    }
    empty_sets.push_back(second);
    return first;
}

template<class type>
std::list<size_t> Sets<type>::find_set(const size_t &ind){
    if(ind < set_index.size())
        return set_index[ind];
    return std::list<size_t>();
}

template<class type>
setpair Sets<type>::make_set(const type& elem){
    size_t elem_ind = element_index.size();
    size_t set_ind = set_index.size();
    bool reuse = false;
    if(!empty_sets.empty()){
        set_ind = empty_sets.back();
        empty_sets.pop_back();
        reuse = true;
    }
    std::list<size_t> buffer;
    buffer.push_front(elem_ind);
    if(reuse == true){
        set_index[set_ind] = buffer;
    }
    else 
        set_index.push_back(buffer);
        
    element_index.push_back(set_ind);
    data.push_back(elem);

    setpair retval = {elem_ind , set_ind};
    return retval;
}
