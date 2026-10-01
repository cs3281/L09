#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

void print_list(node_t *head) {
    for (node_t *node = head; node != NULL; node = node->next) {
        printf("%d -> ", node->value);
    }
    puts("NULL");
}

int main(void) {
    node_t first = {10, NULL};
    node_t node_A = {20, NULL};
    node_t node_B = {30, NULL};
    node_t *A = &node_A;
    node_t *B = &node_B;
    node_t *head = &first;

    puts("Manual interleaving, not two running threads:");
    A->next = head;
    B->next = head;

    head = A;
    printf("After A publishes: ");
    print_list(head);

    head = B;
    printf("After B publishes: ");
    print_list(head);
    return 0;
}
