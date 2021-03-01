#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Sorted_List.h"

using namespace std;

// här lägger ni era testfall.
// Jobba enligt TDD;
//  1. Lägg till testfall
//  2. Testa
//  3. Lägg till (minsta möjliga) implementation
//  4. Testa alla testfall
//  5. Refaktorera (skriv om) så att allt ser bra ut


TEST_CASE ("Constructors")
{
    SECTION("Default constructor")
    {
        Sorted_List empty;
        CHECK(empty.to_string() == "");
        empty.insert(2);
        empty.insert(5);
        CHECK(empty.to_string() == "2 5");
    }
    SECTION("Initializer List constructor")
    {
        Sorted_List initialized{2,7,5};
        CHECK(initialized.to_string() == "2 5 7");
        initialized.insert(4);
        CHECK(initialized.to_string() == "2 4 5 7");
    }
}
TEST_CASE ("Output")
{
    SECTION("Outputstream")
    {
        stringstream ss;
        Sorted_List list;
        list.insert(2);
        list.insert(5);
        ss << list;
        CHECK(ss.str() == "2 5");
    }
}
TEST_CASE ("Copy")
{
    SECTION("Copy constructor")
    {
        Sorted_List original{2,4,6};
        Sorted_List copy{original};
        CHECK(copy.to_string() == "2 4 6");
        CHECK(original.to_string() == "2 4 6");
    }
    SECTION("Copy operation")
    {
        Sorted_List original{2,4,6};
        Sorted_List copy{7,6,5};
        copy = original;
        CHECK(copy.to_string() == "2 4 6");
        CHECK(original.to_string() == "2 4 6");
    }

    SECTION ("Throws selfcopy")
    {
        Sorted_List selfcopy;
        CHECK_THROWS(selfcopy = selfcopy);
    }
    Sorted_List l1{1,2,3};
    Sorted_List l2{4,5,6};
    l1 = l2;
    CHECK(l1.to_string() == "4 5 6");
    CHECK(l2.to_string() == "4 5 6");
}
TEST_CASE ("Move")
{
    SECTION ("Move constructor")
    {
        Sorted_List original{2,4,6};
        Sorted_List new_list{std::move(original)};
        CHECK(new_list.to_string() == "2 4 6");
        CHECK(original.to_string() == "");
    }
    SECTION ("Move operation")
    {
        Sorted_List original{2,4,6};
        Sorted_List new_list{1,2,3};
        new_list = std::move(original);
        CHECK(new_list.to_string() == "2 4 6");
        CHECK(original.to_string() == "1 2 3");
    }
}
TEST_CASE ("Iterator")
{
    Sorted_List list{2,4,7};
    for (Sorted_List::Iterator it = list.begin(); it != list.end(); ++it)
    {
        cout << *it << endl;
    }
}
TEST_CASE ("Get/Remove")
{
    Sorted_List list{6,2,5};
    CHECK(list.get(1) == 5);
    list.remove(1);
    CHECK(list.get(1) == 6);
    CHECK_THROWS(list.remove(4));
    CHECK_THROWS(list.get(-1));
    CHECK_THROWS(list.get(4));
}
#if 0
#endif
