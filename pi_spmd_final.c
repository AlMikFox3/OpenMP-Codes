#include<omp.h>
#include<stdio.h>
#define MAX_THREADS 8
static long no_steps = 100000000;
double step;
int main()
{
	double pi = 0.0,st,rt; 
	step = 1.0/(double)no_steps;
	int i =1;
	
 	for(i = 1; i<MAX_THREADS;i++)
 	{
		omp_set_num_threads(4);
		st = omp_get_wtime();
		pi = 0.0;

		#pragma omp parallel
		{
			int id = omp_get_thread_num();
			int nthrds = omp_get_num_threads();
			double sum = 0.0;
			int j=1; 
			double x;
			//#pragma omp for 
			/*for(j=id;j<=no_steps;j= j+1)*/  for(j=id;j<=no_steps;j= j + nthrds)
			{
				x=(j+0.5)*step;
				sum = sum + (4.0 / (1.0 + x*x));
				//printf("%d  %lf\n",id,sum);
			}
			#pragma critical
			{
				pi += sum * step;
				//printf("%d  %lf\n",id,sum);
			}
			
		}
		rt = omp_get_wtime() - st;
		printf("pi for %d threads is %lf at time %lf\n",i,pi,rt);

	}
}