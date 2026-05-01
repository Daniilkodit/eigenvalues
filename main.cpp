#include "header.h"
int main(int argc, char*argv[])
{
        int n, m,  s, out = 0,its = 0;
        std::string name;
	double Anorm = 1;
	double my_eps = 1.e-15,eps = 0;
        double*A = nullptr;
	double*lamda = nullptr;
	double*rcos  = nullptr;
	double*rsin = nullptr;
        double t1 = 0, t2=0, r1 = -1, r2 =-1;
	feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW);
        if(!((argc == 5 || argc == 6) &&
                        sscanf(argv[1], "%d", &n) == 1 &&
                        sscanf(argv[2], "%d", &m) == 1 &&
                        sscanf(argv[3], "%lf", &eps) == 1 &&
                        sscanf(argv[4], "%d", &s) == 1))
        {
                printf("Usage: %s n m eps s\n", argv[0]);
                return 0;
        }
        if(n <= 0 || m <= 0 || eps < 1.e-16)
        {
                printf("Usage: n>0 m>0 eps>=1.e-16 s\n");
                return 0;
        }

	if(m>n)
		m = n;

        if(s == 0)
        {
                if(argc != 6)
                {
                        printf("Usage: %s n m r 0 namefile.txt\n", argv[0]);
                        return 0;
                }
                else name = argv[5];
        }
        A = new double[n * n];
	if(Ainit(A, n, s, name) < 0)
	{
		delete[] A;
                return -1;
	}
	lamda = new double[n];
	rcos = new double[n-1];
	rsin = new double[n-1];

        Print_matrix(n, n, m, A);
	Anorm = Norm_matrix(A,n);
#if 1
	// тут буду приводить к почти треугольному
        auto start1 = std::chrono::high_resolution_clock::now();
	out = transformation_matrix(A, my_eps, n, Anorm);
        auto end1 = std::chrono::high_resolution_clock::now();
        t1 = std::chrono::duration<double>(end1 - start1).count();
#endif
	// тут буду вычислять lamda
	start1 = std::chrono::high_resolution_clock::now();
        its = Eigenvalues(A, lamda,rcos,rsin, n,eps,my_eps, Anorm);
        end1 = std::chrono::high_resolution_clock::now();
        t2 = std::chrono::duration<double>(end1 - start1).count();
        if(out == 0 && its >= 0)
        {
                Ainit(A, n, s, name);
		if(Anorm>1.e-64)
		{
			r1 = R1(A,lamda,n)/Anorm;
			r2 = R2(A,lamda,n)/Anorm;
		}
		else
		{
			r1 = 0;
			r2 = 0;
		}

        }
        else
        {
                r1 = -1;
                r2 = -1;
        }
	Print_matrix(1,n,m,lamda);
	printf ("%s : Residual1 = %e Residual2 = %e Iterations = %d Iterations1 = %d Elapsed1 = %.2f Elapsed2 = %.2f\n",
			argv[0], r1, r2, its, its / n, t1, t2);
        delete[] A;
	delete[] lamda;
	delete[] rcos;
	delete[] rsin;
        return 0;

}
