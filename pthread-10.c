/*
 * pthread_exit instead returning a value from a thread
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

void* roll_dice() {
	int val = (rand()%6)+1;
	int* res = malloc(sizeof(int));
	*res = val;
	//printf("%d\n", val);
	printf("thread result: %d\n", val);
	pthread_exit((void*) res);
}

int main(int argc, char * argv[]){
	int* res;
	srand(time(NULL));
	pthread_t th;
	if(pthread_create(&th, NULL, &roll_dice, NULL)!=0){
		return 1;
	}
	if(pthread_join(th, (void**) &res)!=0){
		return 2;
	}
	
	printf("main result: %d\n" ,*res);
	free(res);
	return 0;

}
