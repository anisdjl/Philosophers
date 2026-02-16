#include <stdio.h>
#include <pthread.h>

void*	routine()
{
	printf("testing threads\n");
	return NULL;
}
int main(void)
{
	pthread_t t1; // thread struct
	pthread_t t2;

	if (pthread_create(&t2, NULL, &routine, NULL )!= 0)
	{
		printf("error while creating the thread\n");
		return (1);
	}
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
		printf("error while creating the thread\n");
		return (1);
	} // cree les threads
	pthread_join(t1, NULL); // wait for the thread to finish its execution
	pthread_join(t2, NULL); // wait for the thread to finish its execution
	return 0;
}
