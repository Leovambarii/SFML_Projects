<h1>Gravity Project Simulation</h1>
<p>
    This is a simple particle simulation project that demonstrates the behavior of particles under the influence of gravity sources.
</p>

<h2>Dependencies</h2>
<ul>
    <li>SFML library for graphics and input handling.</li>
</ul>
<h2>Running the Simulation</h2>
<p>
    Compile and run the main.cpp file.
    <ul>
    <li>To compile - run this command in terminal: <br>g++ main.cpp header.cpp  Particle.cpp GravitySource.cpp -o gravity_sim -lsfml-graphics -lsfml-window -lsfml-system</li>
    <li>To run - run this command in terminal: <br>./gravity_sim</li>
    </ul>
    The simulation window will open and start running.
</p>
<h2>Controls</h2>
<ul>
    <li>Press the Esc key or close the window to exit the simulation.</li>
    <li>Press the Space key to pause/resume the simulation.</li>
    <li>Press the C key to clear all particles.</li>
    <li>Press the V key to clear all gravity sources.</li>
    <li>Left-click to add multiple particles at the mouse position.</li>
    <li>Right-click to add a gravity source at the mouse position.</li>
    <li>Use the mouse wheel to add a single particle at the mouse position.</li>
</ul>
<h2>Implementation</h2>
<p>
    The simulation is implemented using the following classes:
</p>
<h2>GravityProject Class</h2>
<p>
    This class initializes the simulation window and handles input events, updates particle physics, checks for collisions between particles and gravity sources, and renders the simulation graphics.
</p>
<h2>Particle Class</h2>
<p>
    This class represents a single particle in the simulation. Each particle has a position, velocity, color, radius and trajectory trace. The particle's physics is updated by applying the gravitational force exerted by each gravity source in the simulation.
</p>
<h2>GravitySource Class</h2>
<p>
    This class represents a gravity source in the simulation. Each gravity source has a position, strength, and radius. The strength determines the magnitude of the gravitational force exerted by the source on particles in the simulation.
</p>