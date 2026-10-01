#include <pthread.h>
#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

node_t first = {10, NULL};
node_t *head = &first;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

/* Each worker receives a node that is already prepared. */
void *List_Insert_Narrow(void *arg) {
    node_t *node = arg;

    pthread_mutex_lock(&lock);
    node->next = head;
    head = node;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    node_t a = {20, NULL};
    node_t b = {30, NULL};
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, List_Insert_Narrow, &a) != 0) return 1;
    if (pthread_create(&t2, NULL, List_Insert_Narrow, &b) != 0) return 1;
    if (pthread_join(t1, NULL) != 0) return 1;
    if (pthread_join(t2, NULL) != 0) return 1;

    for (node_t *node = head; node != NULL; node = node->next) {
        printf("%d -> ", node->value);
    }
    puts("NULL");
    pthread_mutex_destroy(&lock);
    return 0;
}
