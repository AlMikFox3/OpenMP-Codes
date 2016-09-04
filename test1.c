#include<omp.h>
#include<stdio.h>
int main()
{
	int numthreads;
	//omp_set_num_threads(8);
	#pragma omp parallel
	{
		int id = omp_get_thread_num();
		#pragma omp single nowait
			printf("\n%d\n",omp_get_num_threads());
		
		printf("Thread %d\n",id);
	}
}