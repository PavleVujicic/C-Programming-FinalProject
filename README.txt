#Author:

Pavle Vujicic
student number: 101159343
Course name: COMP 2401A

#Purpose:
program will simulate the escape by our heroes through Dragon’s Hollow, as the wizard’s flying monkeys
and attack birds try to stop them. The program will be implemented as multi-process, with two separate
instances of the same program. One process computes all participant moves and displays them on the screen in one terminal window, and the other process allows a spectator to view the identical escape output, at the same time, in a different window. Code will use well-designed modular functions, as well as inter-process communications (IPC) over stream sockets, to implement this simulation.


#List of sources:
course notes:
section 1.2
section 2.1
section 2.2
section 2.3
section 3.1
section 3.2
section 3.3
section 3.4
section 5.1
section 5.2
section 5.3
section 5.4
section 7.1
section 7.2
section 7.3

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




