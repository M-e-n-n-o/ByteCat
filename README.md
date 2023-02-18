# ByteCat
[![License](https://img.shields.io/github/license/M-e-n-n-o/ByteCat.svg)](https://github.com/M-e-n-n-o/ByteCat/blob/main/LICENSE)  

Welcome to the ByteCat graphics engine!

I worked on this engine as a side project during my bachelor's degree in computer science.  
This project is my biggest work during my education, but has been stopped at the moment   
due to starting work on a new engine, which could probably be found on my GitHub profile.


# 🚀 Future plans
The ultimate goal for this project is to build an acutal usable and enjoyable to work with graphics engine  
with a simple and easy to navigate user interface. Aside from this the ByteCat engine should always be  
very easy to work with as a regular software engineer and for this reason will stay very code focussed.

A few other big goals for this project are to add solid VR, WebGL and maybe even WebXR support!


# 🏃 Getting started
ByteCat is currently only supported and tested for Windows, Linux & Android.   
You are always welcome to try and expand on this! :)  

### Cloning the repository
Start by cloning the repository with the command:  
``` git clone --recursive https://github.com/M-e-n-n-o/ByteCat ``` 

If the repository was cloned non-recursively (submodules were not initialized),   
use the following command to clone the submodules:  
```git submodule update --init``` 

### Setting up the build system
ByteCat is built using CMake, so first make sure you have CMake installed (atleast version 3.16.3).  
CMake can be downloaded from:  
https://cmake.org/download/  

#### Windows users
When using Windows and planning to use Visual Studio as your envrionment you can simply open the folder in  
Visual Studio and it will make sure everything will be ready to go. If this does not work for you,  
make sure you have the "C++ CMake tools for Windows" installed in your visual studio version.

#### Linux users
When using Linux you then have to configure the repository with the following command:  
``` cmake -DCMAKE_BUILD_TYPE={build configuration} -S . -B build ```  
Where "{build configuration}" should be replaced by one of the following:
- Debug
- RelWithDebInfo
- MinSizeRel

After the project has been configured you can build the project by running make while in your build directory:  
``` cd build; make ```

# 📽️ Already created projects in ByteCat
Despite the fact that the engine is not that big yet, a few fairly small projects have already  
been built to test the capabilities of the engine.

### Volumetric Raymarcher
https://user-images.githubusercontent.com/57482120/171645189-80581372-28f5-443b-88b9-b728cf9a35f1.mp4

### Android demo
https://user-images.githubusercontent.com/57482120/219850375-4d847886-6cfd-4a20-afae-f7a11e4b0c2c.mp4

