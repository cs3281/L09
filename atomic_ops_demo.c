#include <stdbool.h>
#include <stdio.h>

static inline int atomic_exchange(int *ptr, int value) {
    return __atomic_exchange_n(ptr, value, __ATOMIC_SEQ_CST);
}

static inline bool atomic_compare_and_swap(int *ptr, int expected, int desired) {
    return __atomic_compare_exchange_n(ptr, &expected, desired, false,
                                      __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

int main(void) {
    int flag = 0;

    int old = atomic_exchange(&flag, 1);
    printf("Exchange: old = %d, flag = %d\n", old, flag);

    old = atomic_exchange(&flag, 1);
    printf("Exchange again: old = %d, flag = %d\n", old, flag);

    int other_flag = 0;

    bool ok = atomic_compare_and_swap(&other_flag, 0, 1);
    printf("CAS: success = %d, flag = %d\n", ok, other_flag);

    ok = atomic_compare_and_swap(&other_flag, 0, 1);
    printf("CAS again: success = %d, flag = %d\n", ok, other_flag);
    return 0;
}
