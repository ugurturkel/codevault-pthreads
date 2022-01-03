/* 
 * detach threads from main thread, initialize them in detached state
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


void* routine(void* arg){
	sleep(1);
	printf("Finished execution\n");
}

int main(int argc, char * argv[]){
	pthread_t th[2];
	pthread_attr_t detached_thread;
	pthread_attr_init(&detached_thread);
	pthread_attr_setdetachstate(&detached_thread, PTHREAD_CREATE_DETACHED);
	int i;
	for(i=0;i<2;i++){
		if(pthread_create(&th[i], &detached_thread, &routine, NULL)!=0){
			perror("failed to create thread");
		}
		//pthread_detach(th[i]);
	}
	//for(i=0;i<2;i++){
	//	if(pthread_join(th[i], NULL)!=0){
	//		perror("failed to join thread");
	//	}
	//}
	pthread_attr_destroy(&detached_thread);
//	return 0;
	pthread_exit(0); //wait for threads to execute after detach
}

