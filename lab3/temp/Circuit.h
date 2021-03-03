#include <stdexcept>
#include <iostream>
#include <initializer_list>
#include <iomanip>
#include <vector>


class Connection{
public:
    //Constructor
    Connection(std::string id);
    //Destructor
    ~Connection();
    //Functions
    Connection& operator=(double voltage);
    operator double();
    std::string getId() const;

private:
    double charge;
    std::string id;

};

// =======Component========= //
class Component{
public:
    //Constructor
    Component(std::string name, Connection& l, Connection& r);
    //Destructor
    virtual ~Component();
    //Functions
    virtual void update(double time) = 0;
    virtual double getCurrent() const = 0;
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

    double getCurrent() const;
    void update(double time) override;
    double getVoltage() const override;
protected:
    double voltage;
};



// ========Resistor========= //
class Resistor : public Component{
public:
    Resistor(std::string name, double resistance, Connection& l, Connection& r);

    double getCurrent() const;
    void update(double time) override;
protected:
    double resistance;
};


// ========Capacitor========= //
class Capacitor : public Component{
public:
    Capacitor(std::string name, double capacitance, Connection& l, Connection& r);

    double getCurrent() const;
    void update(double time) override;
protected:
    double capacitance;
    double charge;
};

class Circuit{
public:
    //Constructor
    Circuit();
    //Destructor
    virtual ~Circuit();
    //Functions
    void addComponent(Component* comp);
    void addConnection(std::string id);
    Connection& getCon(std::string id);
    void simulate(double iterations, double nmbPrints, double time);

private:
    void printHeader();
    std::vector<Connection*> connections;
    std::vector<Component*> components;

};
