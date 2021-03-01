#include "Circuit.h"

// =======Connection======== //
//Constructor
Connection::Connection() : charge{0}
{

}
Connection::~Connection()
{

}
//Functions
Connection& Connection::operator=(double voltage)
{
    charge = voltage;
    return *this;
}
Connection::operator double()
{
    return this->charge;
}

// =======Component========= //
//Constructors
Component::Component(std::string name,Connection& l, Connection& r) : id{name}, left{l}, right{r}
{

}
Component::~Component()
{

}
//Functions
double Component::getVoltage() const
{
    if (double(left) < double(right))
    {
        return (right-left);
    }
    else
    {
        return (left-right);
    }
}
std::string Component::getId() const
{
    return id;
}


// ========Battery========= //
//Constructors
Battery::Battery(std::string name, double voltage, Connection& l, Connection& r) : Component{name,l,r}, voltage{voltage}
{
    l = voltage;
}
//Functions
void Battery::update(double time)
{
    left = voltage;
    right = 0;
}
double Battery::getCurrent()
{
    return 0;
}
double Battery::getVoltage() const
{
    return voltage;
}


// ========Resistor========= //
//Constructor
Resistor::Resistor(std::string name, double resistance, Connection& l, Connection& r) : Component{name,l,r},
                                                                               resistance{resistance}
{

}
//Functions
void Resistor::update(double time)
{
    //Moves charge from the most charged connection-point to the
    //least charged connection-point
    if (double(left) < double(right))
    {
        double move = (double(right)-double(left))/resistance*time; //Amount to "move"
        right = double(right)-move;
        left = double(left)+move;
    }
    else
    {
        double move = (double(left)-double(right))/resistance*time; //Amount to "move"
        right = double(right)+move;
        left = double(left)-move;
    }
}
double Resistor::getCurrent()
{
    //Returns the current through a resistor
    if (double(left) < double(right))
    {
        return (right-left)/resistance;
    }
    else
    {
        return (left-right)/resistance;
    }
}

// ========Capacitor========= //
//Constructors
Capacitor::Capacitor(std::string name, double capacitance, Connection& l, Connection& r) :
    Component{name,l,r}, capacitance{capacitance}, charge{0}
{

}
//Functions
void Capacitor::update(double time)
{
    if (double(left) < double(right))
    {
        //double stored_charge += double(right);
        //left = double(left)+stored_charge;
        double diff = (double(right)-double(left)); //Difference in potential
        double add_charge = (capacitance*(diff-charge))*time; //Charge to add to "storage" and LCC
        charge += add_charge; //Store additional charge
        left = double(left)+add_charge;
        right = double(right)-add_charge;
        //left += add_charge;
        //right -= add_charge;
    }
    else
    {
        double diff = (double(left)-double(right)); //Difference in potential
        double add_charge = (capacitance*(diff-charge))*time; //Charge to add to "storage" and LCC
        charge += add_charge; //Store additional charge
        left = double(left)-add_charge;
        right = double(right)+add_charge;
        //left -= add_charge;
        //right += add_charge;
    }
}
double Capacitor::getCurrent()
{
    if (double(left) < double(right))
    {
        return capacitance*((double(right)-double(left))-charge);
    }
    else
    {
        return capacitance*((double(left)-double(right))-charge);
    }
}
