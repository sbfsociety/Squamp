# Squamp
A platformer game made in C++ and SFML. More info in the README.md.

Requirements for build:
  gcc version 15.2.0


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


If you ecounter bugs, please reach out at:
