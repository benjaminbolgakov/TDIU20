#include "Circuit.h"

// =======Circuit======== //
//Constructors
Circuit::Circuit() : connections{}, components{}
{

}

//Destructors
Circuit::~Circuit()
{
    for (Component* comp : components)
    {
        delete comp;
    }
    for (Connection* con : connections)
    {
        delete con;
    }
}
//Functions
void Circuit::simulate(double iterations, double nmbPrints, double time)
{
    this->printHeader();
    for (int i{0}; i < nmbPrints; i++)
    {
        for (int j{0}; j < (iterations/nmbPrints); j++)
        {
            for (Component* c : components)
            {
                c->update(time);
            }
        }
        for (Component* c : components)
        {
            std::cout << std::setprecision(2) << std::fixed << std::setw(2)
                      << c->getVoltage() << "  " << c->getCurrent() << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void Circuit::printHeader()
{
    int index{0};
    for (Component* c : components)
    {
        std::cout << c->getId() << "\t \t";
        index++;
    }
    std::cout << std::endl;
    for (int i{0}; i < index; i++)
    {
        std::cout << "Volt  Curr\t";
    }
    std::cout << std::endl;
}
void Circuit::addComponent(Component* comp)
{
    try{
        for (Component* c : this->components)
        {
            if (c->getId() == comp->getId())
            {
                throw Circuit_Error("Component with that name already exists");
            }
        }
        this->components.push_back(comp);
    }
    catch(Circuit_Error& e)
    {
        std::cout << e.what() << std::endl;
        throw Circuit_Error("Something went wrong when adding a component");
    }
}
void Circuit::addConnection(std::string id)
{
    try{
        for (Connection* c : this->connections)
        {
            if ( c->getId() == id)
            {
                throw Circuit_Error("Connection point with that name already exists");
            }
        }
        this->connections.push_back(new Connection(id));
    }
    catch(Circuit_Error& e)
    {
        std::cout << e.what() << std::endl;
        throw Circuit_Error("Something went wrong when adding a connection");
    }
}
Connection& Circuit::getCon(std::string id)
{
    try{
        for (Connection* c : this->connections)
        {
            if ( c->getId() == id)
            {
                return *c;
            }
        }
        throw Circuit_Error("Connection doesn't exists");
    }
    catch(Circuit_Error& e)
    {
        std::cout << e.what() << id << std::endl;
        throw Circuit_Error("Something went wrong with getting a connection");
    }
}

// =======Connection======== //
//Constructor
Connection::Connection(std::string id) : charge{0}, id{id}
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

std::string Connection::getId() const
{
    return id;
}

// =======Component========= //
//Constructors
Component::Component(std::string name, double value,Connection& l, Connection& r)
    : id{name}, left{l}, right{r}
{
    try{
        if (value <= 0)
        {
            throw Circuit_Error("Components input value must be greater than 0");
        }
    }
    catch(Circuit_Error& e)
    {
        std::cout << e.what() << std::endl;
        throw Circuit_Error("Something went wrong when adding a component");
    }
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
Battery::Battery(std::string name, double value, Connection& l, Connection& r)
    : Component{name,value,l,r}, voltage{value}
{
    l = voltage;
}
//Functions
void Battery::update(double)
{
    left = voltage;
    right = 0;
}
double Battery::getCurrent() const
{
    return 0;
}
double Battery::getVoltage() const
{
    return voltage;
}


// ========Resistor========= //
//Constructor
Resistor::Resistor(std::string name, double value, Connection& l, Connection& r)
    : Component{name,value,l,r}, resistance{value}
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
double Resistor::getCurrent() const
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
Capacitor::Capacitor(std::string name, double value, Connection& l, Connection& r) :
    Component{name,value,l,r}, capacitance{value}, charge{0}
{

}
//Functions
void Capacitor::update(double time)
{
    if (double(left) < double(right))
    {
        double diff = (double(right)-double(left)); //Difference in potential
        double add_charge = (capacitance*(diff-charge))*time; //Charge to add to "storage" and LCC
        charge += add_charge; //Store additional charge
        left = double(left)+add_charge;
        right = double(right)-add_charge;
    }
    else
    {
        double diff = (double(left)-double(right)); //Difference in potential
        double add_charge = (capacitance*(diff-charge))*time; //Charge to add to "storage" and LCC
        charge += add_charge; //Store additional charge
        left = double(left)-add_charge;
        right = double(right)+add_charge;
    }
}
double Capacitor::getCurrent() const
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


// ========Circuit_Error========= //
Circuit_Error::Circuit_Error(std::string& message) throw() : std::logic_error(message)
{

}
