# Yet Another Voxel Game

## About
I started to get interested in C/C++ due to wanting to make a 3D game, and seeing all the great frameworks out there to do so.
Raylib gives a lot of control while being easier to use than OpenGL, has great documentation and bindings for other languages.<br>

While a voxel based game engine is nothing new, I thought it would be more fun than modding Minecraft to rebalance some parts
of the game that I didn't really like, or even playing older alpha/beta versions, with the benefit of learning C along the way.
( If I even get there that is )

## Goals for now
So far rendering voxels with textures works, along with backface culling to elliminate performance issues down the road.
Luckily, raylib has built-in camera and collision detection functions to make my life easier, but there's still a lot to do:

#### For the game
* Finish implementing texture loading and mapping it to blocks using enums
  * *A spritemap will be split and loaded into a matrix. The enum will store the indexes of the texture*
* Ability to place and break blocks
* Blocks update their culling when their immediate neighbor(s) change
* Culling between chunks
  * *Right now edge voxels don't have culling implemented when their neighbors include voxels from another chunk*

#### For the projet
* Implement a build system and cross platform compilation for Windows and Linux
  * *I chose Premake5 due to once again their great documentation and syntax. This should happen soonish...*
* Statically bind Raylib both for Windows and Linux so the program doesn't depend on shared libraries.
* Keep clutter to a minimum
  * *In the past I wouldn't really care about quality, since I mostly coded for school.*

These will change as the project moves on, but I don't want to plan too far ahead.

## How to use it?
So far this project is designed to be build on Linux systems, as only shared object libraries for Raylib are included,
but you could modify the Makefile to include the proper libraries on any system, or Visual Studio to set link paths.
Once I have Premake5 set up and working I will publish binaries for both platforms :)<br>

To build the project you need to navigate to the folder in your terminal and just type "make", a binary named "yavg"
should appear if the build is successful and can be run.
