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
  size_t _rows, _columns;
  std::vector<T> arr;

public:
  matrix(size_t rows, size_t columns, const T &x);

  matrix(const std::vector<std::vector<T>> &_arr);

  inline size_t rows() const;
  inline size_t columns() const;

  inline const T &operator()(size_t i, size_t j) const;

  inline T &operator()(size_t i, size_t j);

  matrix<T> transpose() const;

  bool is_upper_triangular() const;
  bool is_lower_triangular() const;

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

namespace AlgebraTAU {

template <typename T>
vector<T> matrix<T>::operator*(const vector<T> &vec) const {
  if (!vec.is_column_vector() || columns() != vec.size())
    throw std::invalid_argument("matrix and vector dimensions doesn't agree");
  vector<T> res(rows(), true, 0);
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < columns(); ++j)
      res(i) += self(i, j) * vec(j);
  return res;
}

template <typename T> matrix<T> &matrix<T>::operator+=(const matrix<T> &other) {
  if (columns() != other.columns() || rows() != other.rows())
    throw std::invalid_argument("matrixes must have same shapes");
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < columns(); ++j)
      self(i, j) += other(i, j);
  return self;
}

template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T> &other) const {
  if (columns() != other.columns() || rows() != other.rows())
    throw std::invalid_argument("matrixes must have same shapes");
  auto res = self;
  res += other;
  return res;
}

template <typename T> matrix<T> &matrix<T>::operator-=(const matrix<T> &other) {
  if (columns() != other.columns() || rows() != other.rows())
    throw std::invalid_argument("matrixes must have same shapes");
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < columns(); ++j)
      self(i, j) -= other(i, j);
  return self;
}

template <typename T> matrix<T> matrix<T>::operator-() const {
  auto res = self;
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < columns(); ++j)
      res(i, j) = -res(i, j);
  return res;
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T> &other) const {
  if (columns() != other.columns() || rows() != other.rows())
    throw std::invalid_argument("matrixes must have same shapes");
  auto res = self;
  res -= other;
  return res;
}

template <typename T> matrix<T> &matrix<T>::operator*=(const T &a) {
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < columns(); ++j)
      self(i, j) *= a;
  return self;
}

template <typename T>
matrix<T> matrix<T>::operator*(const matrix<T> &other) const {
  if (columns() != other.rows())
    throw std::invalid_argument("matrixes dimensions don't agree");
  matrix<T> res(rows(), other.columns(), 0);
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < other.columns(); ++j)
      for (int k = 0; k < columns(); ++k)
        res(i, j) += self(i, k) * other(k, j);
  return res;
}

template <typename T> matrix<T> &matrix<T>::operator*=(const matrix<T> &other) {
  if (columns() != other.rows())
    throw std::invalid_argument("matrixes dimensions don't agree");
  self = self * other;
  return self;
}

template <typename T> matrix<T> matrix<T>::operator*(const T &a) const {
  auto res = self;
  res *= a;
  return res;
}

template <typename T> T dot(const matrix<T> &a, const matrix<T> &b) {
  if (a.columns() != b.columns() || a.rows() != b.rows())
    throw std::invalid_argument("matrixes must have same shapes");
  T res = 0;
  for (int i = 0; i < a.rows(); ++i)
    for (int j = 0; j < b.columns(); ++j)
      res += a(i, j) * b(i, j);
  return res;
}

template <typename T>
matrix<T>::matrix(size_t rows, size_t columns, const T &a)
    : _rows(rows), _columns(columns), arr(rows * columns, a) {
  if (rows == 0 || columns == 0)
    throw std::invalid_argument("can't create empty matrices");
}

template <typename T>
matrix<T>::matrix(const std::vector<std::vector<T>> &_arr) {
  if (_arr.size() == 0 || _arr[0].size() == 0)
    throw std::invalid_argument("can't create empty matrices");
  _rows = _arr.size();
  _columns = _arr.front().size();
  for (const std::vector<T> &v : _arr)
    if (v.size() != _columns)
      throw std::invalid_argument("all rows must be of same size");

  arr = std::vector<T>(_rows * _columns);
  int i = 0;
  for (const std::vector<T> &v : _arr)
    for (const T &x : v)
      arr[i++] = x;
}

template <typename T> size_t matrix<T>::rows() const { return _rows; }

template <typename T> size_t matrix<T>::columns() const { return _columns; }

template <typename T>
inline const T &matrix<T>::operator()(size_t i, size_t j) const {
  return arr[i * _columns + j];
}

template <typename T> inline T &matrix<T>::operator()(size_t i, size_t j) {
  return arr[i * _columns + j];
}

template <typename T> bool matrix<T>::operator==(const matrix<T> &other) const {
  if (other._columns != _columns || other._rows != _rows)
    return false;

  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < _columns; ++j)
      if (self(i, j) != other(i, j))
        return false;
  return true;
}

template <typename T> bool matrix<T>::operator!=(const matrix<T> &other) const {
  return !(self == other);
}

template <typename T> matrix<T> matrix<T>::transpose() const {
  using namespace std;
  matrix<T> res(_columns, _rows);

  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < _columns; ++j)
      res(j, i) = self(i, j);

  return res;
}

template <typename T> bool matrix<T>::is_upper_triangular() const {
  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < i && j < _columns; ++j)
      if (self(i, j) != 0)
        return false;
  return true;
}

template <typename T> bool matrix<T>::is_lower_triangular() const {
  for (int i = 0; i < _rows; ++i)
    for (int j = i + 1; j < _columns; ++j)
      if (self(i, j) != 0)
        return false;
  return true;
}

template <typename T> template <typename F> void matrix<T>::map(const F &f) {
  for (int i = 0; i < _rows; ++i)
    for (int j = 0; j < _rows; ++j)
      self(i, j) = f(self(i, j));
}

template <typename T> void matrix<T>::gaussian_elimination() {
  if (is_upper_triangular())
    return;

  using namespace std;
  int t = 0;
  T r;

  for (int i = 0; i < _rows && i < _columns; ++i) {
    if (self(i, i) == 0) {
      for (t = i + 1; t < _rows && self(t, i) == 0; ++t)
        ;
      if (t >= _rows) {
        --i;
        continue;
      }
      if (t < _rows) {
        for (int j = 0; j < _columns; ++j) {
          swap(self(i, j), self(t, j));
          self(i, j) *= -1;
        }
      } else {
        continue;
      }
    }

    for (t = i + 1; t < _rows; ++t) {
      r = self(t, i) / self(i, i);
      for (int j = i; j < _columns; ++j) {
        self(t, j) -= r * self(i, j);
      }
    }
  }
}

template <typename T> T matrix<T>::det() const {
  if (_rows != _columns)
    throw std::domain_error("can't take determinanent of non-square matrix");
  if (is_upper_triangular() || is_lower_triangular()) {
    T res = 1;
    for (int i = 0; i < _rows; ++i)
      res *= self(i, i);
    return res;
  }

  matrix<T> M = self;
  M.gaussian_elimination();
  return M.det();
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
  using namespace std;
  string res = "";

  for (int i = 0; i < m.rows(); ++i) {
    for (int j = 0; j < m.columns(); ++j)
      res += to_string(m(i, j)) + ", ";

    res.pop_back();
    res.back() = '\n';
  }
  res.pop_back();

  return out << res;
}
} // namespace AlgebraTAU

#endif
