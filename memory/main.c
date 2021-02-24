#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "error_codes.h"
#include "constatnts.h"
#include "memory_blocks.h"


void print_memory(const char* memory){
    int num_blocks = strlen(memory) / BLOCK_LEN;

    for(int i = 0; i < num_blocks; i++)
        printf("%.*s\n", BLOCK_LEN, memory + i * BLOCK_LEN);
}

void print_memory_blocks(block* blocks, int NUM_MEM_BLOCKS){
    for(int i = 0; i < NUM_MEM_BLOCKS; i++){
        printf("(start index: %d, size: %d, active: %s)\n", blocks[i].start_index, blocks[i].block_size, blocks[i].active?"active":"inactive");
    }
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

void initialize_memory_block(char** memory, block** mem_blocks, int* NUM_MEM_BLOCKS, int num_blocks){
    
    *memory = (char*) malloc(num_blocks * BLOCK_LEN * sizeof(char));
    *mem_blocks = (block*) malloc(BLOCK_LEN * sizeof(block));

    memset(*memory, '*', num_blocks * BLOCK_LEN);

    mem_blocks[0]->start_index = 0;
    mem_blocks[0]->block_size = num_blocks * BLOCK_LEN;
    mem_blocks[0]->active = false;

    *NUM_MEM_BLOCKS = 1;

    if(!memory)
        error(MEMORY_ERROR);
}

bool allocate_memory_block(char* memory, int block_size){

}

int main(int argc, char** argv){

    int NUM_BLOCKS;
    int action_code;
    char* memory;

    block* mem_blocks;
    int NUM_MEM_BLOCKS;

    printf("Enter number of blocks: ");
    scanf("%d", &NUM_BLOCKS);
    
    initialize_memory_block(&memory, &mem_blocks, &NUM_MEM_BLOCKS, NUM_BLOCKS);

    while(true){  
        
        printf("Action: ");
        scanf("%d", &action_code);

        switch(action_code){
            case 0: 
                print_memory(memory);
                break;
            case 1:
                print_memory_blocks(mem_blocks, NUM_MEM_BLOCKS);
                break;
        }        

    }

    return 0;
}