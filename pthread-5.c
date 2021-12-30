/* 
 * create 10 threads, each taking a unique prime from the primes array
 * and print it on the screen
 *
 * basically pass an arguement to a thread
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int primes[10] = {2,3,5,7,11,13,17,19,23,29};

void* routine(void* arg){
	sleep(1);
	int index=*(int*)arg;
	printf("%d ",primes[index]);
	free(arg);
}

int main(int argc, char * argv[]){
	pthread_t th[10];
	int i;
	for(i=0;i<10;i++){
		int* a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a)!=0){
			perror("failed to create thread");
		}
	}
	for(i=0;i<10;i++){
		if(pthread_join(th[i], NULL)!=0){
			perror("failed to join thread");
		}
	}
	return 0;
}
