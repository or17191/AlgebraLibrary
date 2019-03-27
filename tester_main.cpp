#include "matrix.h"
#include "vector.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	/* code */

 	matrix<double> M({
		{0,2},
	    {4,5}
	});

 	vector<double> v({1,2},false);
	std::cout << (v*M) << std::endl;
	return 0;
}
