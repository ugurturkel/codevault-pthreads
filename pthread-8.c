/* 
 * mutex and condition example, signaling for condition variables
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h> 

int fuel=0;
pthread_mutex_t mutex_fuel;
pthread_cond_t cond_fuel;

void* fuel_filling(void* arg){
	for(int i=0;i<5;i++){
		pthread_mutex_lock(&mutex_fuel);
		fuel+=30;
		printf("filling fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		//pthread_cond_signal(&cond_fuel); //send signal for one car
		pthread_cond_broadcast(&cond_fuel); //broadcast the cond signal for all the cars
		sleep(1);
	}
}

void* car(void* arg){
	pthread_mutex_lock(&mutex_fuel);
	while(fuel<40){
		printf("no fuel, waiting...\n");
		pthread_cond_wait(&cond_fuel, &mutex_fuel);
		//equivalent to:
		//pthread_mutex_unlock(mutex_fuel);
		//wait for signal on cond_fuel
		//pthread_mutex_lock(&mutex_fuel);
	}
	fuel-=40;
	printf("got fuel, now left: %d\n", fuel);
	pthread_mutex_unlock(&mutex_fuel);
}

int main(int argc, char * argv[]){
	pthread_t th[6];
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&cond_fuel, NULL);
	for(int i=0;i<6;i++){
		if(i == 4 || i == 5){
			if(pthread_create(&th[i], NULL, &fuel_filling, NULL)!=0){
				perror("failed to create thread");
			}
		}
		else{
			if(pthread_create(&th[i],NULL,&car,NULL)!=0){
				perror("failed to create thread");
			}
		}
	}
	for(int i=0;i<6;i++){
		if(pthread_join(th[i],NULL)!=0){
			perror("failed to join thread");
		}
	}
	pthread_mutex_destroy(&mutex_fuel);
	pthread_cond_destroy(&cond_fuel);
	return 0;
}
