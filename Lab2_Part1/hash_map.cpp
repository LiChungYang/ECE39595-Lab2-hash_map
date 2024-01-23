#include "hash_map.h"
#include<assert.h>
static int hash_func(int key, int capacity)
{
    int val;
    int abs_key;
    if (key < 1)
    {
        abs_key = -key;
    }
    else
    {
        abs_key = key;
    }
    val = abs_key % capacity;

    return val;
}

hash_map :: hash_map(size_t capacity)
{
    _capacity = capacity;
    _size = 0;
    if ( _capacity == 0)
    {
        _head = NULL;
    }
    else
    {
        _head = new hash_list[_capacity];
    }
}

hash_map :: hash_map(const hash_map &other)
{
    _capacity = other._capacity;
    _size = other._size;
    _head = new hash_list[_capacity];

    for(size_t cp = 0; cp < _capacity; cp++)
    {
        _head[cp] = other._head[cp];
    }
}

hash_map& hash_map :: operator=(const hash_map &other)
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
        _head = new hash_list[_capacity];
    }
    else
    {
        delete[] _head;
        _head = new hash_list[_capacity];
    }

    for(size_t cp = 0; cp < _capacity; cp++)
    {
        _head[cp] = other._head[cp];
    }

    return *this;
}

void hash_map :: insert(int key, float value)
{   
    //deermine which location in _head should you insert to
    int where = hash_func(key, _capacity);

    //insert element
    //check if there is same key in the original array
    bool  check = _head[where].get_value(key).has_value();
    _head[where].insert(key, value);

    //update _size accordingly
    if(!check)
    {
        _size++;
    }
}

std::optional<float> hash_map :: get_value(int key) const
{
    //deermine which location in _head should you insert to
    int where = hash_func(key, _capacity);

    return _head[where].get_value(key);
}


size_t hash_map :: get_size() const
{
    return _size;
}

bool hash_map :: remove(int key)
{
    //deermine which location in _head should you insert to
    int where = hash_func(key, _capacity);
    bool check = _head[where].remove(key);

    if(check)
    {
        _size--;
    }

    return check;
}


size_t hash_map :: get_capacity() const
{
    return _capacity;
}

void hash_map :: get_all_keys(int *keys)
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

void hash_map :: get_bucket_sizes(size_t *buckets)
{
    for(size_t cp = 0; cp < _capacity; cp++)
    { //go through each bucket
        buckets[cp] = _head[cp].get_size();
    }
}


hash_map ::~hash_map(){
    if(_head != NULL) {
        delete [] _head;
    }
}