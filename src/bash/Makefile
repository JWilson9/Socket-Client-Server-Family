#############################################
#	James Wilson                        #
#	DT211/3 Lab Group B                 #
#	C12527253                           #
#	Network Programming/ Assignment 2   #
#	Lecturer - Mark Deegan              #
#	BUILD FILE for java & c programs    #
#	Port number 4444 (port that is free)#
#   05/03/2015 
#	
#
#                    #
#############################################

#The target build files
all: SimpleServer.o SimpleCClient.o SimpleJavaServer.class SimpleJavaClient.class
#Compile simple server c server & c client
SimpleServer.o: ../c/SimpleServer.c
	gcc -o ../../bin/SimpleServer.o ../c/SimpleServer.c 

SimpleCClient.o: ../c/SimpleCClient.c
	gcc -o ../../bin/SimpleCClient.o ../c/SimpleCClient.c

#compile simple java server & client
SimpleJavaServer.class: ../java/SimpleJavaServer.java
	javac -d ../../bin/ ../java/SimpleJavaServer.java

SimpleJavaClient.class: ../java/SimpleJavaClient.java
	javac -d ../../bin/ ../java/SimpleJavaClient.java


