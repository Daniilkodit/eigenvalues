#include "header.h"
double R1(double*A,double*lamda,int n)
{
	double sum = 0;
	for(int i=0;i<n;i++)
		sum += A[i*n+i]-lamda[i];
	return fabs(sum);
}
double R2(double*A,double *lamda,int n)
{
	double sum1=0,sum2 = 0;
	for(int i =0 ;i<n;i++)
	{
		for(int j = 0; j<n;j++)
			sum1 += A[i*n+j]*A[j*n+i];
		sum2 += lamda[i]*lamda[i];
	}
	return fabs(sqrt(fabs(sum1)) - sqrt(sum2));
}
