#include<omp.h>
#include<stdio.h>
static long num_steps = 100000000;
double step;
int main()
{
	int i;
	double pi, sum = 0.0;
	double st,et;
	step = 1.0/(double)num_steps;
	omp_set_num_threads(4);
	st = omp_get_wtime();
	#pragma omp parallel
	{
		double x;
		#pragma omp for schedule(auto) reduction(+:sum)
		for(i=1;i<=num_steps;i++){
			x = (i-0.5)*step;
			sum = sum + 4.0/(1 + x*x);
		}
	}
	pi = step * sum;
	double run_time = omp_get_wtime() - st;
	  printf("\n pi with %ld steps is %lf in %lf seconds\n ",num_steps,pi,run_time);
}	  
