#include "Sorted_List.h"
//Constructors
Sorted_List::Sorted_List() : first{new Node{nullptr,0,nullptr}}, last{new Node{first,0,nullptr}}
{
    first->next = last;
}
Sorted_List::Sorted_List(std::initializer_list<int> const& l) :
    first{new Node{nullptr,0,nullptr}}, last{new Node{first,0,nullptr}}
{
    first->next = last;
    for (int i : l){
        insert(i);
    }
}
Sorted_List::Sorted_List(Sorted_List const& copy) :
    first{new Node{nullptr,0,nullptr}}, last{new Node{first,0,nullptr}}
{
    first->next = last;
    Node* ptr_index{copy.first->next};
    while(ptr_index->next != nullptr)
    {
        insert(ptr_index->value);
        ptr_index = ptr_index->next;
    }
}
Sorted_List::Sorted_List(Sorted_List && other) :
    first{nullptr}, last{nullptr}
{
    first = other.first;
    last = other.last;
    other.first = nullptr;
    other.last = nullptr;
}
//Destructor
Sorted_List::~Sorted_List()
{
    delete first;
}

//Operators
Sorted_List& Sorted_List::operator=(Sorted_List const& other)
{
    if(this == &other)
    {
        throw std::logic_error("Invalid copy-operation");
    }
    Node* ptr_index{other.first->next};
    while(ptr_index->next != nullptr)
    {
        insert(ptr_index->value);
        ptr_index = ptr_index->next;
    }

    return *this;
}
Sorted_List& Sorted_List::operator=(Sorted_List && other)
{
    Node* tmp{first};
    first = other.first;
    other.first = tmp;
    tmp = last;
    last = other.last;
    other.last = tmp;
    return *this;
}
std::ostream &operator<< (std::ostream &os, Sorted_List list)
{
    os << list.to_string();
    return os;
}

//Functions
std::string Sorted_List::to_string() const
{
    std::string res="";
    Node* tmp{first};
    //Check if list have been emptied
    if(tmp != nullptr)
    {
        tmp = tmp->next;
        while (tmp->next != nullptr)
        {
            res += std::to_string(tmp->value) + " ";
            tmp = tmp->next;
        }
        if(res != "")
        {
            res.pop_back(); //Remove trailing space
        }
    }
    return res;
}

void Sorted_List::insert(int i)
{
    Node* ptr_index{first};
    //std::cout << "First 1: " << first << std::endl;
    if (ptr_index->next->next != nullptr)
    {
        while (i > ptr_index->next->value)
        {
            ptr_index = ptr_index->next;
            if(ptr_index->next->next == nullptr)
            {
                break;
            }
        }

    }
    ptr_index->next = new Node{ptr_index,i,ptr_index->next};
    ptr_index->next->next->prev = ptr_index->next;
}


int Sorted_List::get(int index) const
{
    if (index >= 0)
    {
        Node* tmp{first->next};
        for (int i{0}; i < index; i++)
        {
            tmp = tmp->next;

            if(tmp == nullptr)
            {
                throw std::logic_error("Invalid operation");
            }
        }
        return tmp->value;
    }
    else
    {
        throw std::logic_error("Invalid index");
    }
}

void Sorted_List::remove(int index)
{
    Node* removed{first->next};
    for (int i{0}; i < index; i++)
    {
        removed = removed->next;

        if(removed == nullptr)
        {
            throw std::logic_error("Invalid operation");
        }
    }
    Node* tmp{removed->prev};
    //Reassign the surrounding nodes pointers
    tmp->next = removed->next;
    removed->next->prev = tmp;

    removed->next = nullptr; //Make sure the destructor cant progress further
    delete removed;
}

void Sorted_List::print() const
{
    Node* tmp{first->next};
    while (tmp->next != nullptr)
    {
        std::cout << tmp->value << " ";
        tmp = tmp->next;
    }
    std::cout << std::endl;
}

//Iterator
Sorted_List::Iterator::Iterator(Sorted_List::Iterator const& copy) : current{nullptr}
{
//    Sorted_List::Iterator ptr_index{copy.current};
    current = copy.current;
}
Sorted_List::Iterator& Sorted_List::Iterator::operator=(Sorted_List::Iterator const& copy)
{
    if(this == &copy)
    {
        throw std::logic_error("Invalid copy-operation");
    }
    //Sorted_List::Iterator* ptr_index{copy.current};
    current = copy.current;
    return *this;
}
//Sorted_List::Iterator::Iterator(Sorted_List::Iterator && other) : current{other.current} {}


Sorted_List::Iterator::Iterator(Sorted_List::Node* n) : current{n} {}

Sorted_List::Iterator Sorted_List::begin() const
{
    Sorted_List::Iterator it{first};
    return it;
}
Sorted_List::Iterator Sorted_List::end() const
{
    Sorted_List::Iterator it{last};
    return it;
}
Sorted_List::Iterator& Sorted_List::Iterator::operator++()
{
    current = current->next;
    return *this;
}
bool Sorted_List::Iterator::operator!=(Sorted_List::Iterator const& ir)
{
    if(current == ir.current)
    {
        return false;
    }
    return true;
}
int Sorted_List::Iterator::operator*(Sorted_List::Iterator const& rhs)
{
    return rhs.current->value;
}
