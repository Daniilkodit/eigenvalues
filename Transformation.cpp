#include "header.h"
int transformation_matrix(double*A,double eps,int n,double Anorm)
{
	int q, p, c;
	double cosk, sink, x, y, sq;
	for (q = 0; q < n - 2; q++)
	{
		for (p = q + 2; p < n; p++)
		{
			x = A[(q+1) * n + q];	//насчитываем cos и sin в матрицах поворота
			y = A[p * n + q];
			sq = (sqrt (x * x + y * y));
			if (sq < eps * Anorm)
				continue;		// x=0 и y=0
			cosk = x / sq;
			sink = -y / sq;
			for (c = q; c < n; c++)	
			{
				x = cosk * A[(q+1) * n + c] - sink * A[p * n + c];
				y = sink * A[(q+1) * n + c] + cosk * A[p * n + c];
				A[(q+1) * n + c] = x;
				A[p * n + c] = y;
			}
			for (c = 0; c < n; c++)
			{
				x = cosk * A[c * n + (q+1)] - sink * A[c * n + p];
				y = sink * A[c * n + (q+1)] + cosk * A[c * n + p];
				A[c * n + (q+1)] = x;
				A[c * n + p] = y;
			}
			A[p * n + q] = 0;

		}
	}
	return 0;
}
