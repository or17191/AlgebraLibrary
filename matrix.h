#ifndef MARIX_H
#define MARIX_H

#include <iostream>
#include <math.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "base.h"

namespace AlgebraTAU
{

template <typename T> class matrix
{
    size_t m_rows, m_columns;
    std::vector<T> arr;

    public:
    matrix(size_t rows, size_t columns, const T& x);

    matrix(const std::vector<std::vector<T>>& _arr);

    inline size_t rows() const;
    inline size_t columns() const;

    inline const T& operator()(size_t i, size_t j) const;

    inline T& operator()(size_t i, size_t j);

    matrix transpose() const;

    template <typename F> void map(const F& f);

    T det() const;
    // matrix invert() const; // Not implemented
    T trace() const;

    bool operator==(const matrix& other) const;
    bool operator!=(const matrix& other) const;

    matrix operator+(const matrix& other) const;
    matrix& operator+=(const matrix& other);

    matrix operator-() const;
    matrix operator-(const matrix& other) const;
    matrix& operator-=(const matrix& other);

    matrix operator*(const matrix& other) const;
    matrix& operator*=(const matrix& other);

    vector<column, T> operator*(const vector<column, T>& vec) const;

    matrix operator*(const T& a) const;
    matrix& operator*=(const T& a);

    vector<row, T> get_row(int i) const;
    vector<column, T> get_column(int i) const;

    void set_row(int i, const vector<row, T>& v);
    void set_column(int j, const vector<column, T>& v);
};

template <typename T> void gaussian_elimination(matrix<T>& m);

template <typename T> void gram_schmidt(matrix<T>& m);

template <typename T> void LLL(matrix<T>& m, const T& delta);

} // namespace AlgebraTAU

#include "matrix.inl"

#endif
