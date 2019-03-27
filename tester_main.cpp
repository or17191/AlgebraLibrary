#include "matrix.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	/* code */
	using namespace std;

 	matrix<double> M({
		{0,2},
		{4,5}
	});

	M *= -2;
	cout << M << endl;
	return 0;
}
