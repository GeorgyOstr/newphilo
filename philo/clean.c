#include <philo.h>

void clean(t_sim *sim)
{
    unsigned i;

    i = 0;
    while(i < sim->args.number_of_philos)
        pthread_mutex_destroy(&sim->forks_locks[i++]);
    pthread_mutex_destroy(&sim->finish);
    pthread_mutex_destroy(&sim->write);
    free(sim->forks_states);
    free(sim->forks_locks);
    free(sim->philos);
}