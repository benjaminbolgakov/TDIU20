#include "Circuit.h"
// =======Capacitor======== //
public: class Capacitor : public Component{
public:
    double get_current();
    void update(double time);
private:
    double capacitance;
    double charge;
};
// ======|Capacitor|======= //
