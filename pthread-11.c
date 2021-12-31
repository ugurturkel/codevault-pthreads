/* 
 * pthread_barrier usage 
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_barrier_t barrier;

void* routine(void* arg){
	while(1){
		printf("waiting for the barrier\n");
		sleep(1);
		pthread_barrier_wait(&barrier); //7 thread at the same time allowed to pass.
		printf("we passed the barrier!\n");
		sleep(1);
	}
}

int main(int argc, char * argv[]){
	pthread_t th[10];
	int i;
	pthread_barrier_init(&barrier, NULL, 7);
	for(i=0;i<10;i++){
		if(pthread_create(&th[i], NULL, &routine, NULL)!=0){
			perror("failed to create thread");
		}
	}
	for(i=0;i<10;i++){
		if(pthread_join(th[i], NULL)!=0){
			perror("failed to join thread");
		}
	}
	pthread_barrier_destroy(&barrier);
	return 0;
}
