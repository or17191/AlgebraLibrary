#ifndef MARIX_H
#define MARIX_H

#include "base.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define self (*this)

namespace AlgebraTAU {

template <typename T> class matrix {
  size_t m_rows, m_columns;
  std::vector<T> arr;

public:
  matrix(size_t rows, size_t columns, const T &x);

  matrix(const std::vector<std::vector<T>> &_arr);

  inline size_t rows() const;
  inline size_t columns() const;

  inline const T &operator()(size_t i, size_t j) const;

  inline T &operator()(size_t i, size_t j);

  matrix<T> transpose() const;

  template <typename F> void map(const F &f);

  T det() const;
  matrix<T> invert() const; // Not implemented
  T trace() const;          // Not implemented

  bool operator==(const matrix<T> &other) const;
  bool operator!=(const matrix<T> &other) const;

  matrix<T> operator+(const matrix<T> &other) const;
  matrix<T> &operator+=(const matrix<T> &other);

  matrix<T> operator-() const;
  matrix<T> operator-(const matrix<T> &other) const;
  matrix<T> &operator-=(const matrix<T> &other);

  matrix<T> operator*(const matrix<T> &other) const;
  matrix<T> &operator*=(const matrix<T> &other);

  vector<column,T> operator*(const vector<column,T> &vec) const;

  matrix<T> operator*(const T &a) const;
  matrix<T> &operator*=(const T &a);
};

template<typename T>
void gaussian_elimination(matrix<T>& m);

template<typename T>
void gram_schmidt(matrix<T>& m); // Not implemented

template<typename T>
void LLL(matrix<T>& m);          // Not implemented

} // namespace AlgebraTAU

#include "matrix.inl"

#endif
