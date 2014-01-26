#include "win.h"


void InitializeCriticalSection(CRITICAL_SECTION *s){
    pthread_mutexattr_init(&s->attr);
    pthread_mutexattr_settype(&s->attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&s->mutex, &s->attr);
}

void EnterCriticalSection(CRITICAL_SECTION *s){
    pthread_mutex_lock(&s->mutex);
}

void LeaveCriticalSection(CRITICAL_SECTION *s){
    pthread_mutex_unlock(&s->mutex);
}

void CreateThread(LPVOID ig1, size_t ig2, LPTHREAD_START_ROUTINE func, LPVOID arg, uint32_t ig3,  LPDWORD tid){
    pthread_t thread;
    pthread_create(&thread, NULL, func, arg);
}

void QueryPerformanceCounter(LARGE_INTEGER* hpc)
{
    uint64_t nsec_count;
    struct timespec ts1;
    uint64_t  nsec_per_tick;
    struct timespec ts2;

    if (clock_gettime(CLOCK_MONOTONIC, &ts1) != 0) {
        printf("clock_gettime() failed");
    }

    nsec_count = ts1.tv_nsec + ts1.tv_sec * 1000000000;

    if (clock_getres(CLOCK_MONOTONIC, &ts2) != 0) {
	    printf("clock_getres() failed");
    }

    nsec_per_tick = ts2.tv_nsec + ts2.tv_sec * 1000000000;

    hpc->QuadPart = (nsec_count/nsec_per_tick);

}

void QueryPerformanceFrequency(LARGE_INTEGER* hpc)
{
    hpc->QuadPart = 1000000000;
}
