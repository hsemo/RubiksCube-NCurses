# Description
A simple rubiks cube game where you can perform your algorithms.

# Dependencies
`libncurses` is required

# Build & Run
This simulator was built and tested on Ubuntu Linux (currently using Arch btw) so if you have Windows installed it's on you to run it.
To build & run use the following commands in your preffered terminal (I use `foot` btw):
```bash
git clone https://github.com/hsemo/rubiks-cube.git
cd rubiks-cube
g++ Rubiks.h Rubiks.cpp main.cpp -o main -lncurses
./main
```
