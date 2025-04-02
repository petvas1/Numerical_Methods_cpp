# Differential Equation Solver

This C++ program uses the Runge-Kutta method to solve a system of ordinary differential equations (ODEs). It models a driven, damped harmonic oscillator with nonlinear damping and an external forcing term. The results are saved in `data2.dat`.

## Key Equations
The system consists of three equations:
- \( y'(t) = y_1(t) \)
- \( y_1'(t) = -\gamma y_1(t) - y_0^3(t) + F(t) \)
- \( y_2'(t) = F(t) y_1(t) \)

Where:
- \( F(t) = 7.5 \cos(t) \) is the external force.
- \( \gamma = 0.05 \) is the damping coefficient.
