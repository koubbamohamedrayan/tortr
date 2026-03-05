Tortr

Tortr is a simple cross-distro package wrapper for Linux.

Build

Compile the program:

g++ tortr.cpp -o tortr

Install (global command)

Install it to /usr/local/bin so it can be used like a normal command:

sudo g++ tortr.cpp -o /usr/local/bin/tortr

Usage

Install a package

tortr -ins <package>

Search for a package

tortr -lf <package>

Update the system

tortr -pu

Example

tortr -ins firefox
tortr -lf discord
tortr -pu
