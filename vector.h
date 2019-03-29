#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

/*
 * CR - This macro means that no one can use `self` as a token in any file that
 * directly (or indirectly) includes your library. While that case is not
 * common, it happens sometimes.
 */
#define self (*this)

namespace AlgebraTAU {
/*
 * CR - I would put all of the forward declarations in one file. Think what
 * would happen if you were to add template arguments to `matrix`.
 */
template <typename T> class matrix;

template <typename T> class vector {
  /*
   * CR -
   * Names starting with underscores are frowned upon.
   * See https://stackoverflow.com/questions/228783/what-are-the-rules-about-using-an-underscore-in-a-c-identifier.
   * I like having members start with `m_`.
   *
   * Also, why do you need a separate variable for size? `std::vector` already
   * has one.
   */
  size_t _size;
  /*
   * CR -
   * Is the concept of a "column vector" necessary to implement a vector?
   * I believe not. Instead I would do something like:
   * template<class T>
   * class column_vector: public vector<T> {};
   *
   * This approach simplifies the vector class, and makes sure the types of
   * vectors are enforced at compile time.
   */
  bool _is_column_vector;
  std::vector<T> arr;

public:
  /*
   * CR - Change the signature to `vector(size_t, const T& x={})`
   * This makes the syntax `vector(5)` legal. See `std::vector`'s constructors.
   */
  vector(size_t size, bool is_column_vector, const T &x);

  /*
   * CR - Count the copies this signature requires from the vector in difference
   * cases.
   */
  vector(const std::vector<T> &_arr, bool is_column_vector);

  inline size_t size() const;
  inline bool is_column_vector() const;

  inline const T &operator()(size_t i) const;
  inline T &operator()(size_t i);

  /*
   * CR - I would avoid implementing that right now. Wait until you get your
   * `column_vector` and `row_vector` types straight.
   */
  vector<T> transpose() const;

  template <typename F> void map(const F &f);

  /*
   * CR - This is a manner of personal choice, but I would implement those
   * functions as friend functions and not as member functions.
   *
   * My general rules are:
   * - If the function doesn't need to know how the class is implemented, use a
   *   free function. For example, I would make `transpose` a free function.
   * - If the function needs to know how the class is implemented, and takes two
   *   or more equivalent instances of the same class, use a friend function.
   *   For example, I would make all of the out-of-place operators friend
   *   functions (although they might also be free functions).
   * - If the function needs to know how the class is implemented, and it takes
   *   one instance of that class (or operates on an instance of the class while
   *   taking more than one instance), use a member function. For example,
   *   `size`, `operator()` and all of the in-place operators should be member
   *   functions.
   *
   *
   * Also, you can change your signature to
   * `bool operator==(const vector& other) const`. You don't need to specify
   * `T`.
   */
  bool operator==(const vector<T> &other) const;
  bool operator!=(const vector<T> &other) const;

  vector<T> operator+(const vector<T> &other) const;
  vector<T> &operator+=(const vector<T> &other);

  vector<T> operator-() const;
  vector<T> operator-(const vector<T> &other) const;
  vector<T> &operator-=(const vector<T> &other);

  /*
   * CR - Those functions allow the syntax v * m, but not the syntax m * v. The
   * only way to have full control of the order of arguments is to use a friend
   * function. This makes implementing `v * m` in vector and `m * v` in matrix
   * redundant.
   */
  vector<T> operator*(const matrix<T> &mat) const;
  vector<T> &operator*=(const matrix<T> &mat);

  vector<T> operator*(const T &a) const;
  vector<T> &operator*=(const T &a);

  /*
   * CR -
   *
   * - When not implementing a function, comment out the whole function
   *   definition. This would trigger a compilation error if you try to use it.
   *   The current state would trigger a linkage error instead.
   * - This function should be a static method, since it creates a new object.
   *   Otherwise, I would need to create and initialize the object in two
   *   separate steps.
   * - Use snake_case for your parameter names.
   */
  void read_JSON(std::istream &IS);        // Not implemented
  void write_JSON(std::ostream &OS) const; // Not implemented
};
} // namespace AlgebraTAU

/*
 * CR - If you chose to separate the implementation and definition, you can go
 * an extra step and put all of the implementations in a separate file called
 * `vector.inl`, and include it in your `vector.h`. This is some sort of a
 * substitute for using `.cpp` files. Notice, that this step is optional, and I
 * offer it since you already chose to separate implementation and definition.
 */

