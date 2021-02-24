#ifndef _MEM_BLOCKS_
#define _MEM_BLOCKS_

#include <stdbool.h>

typedef struct{
    int start_index;
    int block_size;
    bool used;
    struct block* next;
}block;

#define swap_values(x, y, T) do { T tmp = x; x = y; y = tmp; } while (0)

void swap_blocks(block* block1, block* block2){
    swap_values(block1->start_index, block2->start_index, int);
    swap_values(block1->block_size, block2->block_size, int);
    swap_values(block1->used, block2->used, bool);
}

void add_new_block(block** head, int start_index, int block_size, bool used){
    if(*head == NULL){
        *head = (block*) malloc(sizeof(block*));
        (*head)->start_index = start_index;
        (*head)->block_size = block_size;
        (*head)->used = used;
        (*head)->next = NULL;

        return;
    }

    add_new_block(&((*head)->next), start_index, block_size, used);
}

void print_memory_blocks(block* head){
    if(head == NULL){
        return;
    }

    printf("%d %d %s\n", head->start_index, head->block_size, head->used?"used":"unused");
    print_memory_blocks(head->next);
}

void sort_memory_blocks(block** head){

    for(block* temp1 = *head; temp1 != NULL; temp1 = temp1->next){
        for(block* temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next){
            if(!temp1->used && temp2->used){
                swap_blocks(temp1, temp2);
            }
        }
    }    

    block* temp1 = *head;
    int first_free_block_index = temp1->start_index;
    temp1->start_index = 0;
    int new_start_index = temp1->block_size;

    temp1 = temp1->next;

    while(temp1->next != NULL){
        printf("Novi start index: %d\n", new_start_index);
        temp1->start_index = new_start_index;
        new_start_index += temp1->block_size;
        temp1 = temp1->next;
    }

    temp1->start_index -= first_free_block_index;
    temp1->block_size += first_free_block_index;
}

#endif