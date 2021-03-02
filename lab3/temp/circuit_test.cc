#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Circuit.h"

using namespace std;

void printHeader(vector<Component*> net);
void simulate(vector<Component*> net, int iterations, int nmbPrints, double time);
void data_control(int argc, char* argv[]);
void mem_clean(vector<Component*> net);

int main(int argc, char* argv[])
{
    //Args:
    // Iterations, iterations to print, time-interval, battery voltage
    data_control(argc,argv);

    double in_iterations = atof(argv[1]);
    double in_prints = atof(argv[2]);
    double in_interval = atof(argv[3]);
    double in_bat_voltage = atof(argv[4]);
    cout << in_iterations << " " << in_prints << " " << in_interval << " " << in_bat_voltage << endl;

    /*Connection p, n, q1, q2;
    vector<Component*> net;
    net.push_back(new Battery("Bat", 24.0,p,n));
    net.push_back(new Resistor("R1", 6.0,p,q1));
    net.push_back(new Resistor("R2", 4.0,q1,q2));
    net.push_back(new Resistor("R3", 8.0,q2,n));
    net.push_back(new Resistor("R4", 12.0,q1,n));
    simulate(net, 200000, 10, 0.01);


    Connection p, l, r, n;
    vector<Component*> net;
    net.push_back(new Battery("Bat", 24.0, p,n));
    net.push_back(new Resistor("R1", 150.0, p,l));
    net.push_back(new Resistor("R2", 50.0, p,r));
    net.push_back(new Resistor("R3", 100.0, r,l));
    net.push_back(new Resistor("R4", 300.0, l,n));
    net.push_back(new Resistor("R5", 250.0, r,n));
    simulate(net, 200000, 10, 0.01);*/

    Connection p, l, r, n;
    vector<Component*> net;
    net.push_back(new Battery("Bat", 24.0, p,n));
    net.push_back(new Resistor("R1", 150.0, p,l));
    net.push_back(new Resistor("R2", 50.0, p,r));
    net.push_back(new Capacitor("C3", 1.0, l,r));
    net.push_back(new Resistor("R4", 300.0, l,n));
    net.push_back(new Capacitor("C5", 0.75, r,n));
    simulate(net, 200000, 10, 0.01);

    mem_clean(net);

    return 0;
}

void mem_clean(vector<Component*> net)
{
    for (Component* c : net)
    {
        delete c;
    }
}

void data_control(int argc, char* argv[])
{
    try{
        if (argc > 5 || argc < 5)
        {
            throw std::invalid_argument("Wrong number of arguments");
        }
        for (int i{1}; i < argc; i++)
        {
            if(stod(argv[i]) < 0)
            {
                throw std::invalid_argument("Negative values are not permitted");
            }
        }
    }
    catch(std::exception& e)
    {
        cout << e.what() << endl;
        throw std::invalid_argument("Invalid argument");
    }
}

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
