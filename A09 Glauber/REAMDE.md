# Glauber Dynamics Simulation

This C++ program simulates the Glauber dynamics of a spin system on a 2D lattice using the Ising model. It performs Monte Carlo simulations for various temperature values and computes the evolution of the system's spins over time. The program also computes the magnetization of the system and saves the results to a file (`glauber1.dat`).

## Key Features:
- **Glauber dynamics**: A method for simulating the behavior of spins in a lattice under the influence of temperature and surrounding spins.
- **Monte Carlo simulations**: Randomly selecting lattice sites and updating spins based on probabilistic rules.
- **Temperature dependence**: The program runs the simulation for different temperatures (`T = 2.0, 2.22, 2.26, 2.28, 2.35`).
- **Magnetization**: Tracks the magnetization of the system during the simulation.
- **Data output**: Results are written to `glauber1.dat` for further analysis or visualization.

## Usage:
1. Compile the code using a C++ compiler:
   ```sh
   g++ -o glauber_simulation glauber_simulation.cpp
