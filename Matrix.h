#pragma once
#include <stdio.h>
#include <fstream> 
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

using std::vector;

class Matrix
{
private:
    int m_rowSize;
    int m_colSize;
    vector<vector<double>> m_matrix;

public:
    Matrix(int, int, double);
    Matrix(const char*);
    //Matrix(const Matrix&);
    Matrix();

    // Матричные операции
    Matrix operator+(Matrix&);
    Matrix operator-(Matrix&);
    Matrix operator*(Matrix&);
    Matrix transpose();

    double& operator()(const int&, const int&);
    unsigned getRows() const;
    unsigned getCols() const;
    void print() const;
};