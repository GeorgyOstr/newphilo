#include "philo.h"

static void threads(t_sim *sim);


void start(t_sim *sim)
{
    if (gettimeofday(&sim->sim_start, NULL))
    {
        sim->error = GETTIME_ERROR;
        return ;
    }
    sim->sim_start = add_timeval(&sim->sim_start, &(struct timeval){0, 500000});
    threads(sim);
}

static void threads(t_sim *sim)
{
    unsigned    i;

    i = 0;
    while(i < sim->args.number_of_philos)
    {
        if (pthread_create(&sim->philos[i].thread_id, NULL, &philo_routine, &sim->philos[i]))
        {
            pthread_mutex_lock(sim->finish);
            sim->sim_finished = true;
            sim->error = THREAD_ERROR;
            pthread_mutex_unlock(sim->finish);
            i++;
            break ;
        }
    }
    i--;
    while (i > 0)
        pthread_join(sim->philos[i--].thread_id, NULL);
} 

