#include "hash_list.h"
//#include <iostream>
#include<assert.h>

//Create an empty list
hash_list::hash_list() 
{
    head = NULL;
    size = 0;
    iter_ptr = head;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) 
{
    
    if(head == NULL)
    {
        node *newnode = new node;
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

        node *prenode = head;
        node *curnode = head;
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
            node *newnode = new node;
            newnode -> key = key;
            newnode -> value = value;
            newnode -> next = NULL;
            prenode -> next = newnode;
            size++;
        }

    }
    
    
}

std::optional<float> hash_list::get_value(int key) const 
{ 
    node *curnode = head;

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


bool hash_list::remove(int key) 
{ 
    node *prenode = head;
    node *curnode = head;

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

size_t hash_list::get_size() const 
{ 
    return size;
}


hash_list::~hash_list() 
{ 
    node *prenode = head;
    node *curnode = head;

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

hash_list::hash_list(const hash_list &other) 
{
    if(other.head != NULL)
    {
        //allocate memory
        node *newnode = new node;

        newnode -> value = other.head -> value;
        newnode -> key = other.head -> key;
        newnode -> next = NULL;
        this -> head =  newnode;

        node *prenode = newnode;
        node *tempnode = other.head;

        //link each node in the list
        for(size_t i = 0; i < other.size; i++)
        {
            if(tempnode -> next != NULL)
            {
                node *newnewnode = new node;
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

hash_list &hash_list::operator=(const hash_list &other) 
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
            node *victim = head;
            head = head -> next;
            delete victim;
        }
    }
    if(other.head != NULL)
    {
        //allocate memory
        node *newnode = new node;

        newnode -> value = other.head -> value;
        newnode -> key = other.head -> key;
        newnode -> next = NULL;
        this -> head =  newnode;

        node *prenode = newnode;
        node *tempnode = other.head;

        //link each node in the list
        for(size_t i = 0; i < other.size; i++)
        {
            if(tempnode -> next != NULL)
            {
                node *newnewnode = new node;
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

void hash_list::reset_iter() 
{
    iter_ptr = head;
}


void hash_list::increment_iter() 
{
    if(iter_ptr != NULL)
    {
        iter_ptr = iter_ptr -> next;
    }
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() 
{
    
    
    if(iter_ptr == NULL)
    {
        return std::nullopt; 
    }
    else
    {
	const int * key = &(iter_ptr -> key);
	float *value = &(iter_ptr -> value);
        return std::pair(key, value);
    }
}


bool hash_list::iter_at_end() 
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
