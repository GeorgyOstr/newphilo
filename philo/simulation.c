#include "philo.h"

void start(t_sim *sim)
{
    if (!gettimeofday(&sim->sim_start, NULL))
        return (sim->error = GETTIME_ERROR);
    sim->sim_start = add_timeval(&sim->sim_start, &(struct timeval){0, 500000});

}