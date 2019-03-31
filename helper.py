import numpy as np
import sys



def matrix_to_str(M):
	res = "({\n"
	for r in M:
		res += "{"
		for x in r: res += str(x) + ", "
		res = res[:-2] + "},\n"
	return res[:-2] + "\n});"


M = np.random.randint(low=0,high=10,size=(4,5))


print(matrix_to_str(M))