#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Circuit.h"

using namespace std;

void data_control(int argc, char* argv[]);
int main(int argc, char* argv[])
{
    //Args:
    // Iterations, iterations to print, time-interval, battery voltage
    data_control(argc,argv);

    double in_iterations = atof(argv[1]);
    double in_prints = atof(argv[2]);
    double in_interval = atof(argv[3]);
    double in_bat_voltage = atof(argv[4]);

    Circuit c1;
    c1.addConnection("p");
    c1.addConnection("n");
    c1.addConnection("q1");
    c1.addConnection("q2");
    c1.addComponent(new Battery("Bat", in_bat_voltage, c1.getCon("p"), c1.getCon("n")));
    c1.addComponent(new Resistor("R1", 6.0, c1.getCon("p"),c1.getCon("q1")));
    c1.addComponent(new Resistor("R2", 4.0, c1.getCon("q1"),c1.getCon("q2")));
    c1.addComponent(new Resistor("R3", 8.0, c1.getCon("q2"),c1.getCon("n")));
    c1.addComponent(new Resistor("R4", 12.0, c1.getCon("q1"), c1.getCon("n")));
    c1.simulate(in_iterations,in_prints,in_interval);

    Circuit c2;
    c2.addConnection("p");
    c2.addConnection("n");
    c2.addConnection("r");
    c2.addConnection("l");
    c2.addComponent(new Battery("Bat", in_bat_voltage, c2.getCon("p"), c2.getCon("n")));
    c2.addComponent(new Resistor("R1", 150.0, c2.getCon("p"),c2.getCon("l")));
    c2.addComponent(new Resistor("R2", 50.0, c2.getCon("p"),c2.getCon("r")));
    c2.addComponent(new Resistor("R3", 100.0, c2.getCon("r"),c2.getCon("l")));
    c2.addComponent(new Resistor("R4", 300.0, c2.getCon("l"), c2.getCon("n")));
    c2.addComponent(new Resistor("R5", 250.0, c2.getCon("r"), c2.getCon("n")));
    c2.simulate(in_iterations,in_prints,in_interval);

    Circuit c3;
    c3.addConnection("p");
    c3.addConnection("n");
    c3.addConnection("l");
    c3.addConnection("r");
    c3.addComponent(new Battery("Bat", in_bat_voltage, c3.getCon("p"),c3.getCon("n")));
    c3.addComponent(new Resistor("R1", 150.0, c3.getCon("p"),c3.getCon("l")));
    c3.addComponent(new Resistor("R2", 50.0, c3.getCon("p"),c3.getCon("r")));
    c3.addComponent(new Capacitor("C3", 1.0, c3.getCon("l"), c3.getCon("r")));
    c3.addComponent(new Resistor("R4", 300.0, c3.getCon("l"), c3.getCon("n")));
    c3.addComponent(new Capacitor("C5", 0.75, c3.getCon("r"), c3.getCon("n")));
    c3.simulate(in_iterations,in_prints,in_interval);




    return 0;
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
