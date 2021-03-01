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
void printHeader(vector<Component*> net)
{
    for (Component* c : net)
    {
        std::cout << c->getId() << "\t \t";
    }
    std::cout << std::endl;
    for (Component* c : net)
    {
        std::cout << "Volt  Curr\t";
    }
    std::cout << std::endl;
}
void simulate(vector<Component*> net, int iterations, int nmbPrints, double time)
{
    printHeader(net);
    for (int i{0}; i < nmbPrints; i++)
    {
        for (int j{0}; j < (iterations/nmbPrints); j++)
        {
            for (Component* c : net)
            {
                c->update(time);
            }
        }
        for (Component* c : net)
        {
            std::cout << setprecision(2) << fixed << setw(2)
                      << c->getVoltage() << "  " << c->getCurrent() << "\t";
        }
        std::cout << std::endl;
    }
}

TEST_CASE ("Circuit 1")
{
    SECTION("Test")
    {
        Connection p, n, q1, q2;
        vector<Component*> net;
        net.push_back(new Battery("Bat", 24.0,p,n));
        net.push_back(new Resistor("R1", 6.0,p,q1));
        net.push_back(new Resistor("R2", 4.0,q1,q2));
        net.push_back(new Resistor("R3", 8.0,q2,n));
        net.push_back(new Resistor("R4", 12.0,q1,n));
        simulate(net, 200000, 10, 0.01);
    }
}

TEST_CASE ("Circuit 2")
{
    SECTION("Test")
    {
        Connection p, l, r, n;
        vector<Component*> net;
        net.push_back(new Battery("Bat", 24.0, p,n));
        net.push_back(new Resistor("R1", 150.0, p,l));
        net.push_back(new Resistor("R2", 50.0, p,r));
        net.push_back(new Resistor("R3", 100.0, r,l));
        net.push_back(new Resistor("R4", 300.0, l,n));
        net.push_back(new Resistor("R5", 250.0, r,n));
        simulate(net, 200000, 10, 0.01);
    }
}

TEST_CASE ("Circuit 3")
{
    SECTION("Test")
    {
        Connection p, l, r, n;
        vector<Component*> net;
        net.push_back(new Battery("Bat", 24.0, p,n));
        net.push_back(new Resistor("R1", 150.0, p,l));
        net.push_back(new Resistor("R2", 50.0, p,r));
        net.push_back(new Capacitor("C3", 1.0, r,l));
        net.push_back(new Resistor("R4", 300.0, l,n));
        net.push_back(new Capacitor("C5", 0.75, r,n));
        simulate(net, 200000, 10, 0.01);
    }
}

#if 0
#endif
