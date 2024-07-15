/*
gcc -pthread ... 
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <time.h>

int iteracoes = 1000;

void* worker(void* thread_id){
	printf("\tCriando thread %ld.\n",(long)thread_id);
	clock_t t;
	t = clock();
	// printf("*** teste: endereço de t = %ld\n",(long)&t);
	for (int i=0; i<iteracoes; i++){
		for (int j=0; j<iteracoes; j++){
			for (int k=0; k<iteracoes; k++){
					sqrt(i%100);
			}
		}
	}
	t = clock() - t;
	printf("\tThread %ld finalizada.\t(Tempo de execução=%.3lf)\n", (long)thread_id,(double)t/CLOCKS_PER_SEC);
	pthread_exit(NULL);
}

int main(int argc, char * argv[]){

	int n_threads = atol(argv[1]);
	pthread_t threads[n_threads];
	
	printf("\nTeste de threads concorrentes:\n");
	clock_t t1 = clock();
    for (long t = 0; t < n_threads; t++) {
        pthread_create(&threads[t], NULL, worker, (void*)t);
    }

	for (int t = 0; t < n_threads; t++) {
		pthread_join(threads[t], NULL);
	}
	t1 = clock() - t1;
	printf("Tempo total do teste=%.3lf\n",(double)t1/CLOCKS_PER_SEC);

	clock_t t2 = clock();
	printf("\nTeste de threads sequenciais:\n");
	for (long t = 0; t < n_threads; t++) {
        pthread_create(&threads[t], NULL, worker, (void*)t);
		pthread_join(threads[t], NULL);
    }
	t2 = clock() - t2;
	printf("Tempo total do teste=%.3lf.\n",(double)t2/CLOCKS_PER_SEC);
	
	return 0;
}