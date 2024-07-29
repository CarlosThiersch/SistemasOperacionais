/* g++ 2.cpp -pthread*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

int acc = 0;
int iteracoes = 10000;

int main(int argc, char **argv) {
    int n = atoi(argv[1]);
	pid_t pid = 1;
    
    int* acc_global = (int*) mmap(NULL, sizeof (int) , PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *acc_global = 0;
    
    pthread_mutex_t* mutex = (pthread_mutex_t*) mmap(NULL, sizeof (pthread_mutex_t) , PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    pthread_mutex_init(mutex, NULL);
    for(int i = 0; i < n; i++) 
         if (pid != 0) 
             pid = fork();
    if (pid == 0) {  // Child processes
        pthread_mutex_lock(mutex);
        for (int i = 0; i < iteracoes; i++) {
            (*acc_global)++;
        }
        pthread_mutex_unlock(mutex);
        exit(0);
    } else {  // Parent process
        // Wait child processes
        while (wait(NULL) > 0);
        acc = *acc_global;
        /*NAO ALTERE ESSE PRINTF*/
        printf("Acc Esperado [%d] Acc obtido [%d]\n", n * iteracoes, acc);

        
        pthread_mutex_destroy(mutex);
        munmap(acc_global, sizeof(int));
        munmap(mutex, sizeof(pthread_mutex_t));
    }

    return 0;
}
