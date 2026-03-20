# Smart Parking System

A multithreaded parking lot simulator written in C using POSIX threads. The program spawns multiple car threads that compete for a limited number of parking spots, demonstrating thread synchronization with semaphores and mutexes. Each car's lifecycle (arrival, wait, park, leave) is logged with timestamps, and aggregate wait-time statistics are printed at the end.

## Project Structure

```
Lab6/
├── Makefile          # Build system
├── main.c            # Entry point: spawns threads, prints statistics
└── lib/
    ├── threads.h     # Thread globals and entry-point declaration
    ├── threads.c     # Car lifecycle logic and synchronization
    ├── parking.h     # Parking lot constants and function declarations
    ├── parking.c     # Parking lot data structure and spot management
    ├── utils.h       # Utility function declarations
    └── utils.c       # Logging, timing, and random number helpers
```

## Layered Architecture

The codebase separates concerns into distinct modules:

| Layer | Files | Responsibility |
|-------|-------|----------------|
| **Entry point** | `main.c` | Initializes synchronization primitives, spawns/joins threads, displays final statistics. |
| **Thread logic** | `lib/threads.c`, `lib/threads.h` | Defines the car thread lifecycle (`run_thread`), controls access to the lot via semaphore and mutex, and accumulates wait-time statistics. |
| **Parking lot** | `lib/parking.c`, `lib/parking.h` | Manages the fixed-size parking array (`set_spot` / `clear_spot`) and tracks the current occupancy count. |
| **Utilities** | `lib/utils.c`, `lib/utils.h` | Provides timestamped logging (`thread_log`), timing helpers (`start_time` / `finish_time`), a random integer generator, and a display function for the lot state. |

This separation means the synchronization and threading code never touches the parking data structure directly — it goes through `set_spot` and `clear_spot` — and the utility functions (logging, timing) are reusable without any coupling to the parking or thread logic.

## How It Works

1. **Initialization** — `main()` creates a mutex and a counting semaphore initialized to `N` (the lot capacity).
2. **Thread creation** — 10 car threads are spawned, each assigned a unique ID (1–10).
3. **Car lifecycle** (inside `run_thread`):
   - The car **arrives** and logs its arrival.
   - A timer starts, and the car calls `sem_wait` on the entry semaphore. If the lot is full, the thread blocks here until a spot opens.
   - Once admitted, the car **parks**: the mutex is acquired, a free slot in the `parking[]` array is claimed via `set_spot`, and the mutex is released. The wait time is recorded.
   - The car **stays** for a random 1–5 seconds (simulating real usage).
   - The car **leaves**: the mutex is acquired, the slot is freed via `clear_spot`, the mutex is released, and `sem_post` signals the semaphore so a waiting car can enter.
4. **Completion** — After all threads are joined, the program prints the total number of cars that parked and the average time each car spent waiting for a spot.

## Synchronization

| Primitive | Purpose |
|-----------|---------|
| **Counting semaphore** (`entry`) | Limits the number of cars inside the lot to `N`. Cars block on `sem_wait` when the lot is full and are unblocked by `sem_post` when another car leaves. |
| **Mutex** (`lock`) | Protects the shared `parking[]` array and the occupancy counter during spot assignment and release, ensuring only one thread modifies the lot state at a time. |

## Logging

Every significant event is printed with a timestamp via `thread_log`:

```
[Fri Mar 20 14:30:05 2026] Car 3: Arrived at parking lot.
[Fri Mar 20 14:30:05 2026] Car 3: Parked succesfully. Waited 0.00 seconds
[Fri Mar 20 14:30:08 2026] Car 3: Leaving parking lot.
```

Three events are logged per car: **arrival**, **successful parking** (with the time spent waiting), and **departure**.

## Statistics

At the end of the run the program displays:

- **Total parked cars** — how many cars successfully parked during the simulation.
- **Average waiting time** — the mean time (in seconds) that cars spent blocked waiting for a free spot.

These values are derived from per-car timers that measure the duration between arrival and semaphore acquisition.

## Building

The included Makefile compiles each source file into `bin/` and links them into the `smart_parking` binary:

```bash
make            # build the project
./smart_parking  # run the simulation
make clean      # remove object files
```
