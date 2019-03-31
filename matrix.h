#ifndef MARIX_H
#define MARIX_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define self (*this)

namespace AlgebraTAU {
template <typename T> class vector;

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

  void gaussian_elimination();
  void gram_schmidt(); // Not implemented
  void LLL();          // Not implemented

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

  vector<T> operator*(const vector<T> &vec) const;

  matrix<T> operator*(const T &a) const;
  matrix<T> &operator*=(const T &a);

  void read_JSON(std::istream &IS);        // Not implemented
  void write_JSON(std::ostream &OS) const; // Not implemented
};
} // namespace AlgebraTAU

#include "matrix.inl"

#endif
