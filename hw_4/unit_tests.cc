#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "gtest/gtest.h"
#include "complex.h"

namespace {

    TEST(TypedArray, PushTypedArray) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.push(Point(3,4,5));
        EXPECT_EQ(b.get(2).x, 3);
        EXPECT_EQ(b.get(2).y, 4);
        EXPECT_EQ(b.get(2).z, 5);
        EXPECT_EQ(b.size(), 3);
    }

    TEST(TypedArray, PopTypedArray) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(2,Point(3,4,5));
        Point c = b.pop();
        EXPECT_EQ(b.size(), 2); 
        EXPECT_EQ(c.x, 3);
        EXPECT_EQ(c.y, 4);
        EXPECT_EQ(c.z, 5);
        EXPECT_EQ(b.get(2).x, 0);
        EXPECT_EQ(b.get(2).y, 0);
        EXPECT_EQ(b.get(2).z, 0);
    }

    TEST(TypedArray, PushFrontTypedArray) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.push_front(Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 3);
        EXPECT_EQ(b.get(0).y, 4);
        EXPECT_EQ(b.get(0).z, 5);
        EXPECT_EQ(b.get(1).x, 1);
        EXPECT_EQ(b.get(1).y, 2);
        EXPECT_EQ(b.get(1).z, 3);
        EXPECT_EQ(b.get(2).x, 2);
        EXPECT_EQ(b.get(2).y, 3);
        EXPECT_EQ(b.get(2).z, 4);
        EXPECT_EQ(b.size(), 3);
    }

    TEST(TypedArray, PopFrontTypedArray) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(2, Point(3,4,5));
        Point c = b.pop_front();
        EXPECT_EQ(c.x, 1);
        EXPECT_EQ(c.y, 2);
        EXPECT_EQ(c.z, 3);
    }

    TEST(TypedArray, ConcatTypedArray) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a.concat(a).concat(a);
        EXPECT_EQ(b.get(0), 0);
        EXPECT_EQ(b.get(1), 1);
        EXPECT_EQ(b.get(2), 0);
        EXPECT_EQ(b.get(3), 1);
        EXPECT_EQ(b.get(4), 0);
        EXPECT_EQ(b.get(5), 1);
    }

    TEST(TypedArray, ReverseTypedArray) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        a.set(2,2);
        TypedArray<int> b = a.reverse();
        EXPECT_EQ(b.get(0), 2);
        EXPECT_EQ(b.get(1), 1);
        EXPECT_EQ(b.get(2), 0);
    }

    TEST(TypedArray, PlusOperatorTypedArray) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a + a + a; 
        EXPECT_EQ(b.get(0), 0);
        EXPECT_EQ(b.get(1), 1);
        EXPECT_EQ(b.get(2), 0);
        EXPECT_EQ(b.get(3), 1);
        EXPECT_EQ(b.get(4), 0);
        EXPECT_EQ(b.get(5), 1);
    }

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Defaults) {
        TypedArray<Point> x;
        Point& y = x.get(3);
        std::cout << x << "\n";
        EXPECT_DOUBLE_EQ(y.magnitude(), 0.0);
    }

    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }    

    TEST(Examples,REAL_AND_IMAGINARY) {
        Complex x(1,2);
        EXPECT_EQ(x.real(), 1);
        EXPECT_EQ(x.imaginary(), 2);
    }

    TEST(Examples,CONJUGATE) {
        Complex x(1,2);
        Complex y = x.conjugate();
        EXPECT_EQ(y.real(), 1);
        EXPECT_EQ(y.imaginary(), -2);
    }

    TEST(Examples,MULTIPLY) {
        Complex x(1,2), y(3,4);
        Complex z = x * y;
        EXPECT_EQ(z.real(), -5);
        EXPECT_EQ(z.imaginary(), 10);
    }

    TEST(Examples,ADD) {
        Complex x(1,2), y(3, 4);
        Complex z = x + y;
        EXPECT_EQ(z.real(), 4);
        EXPECT_EQ(z.imaginary(), 6);
    }

    TEST(Examples,EQUAL) {
        Complex x(1,2), y(1,2), z(2,1);
        ASSERT_TRUE(x==y);
        ASSERT_FALSE(x==z);
    }

    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

}