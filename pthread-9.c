/*
 *trylock example with multiple mutex
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

pthread_mutex_t mutexes_stove[4];
int fuel_stove[4]={100,100,100,100};

void* routine(void* args){
	for(int i=0;i<4;i++){
		if(pthread_mutex_trylock(&mutexes_stove[i])==0){
		
			int fuel_needed=(rand()%30);
			if(fuel_stove[i] - fuel_needed < 0){
				printf("no more fuel left\n");
			}
			else{
				fuel_stove[i]-=fuel_needed;
				usleep(500000);
				printf("fuel left %d\n", fuel_stove[i]);
			}
			pthread_mutex_unlock(&mutexes_stove[i]);
			break;
		}
		else {
			if(i==3){
				printf("no stove available yet\n");
				usleep(300000);
				i=0;
			}
		}
	}
}

int main(int argc, char* argv[]){
	pthread_t th[10];
	srand(time(NULL));
	for(int i=0;i<4;i++){
		pthread_mutex_init(&mutexes_stove[i],NULL);
	}
	for(int i=0;i<10;i++){
		if(pthread_create(&th[i],NULL,&routine,NULL)!=0){
			perror("failed to create thread");
		}
	}
	for(int i=0;i<10;i++){
		if(pthread_join(th[i],NULL)!=0){
			perror("failed to join thread");
		}
	}
	for(int i=0;i<4;i++){
		pthread_mutex_destroy(&mutexes_stove[i]);
	}
	return 0;

}
