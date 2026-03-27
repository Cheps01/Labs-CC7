# Bridge Crossing Simulation

A concurrent simulation of students crossing a bridge, where only one direction of traffic is allowed at a time with a maximum capacity of 4 students.

## Folder Structure

```
Lab7/
├── main.c              # Application entry point
├── Makefile            # Build configuration
├── app/                # Application logic
│   ├── bridge.c        # Bridge crossing implementation
│   └── bridge.h        # Bridge header declarations
├── lib/                # Threading and utilities
│   ├── threads.c       # Thread synchronization utilities
│   ├── threads.h       # Threading header
│   ├── utils.c         # Helper functions (timing, random)
│   └── utils.h         # Utilities header
└── bin/                # Compiled object files
```

## Separation of Concerns

The codebase separates **threading infrastructure** from **application logic**:

### Threading Layer (`lib/`)

- **`threads.c/h`**: Abstracts pthread operations into simple wrapper functions:
  - `lock()` / `unlock()` - mutex operations
  - `wait()` / `signal()` / `broadcast()` - condition variable operations
  - `init_threads()` - creates and joins N threads

- **`utils.c/h`**: General-purpose utilities:
  - `randint()` - generates random integers
  - `start_timer()` / `end_timer()` - measures waiting times

### Application Layer (`app/`)

- **`bridge.c/h`**: Contains the simulation logic:
  - `student_cross_bridge()` - thread function representing a student
  - `access_bridge()` - manages bridge entry with capacity and direction constraints
  - `exit_bridge()` - handles bridge exit and direction switching
  - Shared state: `on_bridge`, `current_dir`, `waiting_left`, `waiting_right`

## Building the Project

Run `make` from the project root:

```bash
make
```

This will:
1. Create the `bin/` directory if it doesn't exist
2. Compile all source files into object files in `bin/`
3. Link all object files into the `bridge_system` executable

To clean build artifacts:

```bash
make clean
```

## Concurrency Model

The application uses **POSIX threads** synchronized with a **lock** and **condition variables**:

### Synchronization Primitives

| Primitive | Purpose |
|-----------|---------|
| `pthread_mutex_t mutex` | Protects all shared state from race conditions |
| `pthread_cond_t left` | Signals when students can cross left |
| `pthread_cond_t right` | Signals when students can cross right |

### Shared State

| Variable | Description |
|----------|-------------|
| `on_bridge` | Current number of students on bridge (max 4) |
| `current_dir` | Current allowed direction (0=right, 1=left) |
| `waiting_left` | Students waiting to cross left |
| `waiting_right` | Students waiting to cross right |

### Bridge Access Protocol

1. **Entry**: A student waits if:
   - The bridge is at capacity (4 students)
   - The current direction differs from their desired direction

2. **Exit**: When a student exits:
   - If last on bridge: direction switches to the side with more waiters
   - If not last: signals another student of same direction if capacity allows

### Direction Balancing

When the bridge empties, the system prioritizes the direction with more waiting students to prevent starvation.

## Usage

After building, run the simulation:

```bash
./bridge_system
```

The simulation creates 10 student threads (configurable via `THREADS` in `main.c`). Each student:
1. Arrives with a random destination (left or right)
2. Waits a random duration
3. Crosses the bridge (subject to capacity/direction constraints)
4. Exits and logs the event

Output includes total students crossed and average waiting time.
