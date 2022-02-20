#ifndef UTILITIES
#define UTILITIES

#include "typed_array.h"
#include <map>
#include <vector>

using namespace std;

void sort_by_magnitude(vector<double>& vector);

TypedArray<TypedArray<double>> read_matrix_csv(const string path);

void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path);

map<string, int> occurrence_map(const string path);

bool is_parentheses_quotes(char in);

char asciitolower(char in);

#endif