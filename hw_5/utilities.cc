#include "utilities.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <bits/stdc++.h>



using namespace std;

void sort_by_magnitude(vector<double>& vector) {
    sort(vector.begin(), vector.end(), [](double a, double b) 
    { 
        return abs(a) < abs(b);
    });
}

TypedArray<TypedArray<double>> read_matrix_csv(const string path) {

    TypedArray<TypedArray<double>> result;
    ifstream file;
    file.open (path);
    assert(file.is_open());

    string line, value;
    int col_num = 0, helper = 0;
    while(getline(file, line)) {     
        TypedArray<double> row = TypedArray<double>();
        stringstream row_string (line);
        while(getline(row_string, value, ',')){
            row.set (row.size(), stoi(value));
            col_num++;
        }
        result.set(result.size(),row);
        if(helper == 0) {
            helper = col_num; 
        }
        else {
            if (helper != col_num) {
                cout<< "Invalid matrix"<<endl;
            }
        }
    }
    file.close();

    return result;

}


void write_matrix_csv(const TypedArray<TypedArray<double>> &matrix, const string path) {
    ofstream out;
    out.open(path);

    int row_num = matrix.size();
    for (int i = 0; i < row_num; i++) {
        TypedArray<double> row = matrix.safe_get(i);
        int col = matrix.safe_get(0).size();
        for (int j = 0; j < col; j++) {
            if (j == col - 1) {
                out << row.get(j);
            }
            else{
                out << row.get(j);
                out <<',';
            }
        }
        out << '\n';
    }
    out.close();
}


map<string, int> occurrence_map(const string path) {

    map<string, int> map;
    ifstream file;
    file.open(path);
    assert(file.is_open()); 
    
    string line; 
    while (getline (file, line)) {
        string word; 
        stringstream row_string (line);
        while (getline (row_string, word, ' ')) {

            transform(word.begin(), word.end(), word.begin(), asciitolower);
            
            
            if(is_parentheses_quotes(word[0]) || is_parentheses_quotes(word[word.length()-1])){
                if(word[0] == '(' || word[0] == '\"'){
                    string new_word = "";
                    for (int i = 1; i < word.length(); i++) {
                        new_word += word[i];
                    }
                    
                    map[new_word]++;
                }
                else if (word[word.length() - 1] == ')' || word[word.length() - 1] == '\"') {
                    string new_word = "";
                    for (int i = 0; i < word.length() - 1; i++) {
                        new_word += word[i];
                    }
                   
                    map[new_word]++;
                }
                
            }
            else { 

                bool helper = true;

                for (int i = 0; i < word.length(); i++) {
                    if ( (word[i] <= 'z' && word[i]>= 'a') ||
                         (word[i] <= '9' && word[i]>= '0') ||
                         (word[i] == '\'') ) {
                        
                        }
                    else {
                        helper = !helper;
                    }
                }

                if(helper) {
                    
                    map[word]++;
                }
            }

        }
        
            
    }
    file.close();

    return map;
}


bool is_parentheses_quotes(char in) {
    if (in == '(' || in == '\"' || in == ')') {
        return true;
    }
    return false;
}

// reference: https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case
char asciitolower(char in) {
    if (in <= 'Z' && in >= 'A')
        return in - ('Z' - 'z');
    return in;
}

