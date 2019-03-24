#ifndef MARIX_H
#define MARIX_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename T>
class matrix
{
	size_t _rows,_columns;
	std::vector<T> arr;
public:

	matrix(size_t rows,size_t columns) :  _rows(rows), _columns(columns), arr(rows*columns){
		if(rows == 0 || columns == 0) throw std::invalid_argument("can't create empty matrices");
	}

	matrix(const std::vector<std::vector<T> >& _arr){
		if(_arr.size() == 0) throw std::invalid_argument("can't create empty matrices");
		_rows = _arr.size();
		_columns = _arr.front().size();
		for(const std::vector<T>& v : _arr) 
			if(v.size() != _columns) 
				throw std::invalid_argument("all rows must be of same size");
		
		arr = std::vector<T>(_rows*_columns);
		int i = 0;
		for(const std::vector<T>& v : _arr)
			for(const T& x : v)
				arr[i++] = x;
	}

	size_t rows() const { return _rows; }
	size_t columns() const { return _columns; }

#ifdef WITH_ACCESSES
	const T& operator()(size_t i, size_t j) const{
		if(i >= _rows || j >= _columns) throw std::length_error("matrix index out of range");
		return arr[i*_columns + j];
	}

    T& operator()(size_t i, size_t j) {
		if(i >= _rows || j >= _columns) throw std::length_error("matrix index out of range");
		return arr[i*_columns+ j];
	}
#endif

	bool operator==(const matrix<T>& other) const{
		if(other._columns != _columns || other._rows != _rows) return false;

		for(int i = 0; i < _rows; ++i)
			for (int j = 0; j < _columns; ++j)
				if(arr[j*_rows + i] != arr[j*_rows + i])
					return false;
		return true;
	}

	bool operator!=(const matrix<T>& other) const{
		return !(*this == other);
	}

	T dot(const matrix<T>& other) const{
		if(other._columns != _columns || other._rows != _rows) throw std::invalid_argument("matrixes must have same shapes");
		T res = 0;
		for (int i = 0; i < _rows; ++i)
			for (int j = 0; j < _columns; ++j)
				res += arr[i*_columns + j] * other.arr[i*_columns + j];
	}

	matrix<T> transpose() const {
		using namespace std;
		matrix<T> res(_columns,_rows);

		for(int i = 0; i < _rows; ++i)
			for(int j = 0; j < _columns ; ++j)
				res.arr[j*_rows + i] = arr[i*_columns+j];
	 
		return res;
	}

	bool is_upper_triangular() const{
		for(int i = 0; i < _rows; ++i)
			for(int j = 0; j < i && j < _columns; ++j)
				if(arr[i*_columns + j] != 0)
					return false;
		return true;
	}

	bool is_lower_triangular() const{
		for(int i = 0; i < _rows; ++i)
			for(int j = i + 1; j < _columns; ++j)
				if(arr[i*_columns + j] != 0)
					return false;
		return true;
	}

	template<typename F>
	void map(const F& f){
		for(int i = 0; i < _rows; ++i)
			for(int j = 0; j < _rows; ++j)
				arr[i*_columns + j] = f(arr[i*_columns + j]);

	}

	void gaussian_elimination() {
		if(is_upper_triangular()) return;

		using namespace std;
		int t = 0;
		T r;

		for(int i = 0; i < _rows && i < _columns; ++i){
			if(arr[i*_columns + i] == 0){
				for(t = i+1; t < _rows && arr[t*_columns + i] == 0; ++t);
				if(t >= _rows){
					--i;
					continue;
				}
				for(int j = 0; j < _columns; ++j){
					swap(arr[i*_columns + j], arr[t*_columns + j]);
					arr[i*_columns + j] *= -1;
				}
			}

			for(t = i+1; t < _rows; ++t){
				r = arr[t*_columns + i] / arr[i*_columns + i];
				for (int j = i; j < _columns; ++j){
					arr[t*_columns + j] -= r*arr[i*_columns + j];
				}
			}
		}
	}

	T det() const{
		if(_rows != _columns) throw std::domain_error("can't take determinanent of non-square matrix");
		if(is_upper_triangular() || is_lower_triangular()){
			T res = 1;
			for(int i = 0; i < _rows; ++i) res *= arr[i*_columns + i];
			return res;
		} 

		matrix<T> M = *this;
		M.gaussian_elimination();
		return M.det();
	}



};

#ifdef WITH_ACCESSES
template<typename T>
std::string to_string(const matrix<T>& m) {
	using namespace std;
	string res = "";

	for(int i = 0; i < m.rows(); ++i){
		for(int j = 0; j < m.columns(); ++j)
			res += to_string(m(i,j)) + ", ";
		
		res.pop_back();
		res.back() = '\n';
	}
	res.pop_back();
	return res;
}


template<typename T>
std::ostream& operator<<(std::ostream& out,const matrix<T>& m) {
	return out << to_string(m);
}
#endif 
#endif