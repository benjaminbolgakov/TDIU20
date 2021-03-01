#include <stdexcept>
#include <iostream>
#include <initializer_list>

class Sorted_List{
public:
    //Constructors
    Sorted_List(); //Default
    Sorted_List(std::initializer_list<int> const& l);
    Sorted_List(Sorted_List const& copy);
    Sorted_List(Sorted_List && other);
    //Destructor
    ~Sorted_List();
    //Operators
    Sorted_List& operator=(Sorted_List const& other);
    Sorted_List& operator=(Sorted_List && other);
    //Functions
    void insert(int i);
    void print() const;
    void remove(int index);
    int get(int index) const;
    std::string to_string() const;

    //Clarify scope for Iterator to access Node elements
private : class Node;

    //Iterator
public: class Iterator{
    friend Sorted_List;
public:
    //Constructor
    Iterator(Iterator const& copy);
    //Destructor
    ~Iterator()
    {
        //delete current;
    }
    //Operators
    Iterator& operator=(Iterator const& copy);
    Iterator& operator++();
    int operator*() const;
    bool operator!=(Iterator const& ir);


private:
    Iterator(Sorted_List::Node* n);
    Node* current;
};

    Iterator begin() const;
    Iterator end() const;

private:
    class Node
    {
    public:
        ~Node()
        {
            delete next;
        }

        Node* prev;
        int value;
        Node* next;
    };
    //Member variables
    Node* first;
    Node* last;
};
//Free functions
std::ostream &operator<< (std::ostream &os, Sorted_List list);
