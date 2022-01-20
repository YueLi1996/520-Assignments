#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif complex object and method definitions
 *
 *  A complex object is a struct with two members: real and im. Functions have add,
 *  negate, multiply and magnitude
 *
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex numbers together
 *  \param a The first complex number
 *  \param b The second complex number
 */
Complex add ( Complex a, Complex b );


/*! Negate two complex numbers
 *  \param a The complex number
 *  \param b The complex number
 */
Complex negate ( Complex a );


/*! Multiply two complex numbers together
 *  \param a The complex number
 *  \param b The complex number
 */
Complex multiply ( Complex a, Complex b );


/*! Calculate magnitude of a complex numbers
 *  \param a The complex number
 */
double magnitude ( Complex a );

#endif