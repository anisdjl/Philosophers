#include <stdio.h>
#include <pthread.h>

typedef struct s_data
{
    int             counter;
    pthread_mutex_t mutex;
}   t_data;

void    *increment(void *arg)
{
    t_data  *data = (t_data *)arg;
    int     i;

    i = 0;
    while (i < 10000)
    {
        pthread_mutex_lock(&data->mutex);    // Verrouille
        data->counter++;                     // Section critique
        pthread_mutex_unlock(&data->mutex);  // Déverrouille
        i++;
    }
    return (NULL);
}

int main(void)
{
    t_data      data;
    pthread_t   t1;
    pthread_t   t2;

    data.counter = 0;
    pthread_mutex_init(&data.mutex, NULL);

    pthread_create(&t1, NULL, increment, &data);
    pthread_create(&t2, NULL, increment, &data);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Counter = %d (attendu : 20000)\n", data.counter);

    pthread_mutex_destroy(&data.mutex);
    return (0);
}