namespace AlgebraTAU {
template <typename T> template <typename F> void vector<T>::map(const F &f) {
  for (int i = 0; i < size(); ++i)
    self(i) = f(self(i));
}

template <typename T> vector<T> &vector<T>::operator*=(const T &a) {
  for (int i = 0; i < size(); ++i)
    self(i) *= a;
  return self;
}

template <typename T> vector<T> vector<T>::operator*(const T &a) const {
  auto res = self;
  res *= a;
  return res;
}

template <typename T> vector<T> &vector<T>::operator+=(const vector<T> &other) {
  if (size() != other.size() || is_column_vector() != other.is_column_vector())
    throw std::invalid_argument("vectors must have same shapes");
  for (int i = 0; i < size(); ++i)
    self(i) += other(i);
  return self;
}

template <typename T>
vector<T> vector<T>::operator+(const vector<T> &other) const {
  auto res = self;
  res += other;
  return res;
}

template <typename T> vector<T> &vector<T>::operator-=(const vector<T> &other) {
  if (size() != other.size() || is_column_vector() != other.is_column_vector())
    throw std::invalid_argument("vectors must have same shapes");
  for (int i = 0; i < size(); ++i)
    self(i) -= other(i);
  return self;
}

template <typename T>
vector<T> vector<T>::operator-(const vector<T> &other) const {
  auto res = self;
  res -= other;
  return res;
}

template <typename T> vector<T> vector<T>::operator-() const {
  auto res = self;
  for (int i = 0; i < size(); ++i)
    res(i) = -self(i);
  return res;
}

template <typename T> size_t vector<T>::size() const { return _size; }

template <typename T> bool vector<T>::is_column_vector() const {
  return _is_column_vector;
}

template <typename T> const T &vector<T>::operator()(size_t i) const {
  return arr[i];
}

template <typename T> T &vector<T>::operator()(size_t i) { return arr[i]; }

template <typename T>
vector<T> vector<T>::operator*(const matrix<T> &mat) const {
  if (is_column_vector() || size() != mat.rows())
    throw std::invalid_argument("matrix and vector dimensions doesn't agree");
  vector<T> res(mat.columns(), false, 0);
  for (int i = 0; i < mat.rows(); ++i)
    for (int j = 0; j < mat.columns(); ++j)
      res(j) += self(i) * mat(i, j);
  return res;
}

template <typename T> vector<T> &vector<T>::operator*=(const matrix<T> &mat) {
  if (is_column_vector() || size() != mat.rows())
    throw std::invalid_argument("matrix and vector dimensions doesn't agree");
  self = self * mat;
  return self;
}

template <typename T>
vector<T>::vector(size_t size, bool is_column_vector, const T &a)
    : _size(size), _is_column_vector(is_column_vector), arr(size, a) {
  if (_size == 0)
    throw std::invalid_argument("can't create empty vectors");
}

template <typename T>
vector<T>::vector(const std::vector<T> &_arr, bool is_column_vector)
    : _size(_arr.size()), _is_column_vector(is_column_vector), arr(_arr) {
  if (_size == 0)
    throw std::invalid_argument("can't create empty vectors");
}

template <typename T> T dot(const vector<T> &a, const vector<T> &b) {
  if (a.size() != b.size() || a.is_column_vector() != b.is_column_vector())
    throw std::invalid_argument("vectos must have same shapes");
  T res = 0;
  for (int i = 0; i < a.size(); ++i)
    res += a(i) * b(i);
  return res;
}

template <typename T> bool vector<T>::operator==(const vector<T> &other) const {
  if (size() != other.size() || is_column_vector() != other.is_column_vector())
    return false;
  for (int i = 0; i < size(); ++i)
    if (self(i) != other(i))
      return false;
  return true;
}

template <typename T> bool vector<T>::operator!=(const vector<T> &other) const {
  return !(self == other);
}

template <typename T> vector<T> vector<T>::transpose() const {
  T res = self;
  res._is_column_vector = !res._is_column_vector;
  return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
  /*
   * CR
   * - You can append elements directly to `out`. You don't need to create an
   *   additional string.
   * - Replace `using namespace std;` with `using std::to_string;`.
   *   This is the difference between `from std import *` and `from std import
   *   to_string`.
   */
  using namespace std;
  string res = "";

  if (v.is_column_vector())
    res += "(";

  for (int i = 0; i < v.size(); ++i)
    res += to_string(v(i)) + ", ";

  res.pop_back();
  res.pop_back();

  if (v.is_column_vector())
    res += ")^T";

  return out << res;
}
} // namespace AlgebraTAU

#endif
