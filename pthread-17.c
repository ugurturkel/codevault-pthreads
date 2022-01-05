/* 
 *producer-consumer problem
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 2

int buffer[10];
int count = 0;

pthread_mutex_t mutex_buffer;

sem_t sem_empty;
sem_t sem_full;

void* producer(void* args){
	while(1){
	
		//Produce
		int x = rand() % 100;
		sleep(1);
		sem_wait(&sem_empty);
		pthread_mutex_lock(&mutex_buffer);
		//add to buffer
		if(count < 10){
			buffer[count]=x;
			count++;
		}
		else{
			printf("skipped %d\n", x);
		}
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&sem_full);
	}
}

void* consumer(void* args){
	while(1){
		int y = -1;
		sem_wait(&sem_full);
		pthread_mutex_lock(&mutex_buffer);
		//remove from the buffer
		if(count > 0){
			 y=buffer[count-1];
			count--;
		}
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&sem_empty);
		printf("got %d\n",y);
	}
}

int main(int argc, char * argv[]){
	pthread_t th[THREAD_NUM];
	int i;
	pthread_mutex_init(&mutex_buffer, NULL);
	sem_init(&sem_empty,0,10);
	sem_init(&sem_full,0,0);
	for(i=0;i<THREAD_NUM;i++){
		if(i%2==0){
			if(pthread_create(&th[i], NULL, &producer, NULL)!=0){
				perror("failed to create thread");
			}
		}
		else{
			if(pthread_create(&th[i], NULL, &consumer, NULL)!=0){
				perror("failed to create thread");
			}
		
		}
	}
	for(i=0;i<THREAD_NUM;i++){
		if(pthread_join(th[i], NULL)!=0){
			perror("failed to join thread");
		}
	}
	sem_destroy(&sem_empty);
	sem_destroy(&sem_full);
	pthread_mutex_destroy(&mutex_buffer);
	return 0;
}

