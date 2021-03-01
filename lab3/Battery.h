#include "Circuit.h"
// ========Battery========= //
class Battery : public Component{
public:
    double get_current();
    void update(double time);
private:
    double voltage;
};
    // =======|Battery|======== //
