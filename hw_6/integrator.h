#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H

#include "elma/elma.h"

using namespace elma;
using namespace std;

class Integrator : public Process {
    public:
    Integrator(string name) : Process(name) {}
    void init() {}
    void start() {}
    void update();
    void stop() {}
    double value();

    private:
    double inte_val = 0;
}; 

#endif
