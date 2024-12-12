# Voxel Engine Project

This project is the foundation for a future voxel simulator. It is currently in the early stages of development, focusing on setting up the basic rendering and input systems using OpenGL and GLFW.

## Current State
- **Rendering Shapes**: The project includes code for rendering basic shapes like pyramids and cubes using OpenGL.
- **Camera Control**: Implemented a camera system allowing movement and orientation control through keyboard and mouse input.
- **Shader Management**: Utilizes custom shader classes to handle vertex and fragment shaders.
- **Texture Mapping**: Basic texture loading and mapping functionalities are in place.

## Future Plans
- **Voxel Simulation**: The primary goal is to expand the project into a full-fledged voxel simulator.
- **Optimized Rendering**: Implement efficient rendering techniques suitable for handling large numbers of voxels.
- **Physics Integration**: Introduce physics to simulate realistic interactions within the voxel environment.
- **User Interaction**: Develop intuitive controls and interfaces for users to interact with the voxel world.

## Getting Started

To run the project:

1. Ensure you have Visual Studio 2022 installed.
2. Clone the repository and open the solution file.
3. Build the project with C++14 standard compliance.
4. Run the executable to see the current rendering capabilities.

## Dependencies
- **GLFW**: For window creation and input handling.
- **GLAD**: To manage OpenGL function pointers.
- **GLM**: Mathematics library for graphics software.
- **STB Image**: For loading images as textures.
