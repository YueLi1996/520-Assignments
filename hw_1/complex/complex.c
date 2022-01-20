#include "complex.h"
#include <math.h>

Complex add(Complex a, Complex b)
{
  return (Complex){
      a.real + b.real,
      a.im + b.im};
}

Complex negate(Complex a)
{
  return (Complex){
      a.real * (-1),
      a.im * (-1)};
}

Complex multiply(Complex a, Complex b)
{
  return (Complex){
      a.real * b.real - a.im * b.im,
      a.real * b.im + b.real * a.im};
}

double magnitude(Complex a)
{
  return (double)sqrt(a.real * a.real + a.im * a.im);
}