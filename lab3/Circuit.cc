#include "Circuit.h"

// ========Circuit========== //
//Constructors
Circuit::Circuit()
{

}
//Destructor
Circuit::~Circuit()
{

}
//Functions
void Circuit::simulate()
{

}
void Circuit::addConnection()
{
    Connection c{};
    std::cout << &c << " " << double(c) << std::endl;
}
void Circuit::addComponent()
{
    //std::cout << "BATTERY: " << b& << std::endl;
}



// =======Component========= //
//Constructors
Circuit::Component::Component(Circuit::Connection& l, Circuit::Connection& r) :
    id{"es"},
    left{l},
    right{r}
{

}
//Destructor
Circuit::Component::~Component()
{

}
//Functions
double Circuit::Component::getVoltage()
{
    double temp = 2.3;
    return temp;
}
std::string Circuit::Component::getId()
{
    return id;
}
void Circuit::Component::update(double time)
{
    time = 2.3;
    std::cout<<time;
}
double Circuit::Component::get_current()
{
    return 3.2;
}

// =======Connection======== //
//Constructor
Circuit::Connection::Connection() : charge{0}
{

}
//Functions
Circuit::Connection& Circuit::Connection::operator=(double charge)
{
    charge = 2.3;
    std::cout<<charge;
    return *this;
}
Circuit::Connection::operator double()
{

    return this->charge;
}
