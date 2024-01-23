#include "hash_map.h"
#include<assert.h>
#include<stdlib.h>     /* for qsort */
/*
static int hash_func(int key, int capacity)
{
    size_t val = _hash( key ) % capacity ;

    return val;
}
*/

template<typename K, typename V> hash_map<K, V> :: hash_map(size_t capacity, float upper_load_factor,
             float lower_load_factor)
{
    _capacity = capacity;
    _size = 0;
    if ( _capacity == 0)
    {
        _head = NULL;
    }
    else
    {
        _head = new hash_list<K, V>[_capacity];
    }
    _upper_load_factor = upper_load_factor;
    _lower_load_factor = lower_load_factor;
}

template<typename K, typename V> hash_map<K, V> :: hash_map(const hash_map &other)
{
    _capacity = other._capacity;
    _size = other._size;
    _head = new hash_list<K, V>[_capacity];

    for(size_t cp = 0; cp < _capacity; cp++)
    {
        _head[cp] = other._head[cp];
    }

    _upper_load_factor = other._upper_load_factor;
    _lower_load_factor = other._lower_load_factor;
}

template<typename K, typename V> hash_map<K, V>& hash_map<K, V> :: operator=(const hash_map &other)
{
    //check if the same
    if (this == &other)
    {
        return *this;
    }

    _capacity = other._capacity;
    _size = other._size;

    if (_head == NULL)
    {
        _head = new hash_list<K,V>[_capacity];
    }
    else
    {
        delete[] _head;
        _head = new hash_list<K,V>[_capacity];
    }

    for(size_t cp = 0; cp < _capacity; cp++)
    {
        _head[cp] = other._head[cp];
    }

    return *this;
}

template<typename K, typename V> void hash_map<K, V> :: insert(K key, V value)
{   
    //deermine which location in _head should you insert to
    size_t where = _hash( key ) % _capacity ;
    //int where = hash_func(key, _capacity);

    //insert element
    //check if there is same key in the original array
    bool  check = _head[where].get_value(key).has_value();
    _head[where].insert(key, value);

    //update _size accordingly
    if(!check)
    {
        _size++;
    }
    if(_size > _upper_load_factor * _capacity)
    {
        hi_rehash();
    }
    else if(_size < _lower_load_factor * _capacity)
    {
        lo_rehash();
    }
}

template<typename K, typename V> std::optional<V> hash_map<K, V> :: get_value(K key) const
{
    //deermine which location in _head should you insert to
    size_t where = _hash( key ) % _capacity ;

    return _head[where].get_value(key);
}


template<typename K, typename V> size_t hash_map<K, V> :: get_size() const
{
    return _size;
}

template<typename K, typename V> bool hash_map<K, V> :: remove(K key)
{
    //deermine which location in _head should you insert to
    size_t where = _hash( key ) % _capacity ;
    bool check = _head[where].remove(key);

    if(check)
    {
        _size--;
    }

    if(_size < _lower_load_factor * _capacity)
    {
        lo_rehash();
    }
    else if(_size > _upper_load_factor * _capacity)
    {
        hi_rehash();
    }

    return check;
}


template<typename K, typename V> size_t hash_map<K, V> :: get_capacity() const
{
    return _capacity;
}

template<typename K, typename V> void hash_map<K, V> :: get_all_keys(K *keys)
{
    size_t keys_idx = 0;
    for(size_t cp = 0; cp < _capacity; cp++)
    { //go through each bucket
        _head[cp].reset_iter();
        for(size_t i = 0; i < _head[cp].get_size(); i++)
        {   
            // bool key_exist = _head[cp].get_iter_value().has_value();
            keys[keys_idx] =  *(_head[cp].get_iter_value().value().first);
            keys_idx++;
            _head[cp].increment_iter();
        }
        assert(_head[cp].iter_at_end());
    }
}

static int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

template<typename K, typename V> void hash_map<K,V> :: get_all_sorted_keys(K *keys)
{
    //size_t j;
    get_all_keys(keys);
    qsort (keys, get_size(), sizeof(K), compare);

    /*insertion sort
    for(size_t i = 1; i < get_size(); i++)
    {
        K t = keys[i];
        j = i - 1;

        while(j >= 0 && keys[j] > t)
        {
            keys[j + 1] = keys[j];
            j--;
        }
        keys[j + 1] = t;
    }
    */

}

template<typename K, typename V> void hash_map<K, V> :: get_bucket_sizes(size_t *buckets)
{
    for(size_t cp = 0; cp < _capacity; cp++)
    { //go through each bucket
        buckets[cp] = _head[cp].get_size();
    }
}


template<typename K, typename V> hash_map<K, V> ::~hash_map(){
    if(_head != NULL) {
        delete [] _head;
    }
}