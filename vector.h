#ifndef MARIX_H
#define MARIX_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#define self (*this)

template <typename T>
class matrix;

template <typename T>
class vector
{
	size_t _size,_is_column_vector;
	std::vector<T> arr;
public:

	vector(size_t size,bool is_column_vector, const T& x = 0);
	vector(const std::vector<T>& _arr);

	inline size_t size() const ;
	inline bool is_column_vector() const;

	inline const T& operator()(size_t i) const;
    inline T& operator()(size_t i) ;

	vector<T> transpose() const ;

	template<typename F>
	void map(const F& f);

	bool operator==(const vector<T>& other) const;
	bool operator!=(const vector<T>& other) const;

	vector<T> operator+(const vector<T>& other) const;
	vector<T>& operator+=(const vector<T>& other);

	vector<T> operator-() const;
	vector<T> operator-(const vector<T>& other) const;
	vector<T>& operator-=(const vector<T>& other);


	vector<T> operator*(const matrix<T>& mat) const;
	vector<T>& operator*=(const matrix<T>& mat);

	vector<T> operator*(const T& a) const;
	vector<T>& operator*=(const T& a);

	void read_JSON(std::istream& IS);
	void write_JSON(std::ostream& OS) const;
};

template<typename T>
T dot(const vector<T>& a, const vector<T>& b);

template<typename T>
vector<T> crose(const vector<T>& a, const vector<T>& b);

#endif
