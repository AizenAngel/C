#include <stdio.h>
#include <stdlib.h>
#include "memory_blocks.h"

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

    printf("\t%d %d %s\n", head->start_index, head->block_size, head->used?"used":"unused");
    print_memory_blocks(head->next);
}

int __combine_free_memory_blocks_size_and_release_them(block** head){
    if(*head == NULL){
        return 0;
    }

    int res = __combine_free_memory_blocks_size_and_release_them(&((*head)->next));

    res += (*head)->block_size;
    (*head)->next = NULL;
    free(*head);
    return res;
}

void combine_free_memory_blocks_size_and_release_them(block** head){
    int combined_size = __combine_free_memory_blocks_size_and_release_them(&((*head)->next));
    (*head)->next = NULL;
    (*head)->block_size+= combined_size;
}

void arrange_memory_blocks(block** head){
    block* temp1 = *head;
    int first_free_block_index = temp1->start_index;
    temp1->start_index = 0;
    int new_start_index = temp1->block_size;

    temp1 = temp1->next;

    block* first_unused_memory_block = NULL;
    bool block_found = false;


    while(temp1->next != NULL){
        
        if(!block_found && !temp1->used){
            first_unused_memory_block = temp1;
            block_found = true;
        }
        
        temp1->start_index = new_start_index;
        new_start_index += temp1->block_size;
        temp1 = temp1->next;
    }

    temp1->start_index -= first_free_block_index;
    temp1->block_size += first_free_block_index;

    combine_free_memory_blocks_size_and_release_them(&first_unused_memory_block);
}

void sort_memory_blocks(block** head){

    for(block* temp1 = *head; temp1 != NULL; temp1 = temp1->next){
        for(block* temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next){
            if(!temp1->used && temp2->used){
                swap_blocks(temp1, temp2);
            }
        }
    }    

    arrange_memory_blocks(head);
}

block* create_new_memory_block(int start_index, int block_size){
    block* new_block = malloc(sizeof(block*));
    new_block->block_size = block_size;
    new_block->next = NULL;
    new_block->start_index = start_index;
    new_block->used = false;

    return new_block;
}
