#ifndef _FILTER_H
#define _FILTER_H

#include "elma/elma.h"

using namespace elma;
using namespace std;

class Filter : public Process {
    public:
    Filter(string name) : Process(name) {}
    void init() {}
    void start() {}
    void update();
    void stop() {}
    double value();

    private:
    int counter = 0;
    double ave_value = 0;
    double nums[10] = {0,0,0,0,0,0,0,0,0,0};
}; 

#endif
