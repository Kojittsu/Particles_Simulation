# Particle Simulation

This project is a particle simulation using the C++ programming language. It models the interaction of particles in a 2D universe.


## Explicit Euler for Particle Dynamics Resolution

In this particle simulation, the explicit Euler method is employed to resolve particle dynamics. This method is a numerical approach for solving first-order ordinary differential equations, such as those describing particle motion in our simulated universe.\
For more details see [Euler method Wiki Page](https://en.wikipedia.org/wiki/Euler_method).

In our case, the formula for updating the position and velocity of particles using the explicit Euler method can be expressed as follows:\
For velocity : `newVelocity = currentVelocity + acceleration * deltaTime`\
For position : `newPosition = currentPosition + velocity * deltaTime`\
Where `deltaTime` is the size of the time step used in the simulation.

The explicit Euler method is simple to implement but can introduce approximation errors. More advanced numerical methods, such as Runge-Kutta methods or Verlet integration, can be employed to obtain more accurate results in certain cases.

## Features

- Particle Initialization : Particles can be initialized with different positions, velocities, acceleration and radius.
- Interaction Simulation : The project simulates interactions between particles and universe boundaries.

## Configuration file

This is the Configuration file structure :
```json
{
    "particles": [
        {
            "position": ["float", "float"],
            "velocity": ["float", "float"],
            "radius": "float"
        }
    ],
    "box": {
        "xMin": "float",
        "xMax": "float",
        "yMin": "float",
        "yMax": "float"
    },
    "circle": {
        "centerX": "float",
        "centerY": "float",
        "radius": "float"
    },
    "simulation": {
        "deltaTime": "float",
        "stepNumbers": "int",
        "AccelerationX": "float",
        "AccelerationY": "float",
        "coefficientRestitution" : "float",
        "scaleFactorPixels" : "int"
    }
}
```

## Compilation and Execution

### Prerequisites

- A C++ compiler compatible with C++11 or higher (e.g., g++).
- `make` installed on your system.

### Compilation Instructions

1. Clone this GitHub repository to your local machine:
```bash
git clone https://github.com/lboudet/Particles_Simulation.git
cd Particles_simulation
```

2. Compile the project using make:
```bash
make
```

### Execution Instructions

To run the simulation, execute the compiled binary:
```bash
./ExecuteSimu
```

## Cleaning

To clean up the object files and the generated binary:
```bash
make clean
```

## Class attributes and methods

### Particle

The `Particle` class represents a particle in the simulated universe.

**Header file:** `include/particle.h`  
**Source file:** `src/particle.cpp`


#### Attributes

- `std::array<double, 2> position;`
- `std::array<double, 2> velocity;`
- `std::array<double, 2> acceleration;`
- `double radius;`

#### Methods

- `double getX() const;`
- `double getY() const;`
- `void setX(double x);`
- `void setY(double y);`
- `double getVX() const;`
- `double getVY() const;`
- `void setVX(double vx);`
- `void setVY(double vy);`
- `double getRadius() const;`
- `void update(double deltaTime);`
- `void printState(double currentTime) const;`


### Universe

The `Universe` class represents the universe containing the particles. It manages the interactions between particles and boundaries and also, their evolution over time.

**Header file:** `include/universe.h`  
**Source file:** `src/universe.cpp`


#### Attributes

- `std::vector<Particle> particles;`
- `Box box;`
- `double coefficientRestitution;`
- `double deltaTime;`

#### Methods

- `void run(int steps, const std::string& filename = "");`
- `void make_step();`
- `void save_step(std::ofstream &file, int step_number);`
- `void handleBoxCollision(Particle &particle, double coefficientRestitution);`


### Box

The `Box` class represents a box in which the particles lives (i.e. simulation space).

**Header file:** `include/box.h`  
**Source file:** `src/box.cpp`


#### Attributes

- `double xMin;`
- `double xMax;`
- `double yMin;`
- `double yMax;`

#### Methods

- `double getXMIN() const;`
- `double getYMIN() const;`
- `double getXMAX() const;`
- `double getYMAX() const;`
- `double getLength() const;`
- `double getHeight() const;`

