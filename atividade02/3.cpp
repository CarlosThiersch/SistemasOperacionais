/*gcc -pthread 3.cpp*/

/*
3. (Programação concorrente e sincronização) Implemente uma solução para o problema 
produtor-consumidor. A solução deve evitar deadlock; portanto, você deve utilizar algum 
recurso de exclusão mútua (ex.: mutex, semáforo ou ambos).
Chamada da função: ./programa <consumidores> <produtores>
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <limits>


sem_t sem_preenchidos;
sem_t sem_vazios;
pthread_mutex_t mutex_buffer;

int N = 0; /*NÃO ALTERE ESSA VARIAVEL*/
int buffer_size = 8;

/*NAO ALTERE ESSE FUNCAO*/
void print_buffer(int i) {
	for (int j = 0; j<i;j++) printf("#");
}

void* produtor(void *thread_id) {
	while(1) {
		sem_wait(&sem_vazios);
		pthread_mutex_lock(&mutex_buffer);
		printf("Produtor %ld:\t",(long)thread_id);
		print_buffer(++N);//Funciona se trocarmos por N++?
		printf("\n");
		sem_post(&sem_preenchidos);
		pthread_mutex_unlock(&mutex_buffer);
		
	}
}

void* consumidor(void *thread_id) {
	while(1) {
		sem_wait(&sem_preenchidos);
		pthread_mutex_lock(&mutex_buffer);
		printf("Consumidor %ld:\t",(long)thread_id);
		print_buffer(--N);//Funciona se trocarmos por N--?
		printf("\n");
		pthread_mutex_unlock(&mutex_buffer);
		sem_post(&sem_vazios);
	}
}

int main(int argc, char * argv[]) {
	int consumidores = atol(argv[1]);
	int produtores = atol(argv[2]);
	sem_init(&sem_vazios,0,buffer_size);
	sem_init(&sem_preenchidos,0,0);
	pthread_t threads_consumidores[consumidores];
	pthread_t threads_produtores[produtores];
	for(long t = 0; t < produtores; t++)
		pthread_create(&threads_produtores[t], NULL, produtor, (void *)t);
	for (long t = 0; t < consumidores; t++)
		pthread_create(&threads_consumidores[t], NULL, consumidor, (void *)t);
	
	while(1);
	return 0;
}
