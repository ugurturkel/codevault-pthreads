/* 
 * what is pthread_t? 
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>


void* routine(void* arg){
	pthread_t th = pthread_self();
	printf("%lu\n",th);
	printf("%d\n",(pid_t) syscall(SYS_gettid)); //get thread id
}

int main(int argc, char * argv[]){
	pthread_t th[2];
	int i;
	for(i=0;i<2;i++){
		if(pthread_create(&th[i], NULL, &routine, NULL)!=0){
			perror("failed to create thread");
		}
		printf("%lu\n",th[i]);
	}
	for(i=0;i<2;i++){
		if(pthread_join(th[i], NULL)!=0){
			perror("failed to join thread");
		}
	}
	return 0;
}
