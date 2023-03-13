#pragma once
#include "matrix_t.h"
#include "vector_t.h"

#define BAD_DETERMINANT -100

template <typename T>
std::size_t find_index(const std::vector<T>& vec, const T& value) {
    auto iter = std::find(vec.begin(), vec.end(), value);
    if (iter == vec.end()) {
        return -1; // Element not found
    }
    else {
        return std::distance(vec.begin(), iter);
    }
};

inline bool operator>(const std::vector<double>& vec, double val) {
    for (const auto& elem : vec) {
        if (elem <= val) {
            return false;
        }
    }
    return true;
};
inline bool operator>=(const std::vector<double>& vec, double val) {
    for (const auto& elem : vec) {
        if (elem < val) {
            return false;
        }
    }
    return true;
};
template <typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{";
    for (const auto& elem : s) {
        os << "x_" << elem + 1;
        if (*s.rbegin() != elem) {
            os << ", ";
        }
    }
    os << "}";
    return os;
}

std::vector <double> gaussian_reverse(Matrix A, vector_t B);
std::vector <double> solve(Matrix A, vector_t B);
double determinant_upper_triangle(Matrix A);
std::vector<std::set<int>> generate_combinations(std::vector<int> column_set, int k);
double evaluate(vector_t obj_function, std::vector<double> solution, std::set<int> variable_indices);
void go(std::vector <int>& column_set, std::vector <int>& combination, std::vector <std::set<int>>& combmas, int offset, int k);
std::vector <double> gauss(Matrix A, vector_t B);