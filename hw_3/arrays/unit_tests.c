#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }         

    TEST(DynamicArray, MinValueInArray) {
        DynamicArray * a = DynamicArray_new(); 
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        ASSERT_EQ(DynamicArray_min(a), 1);
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, MaxValueInArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        ASSERT_EQ(DynamicArray_max(a), 11);
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, MedianValueInArrayWithOdd) {
        DynamicArray * a = DynamicArray_new(); 
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        ASSERT_EQ(DynamicArray_median(a), 6); // 1 2 3 4 5 6 7 8 9 10 11
        DynamicArray_destroy(a); 
    }

    TEST(DynamicArray, MedianValueInArrayWithEven) {
        DynamicArray * b = DynamicArray_new();
        DynamicArray_push(b, 2);
        DynamicArray_push(b, 3);
        DynamicArray_push(b, 4);
        DynamicArray_push(b, 5);
        DynamicArray_pop(b);
        DynamicArray_push(b, 5);
        DynamicArray_push_front(b, 1);
        DynamicArray_push(b, 6);
        DynamicArray_push(b, 7);
        DynamicArray_push(b, 8);
        DynamicArray_push(b, 9);
        DynamicArray_push(b, 10);
        DynamicArray_push(b, 11);
        DynamicArray_push(b, 12);
        ASSERT_EQ(DynamicArray_median(b), 6.5); // 1 2 3 4 5 6 7 8 9 10 11 12
        DynamicArray_destroy(b);
    }
    
    TEST(DynamicArray, SumValueEqualToZero) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_EQ(DynamicArray_sum(a), 0);
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, SumValueInArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        ASSERT_EQ(DynamicArray_sum(a), 66);
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, MeanValueInArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        ASSERT_NEAR (DynamicArray_mean(a), 6, 0.0001);
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, FirstValueInArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        ASSERT_EQ(DynamicArray_first(a), 1);
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, LastValueInArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        ASSERT_EQ(DynamicArray_last(a), 11);
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, CopyArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 2);
        DynamicArray_push(a, 3);
        DynamicArray_push(a, 4);
        DynamicArray_push(a, 5);
        DynamicArray_pop(a);
        DynamicArray_push(a, 5);
        DynamicArray_push_front(a, 1);
        DynamicArray_push(a, 6);
        DynamicArray_push(a, 7);
        DynamicArray_push(a, 8);
        DynamicArray_push(a, 9);
        DynamicArray_push(a, 10);
        DynamicArray_push(a, 11);
        char* aStr = DynamicArray_to_string(a);
        DynamicArray* b = DynamicArray_copy(a);
        char* bStr = DynamicArray_to_string(b);
        ASSERT_STREQ(aStr, bStr);
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, RangeArray) {
        DynamicArray * a = DynamicArray_range(0, 1 ,0.1);
        DynamicArray * b = DynamicArray_new();
        DynamicArray_push(b, 0);
        DynamicArray_push(b, 0.1);
        DynamicArray_push(b, 0.2);
        DynamicArray_push(b, 0.3);
        DynamicArray_push(b, 0.4);
        DynamicArray_push(b, 0.5);
        DynamicArray_push(b, 0.6);
        DynamicArray_push(b, 0.7);
        DynamicArray_push(b, 0.8);
        DynamicArray_push(b, 0.9);
        DynamicArray_push(b, 1);
        for(int i = 0; i <DynamicArray_size(a); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(a, i), DynamicArray_get(b, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, RangeArrayWithSameIndex) {
        DynamicArray * a = DynamicArray_range(1, 1 ,0.1);
        DynamicArray * b = DynamicArray_new();
        DynamicArray_push(b, 1);
        for(int i = 0; i <DynamicArray_size(a); i++) {
            ASSERT_EQ(DynamicArray_get(a, i), DynamicArray_get(b, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, ConcatTwoArraies) {
        DynamicArray * a = DynamicArray_range(0, 1 ,0.1);
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_range(0, 2, 0.1);
        DynamicArray * d = DynamicArray_concat(a, b);
        for(int i = 0; i <DynamicArray_size(d); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, i), DynamicArray_get(d, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
    }

    TEST(DynamicArray, ConcatOneEmptyArrayA) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * c = DynamicArray_range(1.1, 2, 0.1);
        DynamicArray * d = DynamicArray_concat(a, b);
        for(int i = 0; i <DynamicArray_size(d); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, i), DynamicArray_get(d, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
    }

    TEST(DynamicArray, ConcatOneEmptyArrayB) {
        DynamicArray * a = DynamicArray_range(0, 1 ,0.1);;
        DynamicArray * b = DynamicArray_new();
        DynamicArray * c = DynamicArray_range(0, 1, 0.1);
        DynamicArray * d = DynamicArray_concat(a, b);
        for(int i = 0; i <DynamicArray_size(d); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(c, i), DynamicArray_get(d, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
    }

    TEST(DynamicArray, TakeArrayWithSmallPositiveNumber) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * b = DynamicArray_take(a, 2);  /* yields [ 1, 2 ] */
        DynamicArray * c = DynamicArray_subarray(a, 0, 2); 
        for(int i = 0; i <DynamicArray_size(c); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(b, i), DynamicArray_get(c, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
    }

    TEST(DynamicArray, TakeArrayWithSmallNegativeNumber) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * d = DynamicArray_take(a, -2);  /* yields [ 4, 5 ] */
        DynamicArray * e = DynamicArray_subarray(a, 3, 5); 
        for(int i = 0; i <DynamicArray_size(e); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(d, i), DynamicArray_get(e, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(d);
        DynamicArray_destroy(e);
    }

    TEST(DynamicArray, TakeArrayWithLargePositiveNumber) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * b = DynamicArray_take(a, 7); /* yields [ 1, 2, 3, 4, 5, 0, 0 ] */
        DynamicArray_push(a, 0);
        DynamicArray_push(a, 0);
        for(int i = 0; i <DynamicArray_size(a); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(a, i), DynamicArray_get(b, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, TakeArrayWithLargeNegativeNumber) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * b = DynamicArray_take(a, -7); /* yields [ 0, 0, 1, 2, 3, 4, 5] */
        DynamicArray_push_front(a, 0);
        DynamicArray_push_front(a, 0);
        for(int i = 0; i <DynamicArray_size(a); i++) {
            ASSERT_DOUBLE_EQ(DynamicArray_get(a, i), DynamicArray_get(b, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
    }

    TEST(DynamicArray, IsValidArray) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        ASSERT_EQ(DynamicArray_is_valid(a), 1);
        DynamicArray * b = DynamicArray_new();
        DynamicArray_destroy(b);
        ASSERT_EQ(DynamicArray_is_valid(b), 0);
        DynamicArray_destroy(a);
    }

}