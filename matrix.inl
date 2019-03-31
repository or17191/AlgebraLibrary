namespace AlgebraTAU {

template <typename T> bool is_upper_triangular(const matrix<T> &m) {
  for (int i = 0; i < m.rows(); ++i)
    for (int j = 0; j < i && j < m.columns(); ++j)
      if (m(i, j) != 0)
        return false;
  return true;
};

template <typename T> bool is_lower_triangular(const matrix<T> &m) {
  for (int i = 0; i < m.rows(); ++i)
    for (int j = i + 1; j < m.columns(); ++j)
      if (m(i, j) != 0)
        return false;
  return true;
}

template <typename T>
vector<column, T> matrix<T>::operator*(const vector<column, T> &vec) const {
  if (columns() != vec.size())
    throw std::invalid_argument("matrix and vector dimensions doesn't agree");
  vector<column, T> res(rows(), true, 0);
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
    : m_rows(rows), m_columns(columns), arr(rows * columns, a) {
  if (rows == 0 || columns == 0)
    throw std::invalid_argument("can't create empty matrices");
}

template <typename T>
matrix<T>::matrix(const std::vector<std::vector<T>> &_arr) {
  if (_arr.size() == 0 || _arr[0].size() == 0)
    throw std::invalid_argument("can't create empty matrices");
  m_rows = _arr.size();
  m_columns = _arr.front().size();
  for (const std::vector<T> &v : _arr)
    if (v.size() != columns())
      throw std::invalid_argument("all rows must be of same size");

  arr = std::vector<T>(rows() * columns());
  int i = 0;
  for (const std::vector<T> &v : _arr)
    for (const T &x : v)
      arr[i++] = x;
}

template <typename T> size_t matrix<T>::rows() const { return m_rows; }

template <typename T> size_t matrix<T>::columns() const { return m_columns; }

template <typename T>
inline const T &matrix<T>::operator()(size_t i, size_t j) const {
  return arr[i * columns() + j];
}

template <typename T> inline T &matrix<T>::operator()(size_t i, size_t j) {
  return arr[i * columns() + j];
}

template <typename T> bool matrix<T>::operator==(const matrix<T> &other) const {
  if (other.columns() != columns() || other.rows() != rows())
    return false;

  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < columns(); ++j)
      if (self(i, j) != other(i, j))
        return false;
  return true;
}

template <typename T> bool matrix<T>::operator!=(const matrix<T> &other) const {
  return !(self == other);
}

template <typename T> matrix<T> matrix<T>::transpose() const {
  using namespace std;
  matrix<T> res(columns(), rows(), 0);

  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < columns(); ++j)
      res(j, i) = self(i, j);

  return res;
}

template <typename T> template <typename F> void matrix<T>::map(const F &f) {
  for (int i = 0; i < rows(); ++i)
    for (int j = 0; j < rows(); ++j)
      self(i, j) = f(self(i, j));
}

template <typename T> void gaussian_elimination(matrix<T> &m) {
  using namespace std;
  int t = 0;
  T r;

  for (int i = 0; i < m.rows() && i < m.columns(); ++i) {
    if (m(i, i) == 0) {
      for (t = i + 1; t < m.rows() && m(t, i) == 0; ++t)
        ;
      if (t >= m.rows()) {
        --i;
        continue;
      }
      if (t < m.rows()) {
        for (int j = 0; j < m.columns(); ++j) {
          swap(m(i, j), m(t, j));
          m(i, j) *= -1;
        }
      } else {
        continue;
      }
    }

    for (t = i + 1; t < m.rows(); ++t) {
      r = m(t, i) / m(i, i);
      for (int j = i; j < m.columns(); ++j) {
        m(t, j) -= r * m(i, j);
      }
    }
  }
}

template <typename T> T matrix<T>::det() const {
  if (rows() != columns())
    throw std::domain_error("can't take determinanent of non-square matrix");

  matrix<T> M = self;
  gaussian_elimination(M);
  T res = 1;
  for (int i = 0; i < rows(); ++i)
    res *= M(i, i);
  return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const matrix<T> &m) {
  using std::to_string;
  std::string res = "";

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
