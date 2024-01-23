#include "hash_list.h"
//#include <iostream>
#include<assert.h>

//Create an empty list
template<class ke, class va> hash_list<ke,va>::hash_list() 
{
    head = NULL;
    size = 0;
    iter_ptr = head;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

template<class ke, class va> void hash_list<ke, va>::insert(ke key, va value) 
{
    
    if(head == NULL)
    {
        node<ke, va> *newnode = new node<ke, va>;
        newnode -> key = key;
        newnode -> value = value;
        newnode -> next = NULL;
        head = newnode;
        size++;

    }
    else
    {
        // variable to check if there is any matched key
        int check = 0;

        node<ke, va> *prenode = head;
        node<ke, va> *curnode = head;
        while((curnode != NULL) && (check == 0))
        {

            //If a node with the associated key already exists, update that node with the new value
            if(curnode -> key == key)
            {
                curnode -> value = value;
                check = 1;
            }
            curnode = curnode -> next;
        }
        while(prenode -> next != curnode)
        {
            prenode = prenode -> next;
        }

        if(check == 0)
        {
            node<ke, va> *newnode = new node<ke, va>;
            newnode -> key = key;
            newnode -> value = value;
            newnode -> next = NULL;
            prenode -> next = newnode;
            size++;
        }

    }
    
    
}

template<class ke, class va> std::optional<va> hash_list<ke, va>::get_value(ke key) const 
{ 
    node<ke, va> *curnode = head;

    while(curnode != NULL)
    {
        if(curnode -> key == key)
        {
            return curnode -> value;
        }
        curnode = curnode -> next;
    }

    return std::nullopt; 
}


template<class ke, class va> bool hash_list<ke, va>::remove(ke key) 
{ 
    node<ke, va> *prenode = head;
    node<ke, va> *curnode = head;

    while(curnode != NULL)
    {        
        //Remove the node containing the specified key from the list and return true.
        if(curnode -> key == key)
        {
            //assert(prenode != NULL);
            if(curnode == prenode) 
            {
                //special case: removing the first node
                prenode = prenode -> next;
                head = prenode;
            }
            else 
            {
                while(prenode -> next != curnode) 
                {
                    //move prenode to correct position (beyond first node)
                    prenode = prenode -> next;
                }
                prenode -> next = curnode -> next;
            }
            delete curnode;
            size--;
            return true;
        }
        curnode = curnode -> next;

    }
    
    return false; 
}

template<class ke, class va> size_t hash_list<ke, va>::get_size() const 
{ 
    return size;
}


template<class ke, class va> hash_list<ke, va>::~hash_list() 
{ 
    node<ke, va> *prenode = head;
    node<ke, va> *curnode = head;

    while(curnode != NULL)
    {      
        //assert(prenode != NULL);
        if(curnode == prenode) 
        {
            //special case: removing the first node
            prenode = prenode -> next;
            head = prenode;
        }
        delete curnode;
        size--;
        curnode = prenode;
    }
}


/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

template<class ke, class va> hash_list<ke, va>::hash_list(const hash_list &other) 
{
    if(other.head != NULL)
    {
        //allocate memory
        node<ke, va> *newnode = new node<ke, va>;

        newnode -> value = other.head -> value;
        newnode -> key = other.head -> key;
        newnode -> next = NULL;
        this -> head =  newnode;

        node<ke, va> *prenode = newnode;
        node<ke, va> *tempnode = other.head;

        //link each node in the list
        for(size_t i = 0; i < other.size; i++)
        {
            if(tempnode -> next != NULL)
            {
                node<ke, va> *newnewnode = new node<ke, va>;
                newnewnode -> value = tempnode -> next -> value;
                newnewnode -> key = tempnode -> next -> key;
                newnewnode -> next = tempnode -> next -> next;
                prenode -> next = newnewnode;
                prenode = prenode -> next;
                newnewnode = newnewnode -> next;
                tempnode = tempnode -> next;
            }
            else
            {
                prenode -> next = NULL;
            }
        }
        this -> size = other.size;
    }
    else
    {
        head = NULL;
        size = 0;
        iter_ptr = head;
    }

}

template<class ke, class va> hash_list<ke, va>& hash_list<ke, va>::operator=(const hash_list &other) 
{ 
    if(this == &other)
    {
        //assign to myself
        return *this;
    }
    else
    {
        while (head != NULL)
        {
            node<ke, va> *victim = head;
            head = head -> next;
            delete victim;
        }
    }
    if(other.head != NULL)
    {
        //allocate memory
        node<ke, va> *newnode = new node<ke, va>;

        newnode -> value = other.head -> value;
        newnode -> key = other.head -> key;
        newnode -> next = NULL;
        this -> head =  newnode;

        node<ke, va> *prenode = newnode;
        node<ke, va> *tempnode = other.head;

        //link each node in the list
        for(size_t i = 0; i < other.size; i++)
        {
            if(tempnode -> next != NULL)
            {
                node<ke, va> *newnewnode = new node<ke, va>;
                newnewnode -> value = tempnode -> next -> value;
                newnewnode -> key = tempnode -> next -> key;
                newnewnode -> next = tempnode -> next -> next;
                prenode -> next = newnewnode;
                prenode = prenode -> next;
                newnewnode = newnewnode -> next;
                tempnode = tempnode -> next;
            }
            else
            {
                prenode -> next = NULL;
            }
        }
        this -> size = other.size;
    }
    else
    {
        head = NULL;
        size = 0;
        iter_ptr = head;
    }
    return *this;
}

template<class ke, class va> void hash_list<ke, va>::reset_iter() 
{
    iter_ptr = head;
}


template<class ke, class va> void hash_list<ke, va>::increment_iter() 
{
    if(iter_ptr != NULL)
    {
        iter_ptr = iter_ptr -> next;
    }
}


template<class ke, class va> std::optional<std::pair<const ke *, va *>> hash_list<ke, va>::get_iter_value() 
{
    
    
    if(iter_ptr == NULL)
    {
        return std::nullopt; 
    }
    else
    {
	const ke * key = &(iter_ptr -> key);
	va *value = &(iter_ptr -> value);
        return std::pair(key, value);
    }
}


template<class ke, class va> bool hash_list<ke, va>::iter_at_end() 
{ 
    if(iter_ptr == NULL)
    {
        return true;
    }
    else
    {
        return false; 
    }
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
