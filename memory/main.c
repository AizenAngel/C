#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "error_codes.h"
#include "constatnts.h"


void print_memory(const char* memory){
    int num_blocks = strlen(memory) / BLOCK_LEN;

    for(int i = 0; i < num_blocks; i++)
        printf("%.*s\n", BLOCK_LEN, memory + i * BLOCK_LEN);
}

void error(int code){
    switch(code){
        case MEMORY_ERROR: fprintf(stderr, "Memory error!");
                            exit(1);
    }
}

/*
Initialize memory block and set it's inital value to indicate that it's empty.
*/

void initialize_memory_block(char** memory, int num_blocks){
    
    *memory = (char*) malloc(num_blocks * BLOCK_LEN * sizeof(char));

    memset(*memory, '*', num_blocks * BLOCK_LEN);
    
    if(!memory)
        error(MEMORY_ERROR);

}


int main(int argc, char** argv){

    int NUM_BLOCKS;
    int action_code;
    char* memory;

    int free_block[1024];
    int BLOCK_NUM = 0;

    printf("Enter number of blocks: ");
    scanf("%d", &NUM_BLOCKS);
    
    initialize_memory_block(&memory, NUM_BLOCKS);

    while(true){  
        
        printf("Action: ");
        scanf("%d", &action_code);

        switch(action_code){
            case 0: 
                print_memory(memory);
                break;
            
        }        

    }

    return 0;
}