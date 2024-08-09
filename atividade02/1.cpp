/*g++ 1.cpp*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <chrono>
//#include <sched.h>

/*
Apresente uma alternativa para melhorar o desempenho computacional desse programa. 

OPCIONAL: compare a performance do programa antes e sem sua alternativa e pense: 
	(i) por que o Acumulador visto em sala é ineficiente? 
	(ii) sua solução introduz algum tipo de sobrecarga no programa original. 
(Dica: lembre-se da estrutura stack que as threads possuem).
*/

int acc = 0;
int iteracoes = 10000;/*NÃO ALTERE ESSE VALOR*/
pthread_mutex_t mutex;

void* worker(void *thread_id){
	//auto start = std::chrono::high_resolution_clock::now();
	//int cpu = sched_getcpu();
    //printf("Thread %ld está sendo executada no núcleo %d\n", (long)thread_id, cpu);
	int acc_thread = 0;
	
	for (int i=0; i<iteracoes; i++){
		acc_thread += 1;
	}
	//usleep(500000);

	pthread_mutex_lock(&mutex);
	acc += acc_thread;
	pthread_mutex_unlock(&mutex);
	
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double> duration = end - start;
	//std::cout << "\tThread " << (long)thread_id << " finalizada.\t" << "(Tempo de execução= " << duration.count()*1000 << " ms)\n";
	pthread_exit(NULL);
}

int main(int argc, char * argv[]){
	int n_threads = atol(argv[1]);
	pthread_t threads[n_threads];
	pthread_mutex_init(&mutex, NULL);

	for(long t = 0; t < n_threads; t++ )
	      pthread_create(&threads[t], NULL, worker, (void *)t);

	for (int t = 0; t < n_threads; t++)
		pthread_join(threads[t], NULL);
    
	/*NAO ALTERE ESSE PRINTF*/
    printf("Acc Esperado [%d] Acc obtido [%d]\n", n_threads*iteracoes, acc);
	
	return 0;
}