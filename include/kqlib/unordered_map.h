#ifndef kqunordered_map_
#define kqunordered_map_

#include "other.h"
#include "vector.h"
#include "single_list.h"

namespace kq
{
   


    template<typename Key, typename T>
    struct unordered_map
    {
    public:

        using key_type = Key;
        using mapped_type = T;
        using value_type = kq::pair<key_type, mapped_type>;
        using reference = value_type&;
        using pointer = value_type*;


        unordered_map();
        unordered_map(const unordered_map& other); // FIXME: implement
        unordered_map(unordered_map&& other); // FIXME: implement

        unordered_map& operator=(const unordered_map& other); // FIXME: implement
        unordered_map& operator=(unordered_map&& other); // FIXME: implement

    private:
        vector<single_list<value_type>> kq_data;
        size_t kq_size;
        size_t kq_cap;
    };

    template<typename Key, typename T>
    unordered_map<Key, T>::unordered_map()
        : kq_data(), kq_size(0), kq_cap(0)
    {}



} // namespace kq

#endif