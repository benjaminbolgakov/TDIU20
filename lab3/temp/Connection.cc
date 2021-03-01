#include "Circuit.h"

//Constructor
Connection::Connection() : charge{0}
{

}
Connection::~Connection()
{

}



//Component
Component::Component(std::string name,Connection& l, Connection&r) : id{name}, left{l}, right{r}
{

}
Component::~Component()
{

}
//Functions
