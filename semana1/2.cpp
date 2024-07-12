/*
gcc -pthread ... 
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>

int number = -1;
int message = 0;
const char* filename;

void* worker(void *thread_id){

    if ((intptr_t)thread_id == 0){
        while(1){
            if(message == 1){
                printf("Thread A : %d \n",number);
                break;
            }
        }
    }

    if ((intptr_t)thread_id == 1){
        FILE* file = fopen ("./programFile.txt", "r");
        fscanf (file, "%d", &number); 
        message = 1;  
        printf("Thread B : %d \n",number);
	exit(0);
    }

    return NULL;
}


int main(int argc, char * argv[])
{
	filename = argv[1];

    pthread_t threads[2];

    for(int t = 0; t < 2; t++ )
        pthread_create(&threads[t], NULL, worker,  (void *)(intptr_t)t);

    for( int i = 0; i < 2; i++ )
        pthread_join(threads[i], NULL);

    getchar();
    return 0;

}

