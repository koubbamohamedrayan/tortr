tortr

tortr is a small program that installs packages on Linux systems.

It detects the system package manager and runs it automatically.
If the package is not found, it can try Flatpak or Snap.

Supported managers:

- pacman
- apt
- dnf
- zypper

Build

Compile with:

g++ tortr.cpp -o tortr

Install

./tortr setup

This installs tortr to "/usr/local/bin".

Usage

Install a package:

tortr install <package>

Search for a package:

tortr search <package>

Update system packages:

tortr update

Show help:

tortr help

License

GPL
