#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#define self (*this)

namespace AlgebraTAU {
template <typename T> class matrix;

template <typename T> class vector {
  bool m_is_column_vector;
  std::vector<T> arr;

public:
  vector(size_t size, bool is_column_vector, const T &x);
  vector(const std::vector<T> &_arr, bool is_column_vector);

  inline size_t size() const;
  inline bool is_column_vector() const;

  inline const T &operator()(size_t i) const;
  inline T &operator()(size_t i);

  vector<T> transpose() const;

  template <typename F> void map(const F &f);

  bool operator==(const vector &other) const;
  bool operator!=(const vector &other) const;

  vector operator+(const vector &other) const;
  vector &operator+=(const vector &other);

  vector operator-() const;
  vector operator-(const vector &other) const;
  vector &operator-=(const vector &other);

  vector operator*(const matrix<T> &mat) const;
  vector &operator*=(const matrix<T> &mat);

  vector operator*(const T &a) const;
  vector &operator*=(const T &a);

  //void read_JSON(std::istream &IS);        // Not implemented
  //void write_JSON(std::ostream &OS) const; // Not implemented
};
} // namespace AlgebraTAU

#include "vector.inl"
#endif
