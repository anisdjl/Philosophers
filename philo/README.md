*This project has been created as part of the 42 curriculum by adjelili*
 
# Philosophers
 
## Description
 
**Philosophers** is a project from the 42 curriculum that tackles the classic **Dining Philosophers Problem**, originally formulated by Edsger Dijkstra in 1965. It is a foundational exercise in concurrent programming and synchronization.
 
The goal is to simulate a group of philosophers sitting at a round table, alternating between three states: **thinking**, **eating**, and **sleeping**. A fork is placed between each pair of adjacent philosophers. To eat, a philosopher must pick up both the fork to their left and the fork to their right — which introduces the risk of **deadlock** and **data races** if not handled correctly.
 
This project is split into two parts:
 
- **Mandatory**: Each philosopher is a **thread**, and forks are protected using **mutexes**.
- **Bonus**: Each philosopher is a **process**, and forks are managed through **semaphores**.
The simulation must ensure that no philosopher starves, and it must detect and report the moment a philosopher dies (if they go too long without eating).
 
---
 
## Instructions
 
### Requirements
 
- Linux or macOS
- `gcc` or `cc`
- `make`
### Compilation
 
**Mandatory part (threads):**
```bash
cd philo
make
```
 
### Execution
 
```
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
 
| Argument | Description |
|---|---|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` (ms) | Time before a philosopher dies if they haven't started eating |
| `time_to_eat` (ms) | Time it takes to eat |
| `time_to_sleep` (ms) | Time spent sleeping |
| `number_of_times_each_philosopher_must_eat` | *(Optional)* Simulation ends when all philosophers have eaten this many times |
 
### Examples
 
```bash
# 5 philosophers, none should die
./philo 5 800 200 200
 
# 4 philosophers, none should die
./philo 4 410 200 200
 
# 1 philosopher, must die (only one fork available)
./philo 1 800 200 200
 
# Simulation ends after each philosopher eats 7 times
./philo 5 800 200 200 7
```
 
### Cleaning
 
```bash
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Recompile from scratch
```
 
---
 
## Resources
 
### Documentation & References
 
- [Dining Philosophers Problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads (pthreads) — man7.org](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [pthread_mutex_lock — Linux manual](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [pthread_create — Linux manual](https://man7.org/linux/man-pages/man3/pthread_create.3p.html)
- [sem_overview — POSIX Semaphores](https://man7.org/linux/man-pages/man7/sem_overview.7.html)
- [Race Conditions and Deadlocks — GeeksForGeeks](https://www.geeksforgeeks.org/deadlock-in-operating-system/)
- [Valgrind + Helgrind for thread debugging](https://valgrind.org/docs/manual/hg-manual.html)
### AI Usage
 
AI was used during this project for the following purposes:
 
- **Understanding concepts**: Clarifying the difference between mutexes and semaphores, and how to reason about deadlock prevention strategies.
- **Debugging**: Helping identify potential data races and discussing memory model behavior in multithreaded programs.
AI was **not** used to write or generate any part of the source code. All implementation decisions were made independently.
 