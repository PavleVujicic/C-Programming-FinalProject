#Author:

Pavle Vujicic

#Purpose:
program will simulate the escape by heroes through Dragon’s Hollow, as the wizard’s flying monkeys and attack birds try to stop them. The program will be implemented as multi-process, with two separate instances of the same program. One process computes all participant moves and displays them on the screen in one terminal window, and the other process allows a spectator to view the identical escape output, at the same time, in a different window. Code will use well-designed modular functions, as well as inter-process communications (IPC) over stream sockets, to implement this simulation.

#list of source code files:

headers:
defs.h
connect.h
hero.h
flyer.h
escape.h
utils.h

source code:
connect.c
main.c
utils.c
escape.c
hero.c
flyer.c
hollow.c

Textfile:
Makefile


#Compilation and Launching instructions:

extract all files to a5 directory.
go into a5
- cd a5

To Compile:
make

To run:
./a5

open second instance:
To run client:
./a5 127.0.0.1




