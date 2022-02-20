#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "gtest/gtest.h"
#include "utilities.h"
#include <vector>


namespace {

    TEST(Utilities, SortByMagnitude) {
        std::vector<double> vec = {1, -5, 2, -3, 4, 6};
        sort_by_magnitude(vec);
        std::vector<double> exp_vec = {1, 2, -3, 4, -5, 6};
        EXPECT_EQ(vec, exp_vec);        
    }

    TEST(Utilities, ReadMatrixCsv){
        TypedArray<TypedArray<double>> test_matrix = read_matrix_csv("../test1.csv");
        TypedArray<double> test_array1 = test_matrix.get(0);
        TypedArray<double> test_array2 = test_matrix.get(1);
        EXPECT_DOUBLE_EQ(test_array1.get(0), 1);
        EXPECT_DOUBLE_EQ(test_array1.get(1), 2);
        EXPECT_DOUBLE_EQ(test_array2.get(0), 3);
        EXPECT_DOUBLE_EQ(test_array2.get(1), 4);
    }

    TEST(Utilities, ReadBadMatrixCsv){
        TypedArray<TypedArray<double>> test_matrix = read_matrix_csv("../test2.csv");
    }

    TEST(Utilities, WriteMatrixCsv){
        TypedArray<double> array1 = TypedArray<double>();
        TypedArray<double> array2 = TypedArray<double>();
        TypedArray<TypedArray<double>> matrix = TypedArray<TypedArray<double>>();
        array1.set(0, 1);
        array1.set(1, 2);

        array2.set(0, 3);
        array2.set(1, 4);

        matrix.set(0, array1);
        matrix.set(1, array2);
        write_matrix_csv(matrix, "../test3.csv");
    }

    TEST(Occurrence, OccurrenceMap) {
        std::map<string, int> map = occurrence_map("../test4.txt");

        int val1 = map["10xgenomics"];
        int val2 = map["a"];
        int val3 = map["are"];
        int val4 = map["i'm"];

        EXPECT_EQ(val1, 1);
        EXPECT_EQ(val2, 1);
        EXPECT_EQ(val3, 1);
        EXPECT_EQ(val4, 1);
    }


}