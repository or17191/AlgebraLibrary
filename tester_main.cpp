#include "matrix.h"
#include "vector.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	/* code */
 	AlgebraTAU::matrix<double> M({
		{0,2},
	    {4,5}
	});

 	AlgebraTAU::vector<double> v({1,2},false);
 	v = -v;
 	v.map([](const double& x){return x*x;});
	std::cout << v << std::endl;
	return 0;
}
