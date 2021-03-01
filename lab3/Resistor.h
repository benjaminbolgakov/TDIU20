#include "Circuit.h"
// =======Resistor========= //
public: class Resistor : public Component{
public:
    double get_current();
    void update(double time);
private:
    double resistance;
};
// ======|Resistor|======== //
