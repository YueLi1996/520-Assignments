#include <iostream>
#include <cmath>
#include "stopwatch.h"
#include "elma/elma.h"


using namespace elma;
using namespace std;


void Stopwatch::start() {
  start_time = high_resolution_clock::now();
}

void Stopwatch::stop() {
  stop_time = high_resolution_clock::now();
  double time_period = (stop_time.time_since_epoch() - start_time.time_since_epoch()).count();
  minutes += (double) (time_period / ((double) (pow(10,9) * 60)));
  seconds += (double) (time_period / (double)(pow(10,9)));
  milliseconds += (double) (time_period / (double(pow(10,6))));
  nanoseconds += (double) time_period;
}

void Stopwatch::reset() {
  minutes = 0.0;
  seconds = 0.0;
  milliseconds = 0.0;
  nanoseconds = 0.0;
}

double Stopwatch::get_minutes(){
  return minutes;
}

double Stopwatch::get_seconds(){
  return seconds;
}

double Stopwatch::get_milliseconds(){
  return milliseconds;
}

double Stopwatch::get_nanoseconds(){
  return nanoseconds;
}
