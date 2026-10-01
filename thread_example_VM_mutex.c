#include <pthread.h>
#include <stdio.h>

int iterations = 1000000;
int common = 162;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *threadfun(void *arg) {
    (void)arg;
    for (int i = 0; i < iterations; ++i) {
        pthread_mutex_lock(&mtx);
        ++common;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, threadfun, NULL) != 0) return 1;
    if (pthread_create(&t2, NULL, threadfun, NULL) != 0) return 1;
    if (pthread_join(t1, NULL) != 0) return 1;
    if (pthread_join(t2, NULL) != 0) return 1;

    printf("Expected: %d\n", 162 + 2 * iterations);
    printf("Observed: %d\n", common);
    pthread_mutex_destroy(&mtx);
    return 0;
}
