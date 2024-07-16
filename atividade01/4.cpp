/*
gcc -pthread ... 
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include <iostream>
using namespace std;
int number = -1;
int signalA = 0;
int signalB = 0;
std::vector<int> vet;

void* threadA(void *unused){
    cout << "Thread A - Enter vector Size:";
    scanf("%d",&number);
    signalA = 1;
    
    return NULL;
} 

void* threadB(void *unused){
    while(1){
        if (signalA == 1){
	    cout << "Thread B - Initializing Vector \n";
            vet.resize(number);
            for (int i = 0; i < vet.size(); ++i) {
                vet[i] = i;  // Just an example of filling the vector
            }
            signalB = 1;
            break;
        }        
    }
    return NULL;
}

void* threadC(void *unused){
    while(1){
        if (signalB == 1){
	    cout << "Thread C - Printing Vector \n";
            for (int num : vet) {
                std::cout << num << " ";
            }
	    cout << "\n";
        break;
        }
    }
    return NULL;
}
int main(int argc, char * argv[])
{	
	pthread_t threads[3];

    pthread_create(&threads[0], NULL, threadA, NULL);
    pthread_create(&threads[1], NULL, threadB, NULL);
    pthread_create(&threads[2], NULL, threadC, NULL);


    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);

    getchar();
    return 0;
}
