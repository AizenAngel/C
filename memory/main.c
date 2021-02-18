#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "error_codes.h"
#include "constatnts.h"


void print_memory(char** memory, int num_blocks){
    for(int i = 0; i < num_blocks; i++)
        printf("%s\n", memory[i]);
}

void error(int code){
    switch(code){
        case MEMORY_ERROR: fprintf(stderr, "Memory error!");
                            exit(1);
    }
}

/*
@ Initialize memory block and set it's inital value to indicate that it's empty.
*/

void initialize_memory_block(char*** memory, int num_blocks){
    
    *memory = (char**) malloc(num_blocks * sizeof(char*));

    for(int i = 0; i < num_blocks; i++){
        *(*memory + i) = malloc(BLOCK_LEN * sizeof(char));
        memset( *(*memory + i), '*', BLOCK_LEN);
    }

    if(!memory)
        error(MEMORY_ERROR);

}

int main(int argc, char** argv){

    int NUM_BLOCKS;
    int action_code;
    char** memory;

    printf("Enter number of blocks: ");
    scanf("%d", &NUM_BLOCKS);
    
    initialize_memory_block(&memory, NUM_BLOCKS);

    while(true){  
        
        printf("Action: ");
        scanf("%d", &action_code);

        switch(action_code){
            case 0: 
                print_memory(memory, NUM_BLOCKS);
                break;
        }        

    }

    return 0;
}