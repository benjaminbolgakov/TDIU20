#include <stdexcept>
#include <iostream>
#include <initializer_list>
#include <iomanip>
class Connection{
public:
    //Constructor
    Connection();
    //Destructor
    ~Connection();
    //Functions
    Connection& operator=(double voltage);
    operator double();

private:
    double charge;
};

// =======Component========= //
class Component{
public:
    //Constructor
    Component(std::string name,Connection& l, Connection& r);
    //Destructor
    virtual ~Component();
    //Functions
    virtual void update(double time) = 0;
    virtual double getCurrent() = 0;
    virtual double getVoltage() const;
    std::string getId() const;
private:
    std::string id;

protected:
    Connection& left;
    Connection& right;
};

// ========Battery========= //
class Battery : public Component{
public:
    Battery(std::string name, double voltage, Connection& l, Connection& r);
    //~Battery();
    double getCurrent();
    void update(double time) override;
    double getVoltage() const override;
protected:
    double voltage;
};



// ========Resistor========= //
class Resistor : public Component{
public:
    Resistor(std::string name, double resistance, Connection& l, Connection& r);
    //~Battery();
    double getCurrent();
    void update(double time) override;
protected:
    double resistance;
};



// ========Capacitor========= //
class Capacitor : public Component{
public:
    Capacitor(std::string name, double capacitance, Connection& l, Connection& r);
    //~Battery();
    double getCurrent();
    void update(double time) override;
protected:
    double capacitance;
    double charge;
};
