#ifndef _RANDOM_PROCESS_H
#define _RANDOM_PROCESS_H

#include "elma/elma.h"
#include "string.h"

using namespace elma;
using namespace std;

class RandomProcess : public Process {
    public:
    RandomProcess(string name) : Process(name) {}
    void init() {}
    void start() {}
    void update();
    void stop() {}
    
}; 

#endif