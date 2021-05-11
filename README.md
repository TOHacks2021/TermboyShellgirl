# Termboy and Shellgirl

## Installation
For now, the only option for installation is to build from source. Make sure you have the standard build tools (make, gcc) and also have the ncurses library. Once you are ready, simply run `sudo make install`.

## Configuration
A couple of options are available for you to tinker with in the `config.h` file, from simpler things like the controls, to modifying game constants. Just make sure to recompile after making changes. 

## Level syntax
```
Wall: # -> #
Player spawn: 1, 2 -> none
Player exit: 3, 4 -> none
Switches: / or \
Door: ------A, lowercase shorter doors
Pressure plate: = -> /=\
Lava: L -> ~
Water: W -> ~
Green mud: G -> ~
Block: @
Red Gems: <
Blue Gems: >
Red Doors: [
Blue Doors: ]
```

