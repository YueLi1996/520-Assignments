#include <iostream>
#include <random>
#include <time.h>
#include "random_process.h"

void RandomProcess::update() {
  double random_num = (double) rand()/RAND_MAX;
  // std::cout<<"random num is "<<random_num<<"\n";
  channel("link").send(random_num);
}