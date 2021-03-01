#include <stdexcept>
#include <iostream>
#include <initializer_list>
class Circuit{
public:
    // ========Circuit========== //
    //Constructors
    Circuit();
    //Deconstructors
    ~Circuit();
    void simulate();
    void addConnection();
    void addComponent();

    // =======|Circuit|========= //

    // =======Connection======== //
public: class Connection{
public:
    //Constructor
    Connection();
    //Functions
    Connection& operator=(double charge);
    operator double();
private:
    double charge;
};
    // ======|Connection|======= //



    // =======Component========= //
public: class Component{
public:
    //Constructors
    Component();
    Component(Circuit::Connection& l, Circuit::Connection& r);
    //Destructor
    virtual ~Component();
    //Functions
    virtual void update(double time);
    virtual double get_current();
    double getVoltage();
    std::string getId();
private:
    std::string id;
protected:
    Connection& left;
    Connection& right;
};
    // ======|Component|======== //







    // ========Circuit========== //
private:

};
