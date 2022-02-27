#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include "elma/elma.h"

using namespace elma;

class Stopwatch : public Process {
    public:

    void init(){}    // overriding pure virtual
    void update(){}  // overriding pure virtual
    void start();             // starts the timer
    void stop();               // stops the timer
    void reset();              // sets stopwatch to zero
    double get_minutes();      // number of minutes counted, as a double
    double get_seconds();      // number of seconds counted, as a double
    double get_milliseconds(); // number of milliseconds counted, as a double
    double get_nanoseconds();  // number of nanoseconds counted, as a double

    private:
    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point stop_time;
    double minutes = 0;
    double seconds = 0;
    double milliseconds = 0;
    double nanoseconds = 0;
    
}; 

#endif