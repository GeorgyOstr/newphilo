#include "philo.h"

int main(int argc, char **argv)
{
    t_sim   sim;

    ft_bzero(&sim, sizeof(sim));
    if (argc != 5 && argc != 6)
        return (ARGUMENTS_ERROR);
    if (parse_input(argc, argv, &sim))
        return (sim.error);
    if (initialize(&sim))
        return (sim.error);
    start(&sim);
    clean(&sim);
    return (sim.error);
}

static enum e_errors    parse_input(int argc, char **argv, t_sim *sim)
{
    sim->args.number_of_eat_to_finish = 0;
    if (readarg(argv[1], &sim->args.number_of_philos) 
        || readarg(argv[2], &sim->args.time_to_die)
        || readarg(argv[3], &sim->args.time_to_eat)
        || readarg(argv[4], &sim->args.time_to_sleep)
        || (argc == 6 && readarg(argv[5], &sim->args.number_of_eat_to_finish))
    )
        sim->error = ATOI_ERROR;
    return (sim->error);
}

static  enum e_errors   initialize(t_sim *sim)
{
    unsigned i;

    sim->philos = ft_calloc(sim->args.number_of_philos, sizeof(*sim->philos));
    sim->forks_locks = ft_calloc(sim->args.number_of_philos, sizeof(*sim->forks_locks));
    sim->forks_states = ft_calloc(sim->args.number_of_philos, sizeof(*sim->forks_states));
    if (!sim->philos || !sim->forks_locks || !sim->forks_states)
    {
        return (free(sim->philos), free(sim->forks_locks), free(sim->forks_states),
        sim->error = MALLOC_ERROR);
    }
    if (initialize_locks(sim))
        return (free(sim->philos), free(sim->forks_locks), free(sim->forks_states),
        sim->error = MALLOC_ERROR);
    while (i < sim->args.number_of_philos)
    {
        initialize_philo(&sim->philos[i], sim, i);
        i++;
    }
    return (NO_ERROR);
}

static enum e_errors initialize_locks(t_sim *sim)
{
    unsigned    i;

    if (pthread_mutex_init(&sim->write, NULL))
        return (sim->error = MUTEX_INIT_ERROR);
    if (pthtread_mutex_init(&sim->write, NULL))
        return (pthread_mutex_destroy(&sim->write), sim->error = MUTEX_INIT_ERROR);
    i = 0;
    while (i < sim->args.number_of_philos)
    {
        if (pthtread_mutex_init(&sim->forks_locks[i], NULL))
        {
            if (i != 0)
                pthread_mutex_destroy(&sim->forks_locks[0]);
            while (i > 0)
                pthread_mutex_destroy(&sim->forks_locks[i--]);
            return (pthread_mutex_destroy(&sim->write), pthread_mutex_destroy(&sim->finish), sim->error = MUTEX_INIT_ERROR);            
        }
    }
    return (NO_ERROR);
}

static void initialize_philo(t_philo *philo, t_sim *sim, unsigned num)
{
    philo->args = &sim->args;
    philo->eat_count = 0;
    philo->eat_enough_count = &sim->eat_enough_count;
    philo->finish = sim->finish;
    philo->write = sim->write;
    philo->philo_num = num + 1;
    philo->sim_finished = &sim->sim_finished;
    philo->sim_start = &sim->sim_start;
    philo->last_ate_time = sim->sim_start;
    philo->forks_states[0] = &sim->forks_states[num + 1];
    philo->forks_states[1] = &sim->forks_states[(num + 2) % sim->args.number_of_philos];
    philo->forks_locks[0] = &sim->forks_locks[num + 1];
    philo->forks_locks[1] = &sim->forks_locks[(num + 2) % sim->args.number_of_philos];
    if (num % 2 == 1)
    {
        philo->forks_states[1] = &sim->forks_states[num + 1];
        philo->forks_states[0] = &sim->forks_states[(num + 2) % sim->args.number_of_philos];
        philo->forks_locks[1] = &sim->forks_locks[num + 1];
        philo->forks_locks[0] = &sim->forks_locks[(num + 2) % sim->args.number_of_philos];
    }
}

