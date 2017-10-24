# Real-time cloth using Position-Based Dynamics in OpenCL
Course assignment for CS 348C: Animation and Simulation, Fall 2016. Based on the paper [Position Based Dynamics](http://matthias-mueller-fischer.ch/publications/posBasedDyn.pdf) by Macklin and Müller.

<img src="https://raw.githubusercontent.com/bwiberg/position-based-dynamics/master/video.gif" width="500" >

## Libraries
* Based on the cl-gl-bootstrap template for C++ project with OpenCL-OpenGL interoperability, written by me.
* Uses my simple OpenGL-wrapper [BWGL](https://github.com/bwiberg/bwgl)
* Uses [NanoGUI](https://github.com/wjakob/nanogui) for the UI, which in turn depends on GLFW, Eigen and NanoVG
* Uses [GLM](http://glm.g-truc.net/0.9.8/index.html) for vector- and matrix operations
* Uses [SOIL](http://www.lonesock.net/soil.html) for OpenGL texture loading
* Uses [json](https://github.com/nlohmann/json) for JSON scene specification

## Instructions
The idea with the cl-gl-bootstrap template is to allow for multiple simulation demos to be run in the same executable. This is accomplished by having multiple "scenes" available on startup. To start the PBD-simulation scene, press the "LOAD" button in the "General Controls" UI pane and select the only available scene.

The UI displays the average time for a simulation frame (not the rendering) in the Scene Controls UI, as well as the current average FPS (which takes into account both simulation and rendering).

Recordings created by pressing the button with the record symbol are exported through FFMPEG and saved as .mp4-files in the /output folder. Beware, the average simulation time will be incorrect when recording (don't know why yet).

To load a specific cloth setup, use the buttons in the interface on the left ("Scene Controls"). The "Cloth Parameters" UI to the right can be used to adjust the fluids properties, and parameter configurations can be loaded/saved using the provided buttons.

### Parameters
* numSubSteps - How many times the position-correction step should be done each frame (10-40 is good)
* deltaTime - The size if the timestep for each frame, in seconds (0.166 works well, yielding 60 frames per second of simulation)
* k_stretch - Higher value = less stretchy cloth
* k_bend - Higher value = less bendy cloth

### Controls
* Left Shift + Left-click on vertex - pin vertex in space
* Left-click + move on vertex - move vertex in space
* WASD - rotate camera constant amount each update (good for recordings)
* Left Alt + Left-click and mouse -  rotate camera freely

## Build instructions
The program has only been tested on MacOS so far, so it will probably not run on Linux or Windows without modifications to the CMake configuration and some parts of the source dode. 

The only dependency which is not included in the source code is GLM (which is found by CMake and must be installed on the machine), the rest are included as git submodules. 

1. Get the source code using `git clone https://github.com/bwiberg/position-based-dynamics.git`
2. Fetch all submodules using `git submodule update --init --recursive`
3. Create a subdirectory named e.g. /build
4. Run `cmake -DCMAKE_BUILD_TYPE=Debug ..` and then `make` from that directoy (NOTE: the program will crash with the output "illegal hardware instruction" on MacOS if using the release configuration, I will have to investigate why)
5. Run the program using `./pbf`. Optional program flags and arguments are:
    * `-w 1280 720` Opens the window with a resolution of 1280x270.
    * `-f`  Causes the program to run in fullscreen. Overrides the `-w` flag. (NOTE: must specify the `-cl` flag when using the `-f` flag)
    * `-cl 0 1` Automatically selects the OpenCL context as alternative 0 and the OpenCL device as alternative 1.
    