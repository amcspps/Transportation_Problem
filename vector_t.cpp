#include "vector_t.h"

double vector_t::eqNorm() const {
    double res = 0;
    if (this->rows == 1) {
        for (int i = 0; i < this->cols; i++) {
            res += el(0, i) * el(0, i);
        }
    }
    else {
        for (int i = 0; i < this->rows; i++) {
            res += el(i, 0) * el(i, 0);
        }
    }
    res = sqrt(res);
    return res;
}

void vector_t::deleteEl(int _j) {
    for (int j = _j; j < rows - 1; j++)
        addData(el(j + 1, 0), j);
}


double norm(const vector_t& v) { return v.eqNorm(); }

void vector_t::append(vector_t other) {
    int tmp_rows = rows +  other.rows;
    _data.resize(tmp_rows);
    copy(other._data.begin(), other._data.end(), _data.begin() + rows);
    rows = tmp_rows;
}