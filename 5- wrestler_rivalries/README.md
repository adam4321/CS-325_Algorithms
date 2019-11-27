Author:       Adam Wright\
Date:         11/4/2019 \
Description:  Implementation of a program in c++ which takes in a text file from the command line and returns whether wrestling matches are possible, and if so, which pairings.

-The build directory contains a Linux build of the program

-To compile the program on Linux, just unzip the folder and then type "make" into the command line from within the directory. The makefile will compile the program into an  executable.

-To run the program, just type the name into the commannd line with the name of the file to test after it as a command line argument. 

The program is: wrestler

Example program call: wrestler wrestler1.txt


The test case files are:

wrestler1.txt => Impossible
wrestler2.txt => Yes Possible, Babyfaces: Bear Maxx Duke, Heels: Killer Knight Samson
wrestler3.txt => Yes possible, Babyfaces :  A   B   C   D   E, Heels :  V   W   X   Y   Z
wrestler4.txt => Yes Possible, Babyfaces: Alice Danny, Heels: Bob Chris
wrestler4.txt => Yes Possible, Babyfaces: Ace Jax Stone, Heels: Biggs Duke