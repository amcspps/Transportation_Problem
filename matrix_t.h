#ifndef MATRIX_H_
#define MATRIX_H_
#pragma once
#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <ranges>
#include <set>
#include <vector>

namespace mat {
    double random(double a, double b);
} // namespace mat

struct Matrix {
    int rows;
    int cols;
    Matrix();
    ~Matrix() {};
    Matrix(std::vector<double> data, int r, int c) { _data = data; rows = r; cols = c; };
    Matrix(const Matrix& M);
    Matrix(const Matrix& M, std::set<int> Cols);
    Matrix(int h, int w);
    Matrix(int h, int w, double el);
    // column-major ordering
    inline double& el(int i, int j) { return _data[i + j * rows]; }
    inline double el(int i, int j) const { return _data[i + j * rows]; }
    // operator[] with multiple parameters is c++23 feature and my linter does not like it
    inline double& operator()(int i, int j) { return el(i, j); }
    inline double operator()(int i, int j) const { return el(i, j); }
    Matrix operator[](const std::set<int> N) const;
    Matrix operator*(const Matrix R) const;
    Matrix operator*(const double n) const;
    Matrix operator/(const double n) const;
    Matrix operator-(const Matrix R) const;
    Matrix operator+(const Matrix R) const;
    void operator=(const Matrix& R);
    Matrix T();
    double infnorm() const;
    inline void write(std::ofstream& fstr) const { fstr.write(reinterpret_cast<const char*>(_data.data()), _data.size() * sizeof(double)); }

    static Matrix eyes(int size);
    static Matrix ThomasAlg(const Matrix& B);

    auto begin() { return _data.begin(); }
    auto end() { return _data.end(); }

    size_t size() { return _data.size(); }

    void deleteEl(int _j);
    void addData(int data, int i, int j = 0);
    void appendDown(Matrix other);
    void appendRight(Matrix other);
    void deleteLastRow();
protected:
    std::vector<double> _data;
    auto colSpan(int index) const;
};

std::ostream& operator<<(std::ostream& os, const Matrix& M);
double infnorm(const Matrix& M);
void matPrint(const Matrix& M);

#endif // MATRIX_H_