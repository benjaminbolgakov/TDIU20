#include "Sorted_List.h"
//Constructors
Sorted_List::Sorted_List() : first{nullptr}, last{nullptr} {}
Sorted_List::Sorted_List(const Sorted_List& copy)
    : first{nullptr}, last{nullptr} {}
Sorted_List::~Sorted_List()
{
    delete first;
}

//Functions
void Sorted_List::insert(int N)
{
    first = new Node{N, first}; //Append node
}
void Sorted_List::print() const
{
    Node* tmp{first};
    while(tmp != nullptr)
    {
        std::cout << tmp->value << " "; //Find "value" in Node
        tmp = tmp -> next; //Set tmp to point to next Node
    }
    std::cout << std::endl;
}
