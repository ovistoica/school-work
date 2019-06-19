/**
 * SO, 2019
 * Lab #8
 *
 * Task #3, lin
 *
 * Thread safety
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <utils.h>

/* *******************************
 * API to mark a critical region 
 * */
#ifdef USE_SPINLOCK
static bool lock;
#else
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
#endif

void acquire_lock(void)
{
#ifdef USE_SPINLOCK
    /* Busy waiting */
    while(1) {
        if(__atomic_test_and_set(&lock, __ATOMIC_ACQUIRE)) {
            break;
        }

        /* TODO2: Implement spinlock lock method 
         * HINT: use atomic intrutions. ex: __atomic_test_and_set */

    }
#else
		pthread_mutex_lock(&lock);
#endif
}

void release_lock(void)
{
#ifdef USE_SPINLOCK
        __atomic_clear(&lock, __ATOMIC_RELEASE);
        /* TODO2: Implement spinlock release method 
         * HINT: use atomic intrutions. ex: __atomic_clear */

#else
		pthread_mutex_unlock(&lock);
#endif
}
/*******************************
 * end of API */

