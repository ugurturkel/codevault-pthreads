/* 
 *semaphores
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semaphore;

void* routine(void* args){
	sem_wait(&semaphore); //if semaphore value is 0 then wait, if not decrement it and execute
	sleep(1);
	printf("Hello from thread %d\n",*(int*)args);
	sem_post(&semaphore); //increment the semaphore
	free(args);
}

int main(int argc, char * argv[]){
	pthread_t th[THREAD_NUM];
	sem_init(&semaphore,0,2); //if you have only multiple threads pass 0, if you have multiple process pass 1, third parameter is the value of semaphore
	int i;
	for(i=0;i<THREAD_NUM;i++){
		int* a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a)!=0){
			perror("failed to create thread");
		}
	}
	for(i=0;i<THREAD_NUM;i++){
		if(pthread_join(th[i], NULL)!=0){
			perror("failed to join thread");
		}
	}
	sem_destroy(&semaphore);
	return 0;
}

