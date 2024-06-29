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

This is the YAML configuration file structure :
```yaml
particles:
  - position: [double, double]
    velocity: [double, double]
    radius: double
    mass: double

  # Add as many particles as you want

randomParticles:
  numbers: int
  maxVelocityX: double
  maxVelocityY: double
  minRadius: double
  maxRadius: double
  minMass: double
  maxMass: double

box:
  xOrigin: double
  yOrigin: double
  length: double
  height: double

circle:
  centerX: double
  centerY: double
  radius: double

simulation:
  deltaTime: double
  applyGravity: bool                   # Compute Newton's law of universal gravitation
  globalAcceleration: [double, double] # Global acceleration applied to all objects
  coefficientRestitution: double       # Energy restitution during collision (1.0 mean energy conservation)
  dataFileName: string                 # data file name for saving particles positions through time

visualization:
  scaleFactorPixels: double
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
./ExecuteSimu <config_file>
```
where `config_file` is your configuration file.

## Cleaning

To clean up the object files and the generated binary:
```bash
make clean
```