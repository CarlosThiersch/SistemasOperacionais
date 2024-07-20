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
#include <chrono>

int iteracoes = 1000;

void* worker(void* thread_id){
	auto start = std::chrono::high_resolution_clock::now();
	for (int i=0; i<iteracoes; i++){
		for (int j=0; j<iteracoes; j++){
			for (int k=0; k<iteracoes; k++){
					sqrt(i%100);
			}
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "\tThread " << (long)thread_id << " finalizada.\t" << "(Tempo de execução= " << duration.count() << " segundos)\n";
	pthread_exit(NULL);
}

int main(int argc, char * argv[]){

	int n_threads = atol(argv[1]);
	pthread_t threads[n_threads];
	long thread_params[n_threads] = {0};
	
	printf("\nTeste de threads concorrentes:\n");
	clock_t t1 = clock();
    for (long t = 0; t < n_threads; t++) {
		thread_params[t]=t;
		std::cout << "\tCriando thread " << thread_params[t] << ".\n";
        pthread_create(&threads[t], NULL, worker, (void*)thread_params[t]);
    }
	for (int t = 0; t < n_threads; t++) {
		pthread_join(threads[t], NULL);
	}
	t1 = clock() - t1;
	printf("Tempo total do teste=%.3lf\n",(double)t1/CLOCKS_PER_SEC);

	clock_t t2 = clock();
	printf("\nTeste de threads sequenciais:\n");
	for (long t = 0; t < n_threads; t++) {
		thread_params[t]=t;
		std::cout << "\tCriando thread " << thread_params[t] << ".\n";
        pthread_create(&threads[t], NULL, worker, (void*)thread_params[t]);
		pthread_join(threads[t], NULL);
    }
	t2 = clock() - t2;
	printf("Tempo total do teste=%.3lf.\n",(double)t2/CLOCKS_PER_SEC);
	
	return 0;
}