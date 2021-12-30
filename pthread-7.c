/* 
 * difference between lock and trylock
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h> //if trylock couldnt lock, then the return value is constant EBUSY

pthread_mutex_t mutex;

void * routine(void *arg) {
	if(pthread_mutex_trylock(&mutex)==0){  //if it gets the lock returns 0
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	else{
		printf("didnt get the lock\n");
	}
}

int main(int argc, char * argv[]){
	pthread_t th[4];
	pthread_mutex_init(&mutex, NULL);

	for(int i=0;i<4;i++){
		if(pthread_create(th+i, NULL, &routine, NULL)!=0){
			perror("failed to create thread\n");
			return 1;
		}
	}
	for(int i=0;i<4;i++){
		if(pthread_join(th[i], NULL)!=0){
			return 2;
		}
	}
	pthread_mutex_destroy(&mutex);
	return 0;

}
