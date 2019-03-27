#ifndef VECTOR_H
#define VECTOR_H

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
	size_t _size;
	bool _is_column_vector;
	std::vector<T> arr;
public:

	vector(size_t size,bool is_column_vector, const T& x);
	vector(const std::vector<T>& _arr, bool is_column_vector);

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

	void read_JSON(std::istream& IS); //Not implemented
	void write_JSON(std::ostream& OS) const; //Not implemented
};



template<typename T>
template<typename F>
void vector<T>::map(const F& f){
	for(int i = 0; i < size(); ++i)
		self(i) = f(self(i));
}


template<typename T>
vector<T>& vector<T>::operator*=(const T& a){
	for(int i = 0; i < size(); ++i)
		self(i) *= a;
	return self;
}

template<typename T>
vector<T> vector<T>::operator*(const T& a) const{
	auto res = self;
	res *= a;
	return res;
}

template<typename T>
vector<T>& vector<T>::operator+=(const vector<T>& other){
	if(size() != other.size() || is_column_vector() != other.is_column_vector()) throw std::invalid_argument("vectors must have same shapes");
	for(int i = 0; i < size(); ++i)
		self(i) += other(i);
	return self;
}

template<typename T>
vector<T> vector<T>::operator+(const vector<T>& other) const{
	auto res = self;
	res += other;
	return res;
}

template<typename T>
vector<T>& vector<T>::operator-=(const vector<T>& other){
	if(size() != other.size() || is_column_vector() != other.is_column_vector()) throw std::invalid_argument("vectors must have same shapes");
	for(int i = 0; i < size(); ++i)
		self(i) -= other(i);
	return self;
}

template<typename T>
vector<T> vector<T>::operator-(const vector<T>& other) const{
	auto res = self;
	res -= other;
	return res;
}

template<typename T>
vector<T> vector<T>::operator-() const{
	auto res = self;
	for(int i = 0; i < size(); ++i)
		res(i) = -self(i);
	return res;
}

template<typename T>
size_t vector<T>::size() const { return _size; }

template<typename T>
bool vector<T>::is_column_vector() const { return _is_column_vector; }


template<typename T> 
const T& vector<T>::operator()(size_t i) const { return arr[i]; }


template<typename T> 
T& vector<T>::operator()(size_t i) { return arr[i]; }

template<typename T>
vector<T> vector<T>::operator*(const matrix<T>& mat) const{
	if(is_column_vector() || size() != mat.rows()) throw std::invalid_argument("matrix and vector dimensions doesn't agree");
	vector<T> res(mat.columns(),false,0);
	for(int i = 0; i < mat.rows(); ++i)
		for(int j = 0; j < mat.columns(); ++j)
			res(j) += self(i)*mat(i,j);
	return res;
}

template<typename T>
vector<T>& vector<T>::operator*=(const matrix<T>& mat) {
	if(is_column_vector() || size() != mat.rows()) throw std::invalid_argument("matrix and vector dimensions doesn't agree");
	self = self * mat;
	return self;
}


template<typename T>
vector<T>::vector(size_t size, bool is_column_vector, const T& a) : _size(size),_is_column_vector(is_column_vector), arr(size,a){
	if(_size == 0) throw std::invalid_argument("can't create empty vectors");
} 

template<typename T>
vector<T>::vector(const std::vector<T>& _arr, bool is_column_vector) : _size(_arr.size()), _is_column_vector(is_column_vector), arr(_arr){
	if(_size == 0) throw std::invalid_argument("can't create empty vectors");
} 

template<typename T>
T dot(const vector<T>& a, const vector<T>& b){
	if(a.size() != b.size() || a.is_column_vector() != b.is_column_vector()) throw std::invalid_argument("vectos must have same shapes");
	T res = 0;
	for(int i = 0; i < a.size(); ++i)
		res += a(i) * b(i);
	return res;
}

template<typename T>
bool vector<T>::operator==(const vector<T>& other) const{
	if(size() != other.size() || is_column_vector() != other.is_column_vector()) return false;
	for (int i = 0; i < size(); ++i)
		if(self(i) != other(i))
			return false;
	return true;	
}

template<typename T>
bool vector<T>::operator!=(const vector<T>& other) const{
	return !(self == other);
}


template<typename T>
vector<T> vector<T>::transpose() const{
	T res = self;
	res._is_column_vector = !res._is_column_vector;
	return res;
}


template<typename T>
std::string to_string(const vector<T>& v) {
	using namespace std;
	string res = "";

	if(v.is_column_vector()) res += "(";

	for(int i = 0; i < v.size(); ++i)
		res += to_string(v(i)) + ", ";

	res.pop_back();
	res.pop_back();

	if(v.is_column_vector()) res += ")^T";
	return res;
}


template<typename T>
std::ostream& operator<<(std::ostream& out,const vector<T>& m) {
	return out << to_string(m);
}

#endif
