#include<iostream>
#include<cmath>
#include"integrator.h"

using namespace std;

void Integrator::update() {
  if ( channel("link").nonempty() ) {
    double v = channel("link").latest();
    inte_val += delta() * v;
  }
  // cout<<value()<<"\n";
}


double Integrator::value() {
  return inte_val;
}