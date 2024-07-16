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

int main(int argc, char * argv[])
{
    int id;
    int var;
    int* p_read = (int*) mmap(NULL, sizeof (int) , PROT_READ | PROT_WRITE,
                MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    *p_read = -1;
    int* message = (int*) mmap(NULL, sizeof (int) , PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *message = 0;
    const char* filename = argv[1];

    id = fork();
    if (id == 0) {
        FILE* file = fopen (filename, "r");
        fscanf (file, "%d", p_read); 
        *message = 1;  
        printf("Fork Filho : %d \n", *p_read);
	exit(0);
    }
    else
    if (id>0) {
    while(1) {
        if(*message == 1){
            printf("Fork Pai : %d \n", *p_read);
            break;
        }
        }
    }
    
    return 0;
}
