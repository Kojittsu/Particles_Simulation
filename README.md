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

- Particle initialization :
  - Particles are initialized with different parameters, acceleration is set to zero.

- Random particles initialization :
  - Random particles are initialized with different parameters.
  - Position is randomly set in the box.
  - Velocity is randomly set in [-maxVelocity, maxVelocity] for each components.
  - Radius is randomly set in [minRadius, maxRadius].
  - Mass is randomly set in [minMass, maxMass].
  - Acceleration is set to globalAcceleration.
  - Color is randomly set.
  - Name is empty.

- Universe initialization :
  - Universe is initialized with different parameters.

- Universe simulation :
  - Particle-particle collisions
  - Particle-box collisions.
  - Particle-circle collisions if circle radius is not zero.
  - Global acceleration set to all particles.
  - Energy restitution must be set in [0,1], 0 mean all energy is loss, 1 mean energy conservation.

- Universe rendering :
  - Create a window that display universe simulation.
  - Window's dimensions are set to the dimensions of the box multiplied by a scale factor pixels (1 mean that one pixel is equivalent to one meters).
  - Simulation speed is set to a speed factor (1 mean real time simulation).
  - Display simulation time in runtime.
  - GUI clickable buttons.

- Miscellaneous :
  - A datafile name can be set to save particles motions over time.

## Configuration file

This is the YAML configuration file structure :
```yaml
particles:
  - position: [double, double] # Particle position in meters
    velocity: [double, double] # Particle velocity in meters
    radius: double             # Particle radius in meters
    mass: double               # Particle mass in kilograms
    color: [int, int, int]     # Particle color in RGB format
    name: string               # Particle name (can be empty)

  # Add as many particles as you want

randomParticles:
  numbers: int         # Number of random particles
  maxVelocityX: double # Particle max X random velocity in meters/second
  maxVelocityY: double # Particle max Y random velocity in meters/second
  minRadius: double    # Particle min random radius in meters
  maxRadius: double    # Particle max random radius in meters
  minMass: double      # Particle min random mass in kilograms
  maxMass: double      # Particle max random mass in kilograms

box:
  xOrigin: double # Box X origin in meters
  yOrigin: double # Box Y origin in meters
  length: double  # Box length in meters
  height: double  # Box height in meters

circle:
  centerX: double # Circle X center in meters
  centerY: double # Circle X center in meters
  radius: double  # Circle radius in meters

simulation:
  deltaTime: double
  applyGravity: bool                   # Compute Newton's law of universal gravitation
  globalAcceleration: [double, double] # Global acceleration applied to all objects
  coefficientRestitution: double       # Energy restitution during collision (1.0 mean energy conservation)
  dataFileName: string                 # data file name for saving particles positions through time (can be empty)

visualization:
  scaleFactorPixels: double
  speedFactor: double
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