#ifndef VECTOR_H_
#define VECTOR_H_
#pragma once
#include "matrix_t.h"

struct vector_t : public Matrix {
    vector_t() : Matrix(0, 0) {};
    vector_t(int h) : Matrix(h, 1) {};
    vector_t(std::vector<double> data, int cols) : Matrix(data, 1, cols) {};
    vector_t(Matrix& mat) : Matrix(mat) {
        rows *= cols;
        cols = 1;
    };
    inline double& operator[](const int i) { return el(i, 0); }
    inline double operator[](const int i) const { return el(i, 0); }
    bool operator<(const double R) const {
        for (double el : _data) {
            if (el >= R) {
                return false;
            }
        }
        return true;
    }
    void push_back(double el) {
        _data.push_back(el);
        rows++;
    }
    void pop_back() {
        _data.pop_back();
        rows--;
    }
    double eqNorm() const;
    void deleteEl(int _j);
    void insertEl(int _j, int data) { _data.insert(_data.begin() + _j, data); };
    void append(vector_t other);
};
double norm(const vector_t& v);


#endif // VECTOR_H_