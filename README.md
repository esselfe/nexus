![Nexus logo](images/nexus-logo.png)  

Nexus is a 3D Linux program written in C using OpenGL/Mesa, GLU and SDL2.  
The program renders a scene with multidirectional camera movement.  
Different modules can be implemented, like a file browser, text editor or memory meter.  
A low OpenGL version (1.1) is used so the project can be run on the most diversified/old hardware.  
The development status is currently in alpha stage.  

## Dependencies

You will need to install couple tools and libraries in order to compile and run this project.  
On Debian and Ubuntu systems, install:  
```sudo apt install make gcc libgl1-mesa-dev libglu1-mesa-dev libsdl2-dev```  
On Gentoo, install:  
```sudo emerge media-libs/libglvnd media-libs/mesa media-libs/glu media-libs/libsdl2```  
On Fedora, install:  
```sudo dnf install make gcc mesa-libGL-devel mesa-libGLU-devel SDL2-devel```  
On OpenSuse, install:  
```sudo zypper install make gcc Mesa-libGL-devel glu-devel libSDL2-devel```  
On Arch, install:  
```sudo pacman -S make gcc mesa glu sdl2```  

## Compile and run

To compile the program, run:  
```make```  
then  
```./nexus```  

Enjoy!

