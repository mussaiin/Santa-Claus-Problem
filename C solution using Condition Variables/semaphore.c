#include <pthread.h>
#include <assert.h>
#include <stdlib.h>

#include "semaphore.h"

struct sema_state
{
	pthread_mutex_t mutex;
	int value;
	pthread_cond_t queue;
};

semaphore_t CreateSemaphore(int initial_value)
{
	struct sema_state *s = (struct sema_state *)malloc(sizeof(struct sema_state));
	assert(s != NULL);
	int ret = pthread_mutex_init(&s->mutex, NULL);
	assert(ret == 0);
	s->value = initial_value;
	ret = pthread_cond_init(&s->queue, NULL);
	assert(ret == 0);
	return (semaphore_t)s;
}

void CloseSemaphore(semaphore_t sema)
{
	struct sema_state *s = (struct sema_state *)sema;
	int ret = pthread_mutex_destroy(&s->mutex);
	assert(ret == 0);
	ret = pthread_cond_destroy(&s->queue);
	free((char *)s);
}

void Wait(semaphore_t sema)
{
	struct sema_state *s = (struct sema_state *)sema;
	int ret = pthread_mutex_lock(&s->mutex);
	assert(ret == 0);
	s->value--;
	if (s->value < 0)
	{
		ret = pthread_cond_wait(&s->queue, &s->mutex);
		assert(ret == 0);
	}
	ret = pthread_mutex_unlock(&s->mutex);
	assert(ret == 0);
}

void Release(semaphore_t sema)
{
	struct sema_state *s = (struct sema_state *)sema;
	int ret = pthread_mutex_lock(&s->mutex);
	assert(ret == 0);
	s->value++;
	if (s->value <= 0)
	{
		ret = pthread_cond_signal(&s->queue);
		assert(ret == 0);
	}
	ret = pthread_mutex_unlock(&s->mutex);
	assert(ret == 0);
}