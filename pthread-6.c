/* 
 * get sum of the primes array bu summing first and second half of it respectively 
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void* routine(void* arg){
	int index=*(int*)arg;
	int sum = 0;
	for(int j=0;j<5;j++){
		sum+=primes[index+j];
	}
	printf("local sum: %d\n", sum);
	*(int*)arg = sum;
	return arg;
}

int main(int argc, char * argv[]){
	pthread_t th[2];
	int i;
	for(i=0;i<2;i++){
		int* a = malloc(sizeof(int));
		*a = i*5;
		if(pthread_create(&th[i], NULL, &routine, a)!=0){
			perror("failed to create thread");
		}
	}
	int global_sum=0;
	for(i=0;i<2;i++){
		int* res;
		if(pthread_join(th[i], &res)!=0){
			perror("failed to join thread");
		}
		global_sum+=*res;
		free(res);
	}
	printf("Global Sum: %d\n", global_sum);
	return 0;
}
