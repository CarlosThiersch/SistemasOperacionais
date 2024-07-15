/*
gcc -pthread ... 
*/

/*
Construa um programa que execute 𝑛 threads. Cada thread deve realizar a tarefa definida 
pela função worker. Todas as threads devem ser exclusivamente orientadas à CPU.

(Opcional para análise) Crie a versão sequencial desse mesmo programa, isto é, a função
worker é executada 𝑛 vezes sequencialmente. Compare os tempos de execução do
programa usando threads e a versão sequencial.

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
	clock_t t;
	t = clock();
	printf("\tCriando thread %ld\t(clock=%.3lf)\n",(long)thread_id,(double)t);
	for (int i=0; i<iteracoes; i++){
		for (int j=0; j<iteracoes; j++){
			for (int k=0; k<iteracoes; k++){
					sqrt(i%100);
			}
		}
	}
	t = clock() - t;
	printf("\tFinalizando thread %ld\t(delta clock=%.3lf)\n", (long)thread_id,(double)t);
	pthread_exit(NULL);
}

int main(int argc, char * argv[]){

	int n_threads = atol(argv[1]);
	pthread_t threads[n_threads];
	
    for (long t = 0; t < n_threads; t++) {
        pthread_create(&threads[t], NULL, worker, (void*)t);
    }
	for (int t = 0; t < n_threads; t++) {
		pthread_join(threads[t], NULL);
	}
	
	return 0;
}