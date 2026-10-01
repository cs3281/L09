#include <errno.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *try_once(void *arg) {
    (void)arg;
    int rc = pthread_mutex_trylock(&mtx);

    if (rc == 0) {
        puts("Worker acquired mtx.");
        pthread_mutex_unlock(&mtx);
    } else if (rc == EBUSY) {
        puts("Worker found mtx busy and did not wait.");
    } else {
        puts("Mutex error.");
    }
    return NULL;
}

int main(void) {
    pthread_t worker;

    pthread_mutex_lock(&mtx);
    puts("Main holds mtx.");
    if (pthread_create(&worker, NULL, try_once, NULL) != 0) return 1;
    if (pthread_join(worker, NULL) != 0) return 1;
    pthread_mutex_unlock(&mtx);

    puts("Main released mtx.");
    if (pthread_create(&worker, NULL, try_once, NULL) != 0) return 1;
    if (pthread_join(worker, NULL) != 0) return 1;

    pthread_mutex_destroy(&mtx);
    return 0;
}
