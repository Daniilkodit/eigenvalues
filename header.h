#ifndef HEADER
#define HEADER
#include<cstdio>
#include<fstream>
#include<string>
#include<chrono>
#include<cmath>
#include <fenv.h>
int feenableexcept(int excepts);
int fedisableexcept(int excepts);
int fegetexcept(void);

int Ainit(double*, int, int, const std::string&);
void Print_matrix(int, int, int, double*);
double Norm_matrix(double*,int);

int transformation_matrix(double*A,double my_eps,int n,double Anorm);
int Eigenvalues(double*A,double*lamda,double*rcos,double*rsin,int n, double eps,double my_eps,double Anorm);
void QR(double*A,double*rcos,double*rsin,int n,int nn,double my_eps,double Anorm);

double R1(double*A,double *lamda,int n);
double R2(double*A,double *lamda,int n);
#endif
