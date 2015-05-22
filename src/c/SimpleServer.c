/********************************************
	James Wilson                        
	DT211/3 Lab Group B                
	C12527253                          
	Network Programming/ Assignment 2  
	Lecturer - Mark Deegan             
	Simple Server (with comments)
	TCP Port
	Port Number: Argument passed via user
	Reference: http://www.cs.rpi.edu/~moorthy/Courses/os98/Pgms/socket.html
 *********************************************/
#include <stdio.h> // contains number of data types used in syste calls
#include <stdlib.h>	// standard library for functions for memory allocation
#include <sys/types.h> // contains defintiions of a number of data types used in system calls
#include <sys/socket.h> // structures needed for sockets
#include <netinet/in.h> // contains constants & structures needed for internet domain
#include <strings.h>	// library for string function
#include <unistd.h>	
#include <locale.h>	

#define BUF 256
/*****************************ERROR*******************************************/
// declare error function
void error(char *msg)
{
    perror(msg); // the error message printed in command line
    exit(0);     // program with the exit 0
} //end error function

 void realWorldServer();// declare function realTimeServer before main
/*************************MAIN*********************************************/

// the main program function
int main(int argc, char *argv[])
{ 
	// declare variables to store incoming and outgoing socket identifiers and the 
	// port number
	int sockfd, newsockfd, portno, pid;
	// declare a variable to store the length of the client struct
	unsigned int clilen;
	// sockaddr_in contains the internet address, serv_addr contains the address of the server
	// cli_addr contains the address of the client
	struct sockaddr_in serv_addr, cli_addr;
	
	if (argc < 2) {	// if the num of args passed through the console
		// is lower than 2 then print error message
		//stating that there was no port provided
		fprintf(stderr,"ERROR, no port provided\n");
		//  exit with code 1
		exit(1);
     }
     
     // creating the socket connection
     // the socket is a stream socket, AF_INET is the domain of the socket
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     
     //if the socket is smaller than 0 then it prints an error message
     if (sockfd < 0) 
        error("ERROR opening socket");
     
     // the functioin bzero() sets all the values in the buffer to zero
     // it takes 2 arguments, the pointer to the buffer (&serv_adder)
     // & the 2nd argument is the size of the buffer
     bzero((char *) &serv_addr, sizeof(serv_addr));
     
     // convert command line arg (char to int), portno is now this value
     // it is the port number on which the server will listen for connections
     portno = atoi(argv[1]);
     
     // set the family of the serv-addr socket to AF-INET
     // the var serv_adder is the structure of type struct sockaderr_in
     serv_addr.sin_family = AF_INET;
     
     // set the address to any available IP address
     // the field of sockadder_in contains the IP adress of the host
     // for the server, this will always be the IP adress of the machine INADDR_ANY gets this address
    
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     
     // set the port number to listen on
     // serv_adder contains the port number
     // htons() converts a port number in host byte order to a 
     // port number in network byte order
     serv_addr.sin_port = htons(portno);
     
     // bind to the socket to listen for requests, the bind() system call binds a socket to an address
     // here it would be the address of the current host & the port number on which the server will run on
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
     	sizeof(serv_addr)) < 0) 
     	// printing message to user
     	error("ERROR on binding");
 
 	// use listin function to listen to socket create with the queue of a length of 5 waiting connections
 	// the first arg is the socket file descriptor, the second is the size of the backlog queue
 	listen(sockfd,5);
 	
 	// set clilen to be the size of the struct cli_addr  
 	clilen = sizeof(cli_addr);
 	
 	//infinite while loop
 	while(1){
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
		
		if (newsockfd < 0)// if the new socket is smaller than 0(negative) print error message
			error("ERROR on accept");// printing the error message
		//call fork to create a new process
		pid = fork();
	
		//if the 
		if (pid < 0){
			error("ERROR on fork");
		}
		if(pid == 0){
			//parent process closes the socket connection
			close(sockfd);
			//calls function realWorldServer with the socket value
			realWorldServer(newsockfd);
			//exits with code 0
			exit(0);
		}
		else{
			close(newsockfd);
		}
		
	}//end while loop
	// exit the program returning an exit code of 0
	return 0; 
} // end declaration of main method

/**************REALWORLDSERVER**************/
 
//
 void realWorldServer (int sock)
 {
		int n;//n contains the number of char's read or written
		char buffer[BUF];//server reads char's from the socket connection into this buffer
		
		bzero(buffer, BUF);//buffer initialized to zero using bzero function
		n = read(sock, buffer, 255);//read from desciptor returned by socket()
		if(n < 0){
			error("ERROR reading from the socket");
		}
		
		printf("Here is the message \n %s", buffer); //printing off the clients message
		
		// i am still debugging C Server timeouts - not fully functional yet
		struct timeval timeout;
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;
		
		if(setsockopt (sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
					sizeof(timeout)) < 0)
					error("setsockopt failed");
		
		n = write(sock, "I got your message", 18);//writes short message to client
		
		if( n < 0 ){
			error("ERROR wrting to socket");
		}
		
}
		
		
