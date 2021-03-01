#include <stdexcept>
#include <iostream>
#include <initializer_list>

/* Komplettering
 * Får ett error vid kompilering:
 * Er *operator till Iterator tar in en Iterator const& som argument.
 * *operatorn ska inte ha några parametrar.
*/

/* Komplettering
 * Testa er remove och get.
*/

/* Komplettering
 * Användaren ska inte ha tillgång till någon publik funktion som
 * returnerar eller tar in en Node*.
 * 
 * Er konstruktor i iteratorn måste därför göras private.
*/

/* Komplettering
 * Copy konstruktor/tilldelning: Just nu är dessa väldigt lika varandra
 * (kodduplicering). Ni kan använda copy konstruktorn i copy tilldelningen.
 * Copy tilldelningen borde även ta bort datat från den existerande
 * listan, dvs datat ska inte lägga till.
 * 
 * List l1{1,2,3};
 * List l2{4,5,6};
 * l1 = l2;
 * l1 == {4,5,6}
 * l2 == {4,5,6}
*/

/* Kommentar
 * C++ har en inbyggd swap-funktion som kan användas för att byta värde
 * på två variabler.
*/

/* Kommentar
 * Implementationen av copy är väldigt ineffektiv när insert används.
 * Går att förbättra genom att ha en privat insert_last funktion som sätter
 * in ett värde i slutet av listan. Detta eftersom listan som kopieras
 * alltid är sorterad.
*/

class Sorted_List
{
public:
    //Constructors
    Sorted_List(); //Default
    Sorted_List(std::initializer_list<int> const &l);
    Sorted_List(Sorted_List const &copy);
    Sorted_List(Sorted_List &&other);
    //Destructor
    ~Sorted_List();
    //Operators
    Sorted_List &operator=(Sorted_List const &other);
    Sorted_List &operator=(Sorted_List &&other);
    //Functions
    void insert(int i);
    void print() const;
    void remove(int index);
    int get(int index) const;
    std::string to_string() const;

private:
    class Node;

public:
    class Iterator
    {
    public:
        //Constructor
        Iterator(Sorted_List::Node *n);
        Iterator(Iterator const &copy);
        //Destructor
        ~Iterator()
        {
            //delete current;
        }
        //Operators
        Iterator &operator=(Iterator const &copy);
        Iterator &operator++();
        int operator*(Iterator const &rhs);
        bool operator!=(Iterator const &ir);

    private:
        Node *current;
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

        Node *prev;
        int value;
        Node *next;
    };
    //Member variables
    Node *first;
    Node *last;
};
//Free functions
std::ostream &operator<<(std::ostream &os, Sorted_List list);
