#include <stdio.h>
#include <stdlib.h>
#include "memory_blocks.h"

int main(){
    block* head = NULL;
    add_new_block(&head, 3, 40, true);
    add_new_block(&head, 43, 20, false);
    add_new_block(&head, 63, 20, true);
    add_new_block(&head, 83, 20, false);
    add_new_block(&head, 103, 20, true);
    add_new_block(&head, 123, 20, false);
    add_new_block(&head, 143, 20, true);
    add_new_block(&head, 163, 20, false);
    

    print_memory_blocks(head);

    sort_memory_blocks(&head);
    printf("\n");

    print_memory_blocks(head);

    // print_memory_blocks(head);
    // int size = get_free_memory_blocks_size_and_release_them(&(head->next));
    // head->next = NULL;
    // printf("%d\n", size);
    // print_memory_blocks(head);

    return 0;
}