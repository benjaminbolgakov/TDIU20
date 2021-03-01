#include <string>
#include <iostream>
#include <sstream>

#include "catch.hpp"
#include "Circuit.h"

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
        Circuit c;
        c.addConnection();
        c.addComponent(new Battery("Bat",24.0));

    }
}

#if 0
#endif
