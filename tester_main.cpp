#define WITH_ACCESSES
#include "matrix.h"
#include <iostream>

#ifdef WITH_ACCESSES
int main(int argc, char const *argv[])
{
	/* code */
	using namespace std;

 	matrix<double> M({
		{0,2},
		{4,5}
	});

 	M.map([](const double& x){ return x - 1; });
	cout << M << endl;
	return 0;
}

#else 
int main(int argc, char const *argv[]){

	const matrix<double> M({
		{1,2,3},
		{4,5,6}
	});

	return 0;
}
#endif