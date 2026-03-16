# Particles Simulation

![GitHub repo size](https://img.shields.io/github/repo-size/Kojittsu/Particles_Simulation)
![GitHub contributors](https://img.shields.io/github/contributors/Kojittsu/Particles_Simulation)
![GitHub license](https://img.shields.io/github/license/Kojittsu/Particles_Simulation)
![GitHub issues](https://img.shields.io/github/issues/Kojittsu/Particles_Simulation)
[![built with nix](https://img.shields.io/static/v1?logo=nixos&logoColor=white&label=&message=Built%20with%20Nix&color=41439a)](https://builtwithnix.org)

This project is a particle simulation using the C++ programming language. It models the interaction of particles in a 3D universe and render it using the the [GLFW](https://www.glfw.org/) library.


## 🖼️ Gallery

<p align="center">
   <img src="./.github/assets/pictures/video.gif" style="margin-bottom: 15px;"/> <br>
</p>


## 📐 Explicit Euler for Particle Dynamics Resolution

In this particle simulation, the explicit Euler method is employed to resolve particle dynamics. This method is a numerical approach for solving first-order ordinary differential equations, such as those describing particle motion in our simulated universe.\
For more details see [Euler method Wiki Page](https://en.wikipedia.org/wiki/Euler_method).

In our case, the formula for updating the position and velocity of particles using the explicit Euler method can be expressed as follows:\
For velocity : `newVelocity = currentVelocity + acceleration * deltaTime`\
For position : `newPosition = currentPosition + velocity * deltaTime`\
Where `deltaTime` is the size of the time step used in the simulation.

The explicit Euler method is simple to implement but can introduce approximation errors. More advanced numerical methods, such as Runge-Kutta methods or Verlet integration, can be employed to obtain more accurate results in certain cases.

## 📚 Features

- Particle initialization :
  - Particles are initialized with different parameters, acceleration is set to zero.

- Universe initialization :
  - Universe is initialized with different parameters.

- Universe simulation :
  - Particle-particle collisions
  - Particle-boxes collisions.
  - Global acceleration set to all particles.
  - Energy restitution must be set in [0.0, 1.0], 0.0 mean all energy is loss, 1.0 mean energy conservation.

- Universe rendering :
  - Create a window that display universe simulation using GLFW.
  - Simulation speed is set by a speed factor (1.0 mean real time simulation).
  - Rendering is scale up/down by a scale factor (1.0 mean that 1 meter is 1 scene unit).
  - Graphical user interface :
    - Control the simulation through a graphical interface using the [Dear ImGui](https://github.com/ocornut/imgui) library.
    - Usage of the [ImPlot](https://github.com/epezent/implot) library for graphs rendering.

- Miscellaneous :
  - A datafile name can be set to save particles motions over time.

## 📖 Documentation

The project documentation detailing its codebase is available here: [Particles Simulation Documentation](https://kojittsu.github.io/Particles_Simulation/)

## 📝 Configuration file

This is the YAML configuration file structure :
```yaml
particles:
  - position: [double, double, double] # Particle position in meters
    velocity: [double, double, double] # Particle velocity in meters
    radius: double                     # Particle radius in meters
    mass: double                       # Particle mass in kilograms
    color: [int, int, int]             # Particle color in RGB format
    name: string                       # Particle name (can be empty)

  # Add as many particles as you want

boxes:
  - origin: [double, double, double] # Box origin in meters
    length: double                   # Box length in meters
    height: double                   # Box height in meters
    depth: double                    # Box depth in meters

  # Add as many boxes as you want

simulation:
  deltaTime: double
  applyGravity: bool                           # Compute Newton's law of universal gravitation
  globalAcceleration: [double, double, double] # Global acceleration applied to all objects
  coefficientRestitution: double               # Energy restitution during collision (1.0 mean energy conservation)
  dataFileName: string                         # data file name for saving particles positions through time (can be "")

visualization:
  speedFactor: double # Factor for rendering speed (1.0 mean real time universe rendering)
  scaleFactor: double # Factor for scale up/down rendering values (usefull for rendering with big value for example)
```
## 📦 Dependencies

- Nix package manager installed on your system.

## Installation

- Install with [Nix](https://github.com/NixOS/nix) package manager
```bash
nix profile add github:Kojittsu/Particles_Simulation
```

- Install on NixOs

Add the input to your flake configuration:
```nix
inputs = {
  nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";

  particles-simulation = {
    url = "git+https://github.com/Kojittsu/Particles_Simulation";
    inputs.nixpkgs.follows = "nixpkgs";
  };
  
  # ... Other inputs
};
```
Add the package to environment.systemPackages:
```nix
{ pkgs, inputs, ... }:
{
  environment.systemPackages = with pkgs; [
    inputs.noctalia.packages.${pkgs.stdenv.hostPlatform.system}.default
    
    # ... Other packages 
  ];
}
```

## Running the app

1. Clone the repository
```bash
git clone --recursive https://github.com/Kojittsu/Particles_Simulation.git
```

2. Access the repository
```bash
cd Particles_simulation
```

3. Use nix run to execute the program
```bash
nix run . -- <config_file>
```
where `config_file` is your configuration file.

## ⚙️ Development environment

1. Clone the repository
```bash
git clone --recursive https://github.com/Kojittsu/Particles_Simulation.git
```

2. Access the repository
```bash
cd Particles_simulation
```

3. Enter Nix development environment
```bash
nix develop
```

- To compile the program type
```bash
make
```

- To execute the program type
```bash
./particle-simulation-executable <config_file>
```
where `config_file` is your configuration file.

- To clean up the generated files type
```bash
make clean
```

- To compile doxygen documentation type
```bash
cd docs
doxygen Doxyfile
```

- To update flake inputs
```bash
nix flake update
```

- To update git submodules
```bash
git submodule update --remote
```
