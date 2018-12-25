#ifndef _asysob_semaphore_
#define _asysob_semaphore_

typedef void *semaphore_t;

semaphore_t CreateSemaphore(int initial_value);
void CloseSemaphore(semaphore_t sema);

void Wait(semaphore_t sema);
void Release(semaphore_t sema);

#endif