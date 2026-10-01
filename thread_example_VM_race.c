#include <pthread.h>
#include <stdio.h>

int iterations = 1000000;
int common = 162;

void *threadfun(void *arg) {
    (void)arg;
    for (int i = 0; i < iterations; ++i) {
        ++common;  /* Intentionally unsynchronized. */
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
    return 0;
}
