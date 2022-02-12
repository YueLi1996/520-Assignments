#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

double Complex::real() {
    return re;
}

double Complex::imaginary() {
    return im;
}

Complex Complex::conjugate() {
    return Complex(re, -1 * im);
}

Complex Complex::operator*(const Complex& b) {
    double re_part = this->re * b.re - this->im * b.im;
    double im_part = this->re * b.im + this->im * b.re;
    return Complex(re_part, im_part);
}

Complex Complex::operator+(const Complex& b) {
    return Complex(re + b.re, im + b.im);
}

bool Complex::operator==(const Complex& b) const{
    return re == b.re && im == b.im;
}