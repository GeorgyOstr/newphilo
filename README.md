*This project has been created as part of the 42 curriculum by gostroum.*
## Description
This project implements the classic Dining Philosophers concurrency problem.
Check the subject.pdf in your intra (or I will provide you with the document on request).
The goal is to synchronize multiple philosopher threads so they can think, eat,
and sleep without starving or causing deadlocks, while respecting timing rules.

## Instructions
Build:
```bash
cd philo
make
```

Run:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200
```

## Resources
- The Dining Philosophers Problem (Wiki)
- pthreads documentation and other linux man pages
- 42 School "philosophers" subject PDF
- Github (various approaches, tests)
- Leetcode (another approach)
- https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html PTHREAD_MUTEX_INIT Always return 0
- https://pubs.opengroup.org/onlinepubs/9799919799/functions/pthread_mutexattr_destroy.html

## AI usage:
- Copilot autocomplete - (quick code rewriting)
- Codex/Claude
  - context analysis, issues bullets list, (toying with fix all, but not using, just dump in ai slop branch for comparison)
  - Drafting a project Makefile
  - Updating README

## Memo:
- All starts from thinking (can't all start from eating, and from sleeping doesn't make sense)
- fixed usleep time and fixed sim delay
- non monotonic time, retaking actual death time after detection
- bad protection on time_add overflow
- calloc weird
- Can't do anything against join fail
- Not handling mutex_destroy fail (still locked, probably join also fail or something terrible)
- All the args assumed to be positive int
- This programm not overflows for long time on systems with 32bit integers
