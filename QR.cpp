#include "header.h"
int Eigenvalues(double*A,double*lamda,double*rcos,double*rsin,int n, double eps,double my_eps,double Anorm)
{
	double sk;
	int old_n = n;
	int its = 0,max_its = 200*n;
	for(int i = old_n-1;i>1;i--)
	{
		sk = A[(n-1)*old_n + n-1] - 0.5*A[(n-1)*old_n + n-2];
		while(fabs(A[(n-1)*old_n + n-2]) > eps*Anorm && its<max_its)
		{
			for(int j = 0;j<n;j++)
				A[j*old_n+j] -=sk;

			QR(A,rcos,rsin,n,old_n,my_eps,Anorm);
			for(int j = 0;j<n-1;j++)
			{
				for(int q = 0;q<j;q++)
                                {
                                        double a = A[q*old_n + j],b = A[q*old_n + j+1];

                                        A[q*old_n + j] = rcos[j] * a -  b * rsin[j];
                                        A[q*old_n + j + 1] = rsin[j] * a +  b * rcos[j];
                                }
                                double a = A[j*old_n + j],b = A[j*old_n + j+1],d = A[(j+1)*old_n + j+1];
                                A[j*old_n + j] = rcos[j] * a -  b * rsin[j];
                                A[(j + 1)*old_n + j] = -rsin[j] * d;

                                A[j*old_n + j + 1] = rsin[j] * a +  b * rcos[j];
                                A[(j + 1)*old_n + j + 1] = rcos[j]*d;
			}
			for(int j =0;j<n;j++)
				A[j*old_n+j] += sk;
			sk = A[(n-1) * old_n + n-1] - 0.5 * A[(n-1) * old_n + n-2];
			its++;
		}
		lamda[i] = A[(n-1) * old_n + n-1];
		n--;
	}
	if(n==1)
	{
		lamda[0] = A[0];
		return 0;
	}
	else
	{
		double trA = A[0] + A[1*old_n +1];
		double detA = A[0] *A[1*old_n +1] - A[1]*A[1*old_n + 0];
		if(trA * trA - 4 * detA < 0)
		{
			lamda[0] = 0;
			lamda[1] = 1;
			printf("Determinant A < 0\n");
			return its;
		}
		lamda[0] = ( trA + sqrt( trA * trA - 4 * detA) )/2;
		lamda[1] = ( trA - sqrt( trA * trA - 4 * detA) )/2;
	}
	return its;


}
void QR(double*A,double*rcos,double*rsin,int n,int nn,double my_eps,double Anorm)
{
	double cosk,sink,x,y,sq;
	double small_eps = 1.e-50; 
	for(int i=0;i<n - 1;i++)
	{
		x = A[i * nn + i];
		y = A[(i + 1) * nn + i];
		if(fabs(x)<small_eps)
			x = 0.0;
		if(fabs(y)<=small_eps)
			y = 0.0;
		sq = sqrt(x * x + y * y);
		if(sq<my_eps*Anorm)
		{
			rcos[i] = 1;
			rsin[i] = 0;
			if(fabs(x)<=small_eps)
				A[i * nn + i] = 0.0;
			if(fabs(y)<=small_eps)
				A[(i+1) * nn + i] = 0.0;
			continue;
		}
		cosk = x / sq;
		sink = -y / sq;
		if(fabs(cosk)<=small_eps)
			cosk = 0.0;
		if(fabs(sink)<=small_eps)
			sink = 0.0; 
		rcos[i] = cosk;
		rsin[i] = sink;
		for(int c = i;c < n;c++)
		{
			x = cosk * A[i * nn + c] - sink * A[(i+1) * nn + c];
			y = sink * A[i * nn + c] + cosk * A[(i+1) * nn + c];
			A[i * nn + c] = x;
			A[(i+1) * nn + c] = y; 
		}
		A[(i + 1) * nn + i] = 0.0;
	}
}
