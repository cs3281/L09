#include <pthread.h>
#include <stdio.h>

int iterations = 1000000;
int common = 162;
int flag;

static inline int atomic_exchange(int *ptr, int value) {
    return __atomic_exchange_n(ptr, value, __ATOMIC_SEQ_CST);
}

static inline void atomic_store(int *ptr, int value) {
    __atomic_store_n(ptr, value, __ATOMIC_SEQ_CST);
}

void spinlock_init(void) {
    flag = 0;
}

void spinlock_lock(void) {
    while (atomic_exchange(&flag, 1) == 1) {
        /* Spin. */
    }
}

void spinlock_unlock(void) {
    atomic_store(&flag, 0);
}

void *threadfun(void *arg) {
    (void)arg;
    for (int i = 0; i < iterations; ++i) {
        spinlock_lock();
        ++common;
        spinlock_unlock();
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    spinlock_init();

    if (pthread_create(&t1, NULL, threadfun, NULL) != 0) return 1;
    if (pthread_create(&t2, NULL, threadfun, NULL) != 0) return 1;
    if (pthread_join(t1, NULL) != 0) return 1;
    if (pthread_join(t2, NULL) != 0) return 1;

    printf("Expected: %d\n", 162 + 2 * iterations);
    printf("Observed: %d\n", common);
    return 0;
}
