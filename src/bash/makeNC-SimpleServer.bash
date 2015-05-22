#!/bin/bash

# Mark Deegan
# Sun 15 Feb 2015 13:50:57 GMT
# DT211-3
# Network Programming
# February 2015
# CA-2
#
# script to build NC-SimpleServer.c
# this script should be run from the src/bash directory of the project

# this calls the gcc compiler on the input file NC-SimpleServer.c and 
# generates the output file NC-SimpleServer.o
gcc -o ../../bin/NC-SimpleServer.o ../c/NC-SimpleServer.c
