# Squamp
A platformer game made in C++ and SFML. More info in the README.md.

This is just the base mechanics. The full game is on my other repo SquampWH (Squamp (W)ith (G)raphics). If you use this credit me for the physics and game mechanics.

Requirements for build:
  gcc version 15.2.0

NOTE: second.cpp is the main file, main.cpp isn't included in any header file.


For fellow devs:
  There is the eventualno-fix.txt file in the main branch. It's a fix for the Lines class, (it fixes the order of the positions of the begin and end of the line so the game would work, now it's smaller x, bigger x, bigger y, smaller y). It's there if you wanna make it work   for your project.

  Lines are added in the main() with a vector pushback.


if you don't care about the build you just need this folder structure:
  Squamp
  |- /cmake-build-debug
  |     |-/assets
  |     |-/Squamp.exe
  |-Graphics.hpp
  |-Audio.hpp
  |-System.hpp


If you ecounter bugs, please reach out at: devsbf0@gmail.com



VERSION PATCHES:
  2.0:
    -added limit to Player's jump velocity, set to -30.f
    -added a function Compensate() to add horizontal lines at the edges of vertical lines
    -added collision for hitting your head against a horizontal platform
  2.1:
    -upgraded Compenstate() to place vertical lines at the edges of horizontal lines
    -added a constructor overload with a boolean at the end for drawining it (so the lines on edges woudnt be drawn)
