/* 
 * every thread rolls a dice, saved its value in an arrray
 * the main thread calculates the winner then
 * each thread prints a message whether or not they lost or won
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define THREAD_NUM 8

int dice_values[8];
int status[8]={0};

pthread_barrier_t barrier_roll_dice;
pthread_barrier_t barrier_calculated;

void* roll_dice(void* args){
	while(1){
	
		int index = *(int*)args;
		dice_values[index]=rand()%6+1;
		pthread_barrier_wait(&barrier_roll_dice);
		pthread_barrier_wait(&barrier_calculated);
		if(status[index]==1){
			printf("(%dth rolled %d) I won\n",index,dice_values[index]);
		}
		else{
			printf("(%dth rolled %d) I lost\n",index,dice_values[index]);
		}
	}
	free(args);
}

int main(int argc, char * argv[])
{
	srand(time(NULL));
	pthread_t th[THREAD_NUM];
	pthread_barrier_init(&barrier_roll_dice, NULL, THREAD_NUM+1);
	pthread_barrier_init(&barrier_calculated, NULL, THREAD_NUM+1);
	int i;
	for(i=0;i<THREAD_NUM;i++){
		int* a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i],NULL,&roll_dice,a)!=0){
			perror("failed to create thread");
		}
	}
	while(1){
		pthread_barrier_wait(&barrier_roll_dice);
		//calculation of winner
		int max=0;
		for(i=0;i<THREAD_NUM;i++){
			if(dice_values[i]>max){
				max=dice_values[i];
			}
		}
		for(i=0;i<THREAD_NUM;i++){
			if(dice_values[i]==max){
				status[i]=1;
			}
			else{
				status[i]=0;
			}
		}
		printf("==========NEW ROUND STARTED==========\n");
		sleep(1);
		pthread_barrier_wait(&barrier_calculated);
	}
	for(i=0;i<THREAD_NUM;i++){
		if(pthread_join(th[i],NULL)!=0){
			perror("failed to join thread");
		}
	}
	pthread_barrier_destroy(&barrier_roll_dice);
	pthread_barrier_destroy(&barrier_calculated);
	return 0;

}
