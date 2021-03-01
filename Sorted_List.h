#include <stdexcept>
#include <iostream>
#include <initializer_list>
class Sorted_List{
public:
    //Constructors
    Sorted_List(); //Default
    Sorted_List(const Sorted_List& copy);
    //Destructor
    ~Sorted_List();
    //Functions
    void insert(int N); //Performs sorted insert
    void print() const;
private:
    class Node
    {
    public:
        //Destructor
        ~Node()
        {
            delete next;
        }
        int value;
        Node* next;
    };
    //Member variables
    Node* first;
    Node* last;
};
