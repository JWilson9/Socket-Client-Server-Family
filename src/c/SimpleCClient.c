/* **********************************************************************
	James wilson 
	DT211/3
	Network Programming
	Simple C Client
	28/2/2015

********************************************************************** */


#include <stdio.h> // contains number of data types used in syste calls
#include <sys/types.h>// contains defintiions of a number of data types used in system calls
#include <sys/socket.h>// structures needed for sockets
#include <netinet/in.h>// contains constants & structures needed for internet domain
#include <netdb.h> 

#include <stdlib.h> // standard library for functions for memory allocation
#include <string.h> // library for string function
#include <unistd.h>
#include <fcntl.h>

#define BUF 256
	
/************************************************************************/
/* Error function that exits 0 when executed */
void error(char *msg)
{
    perror(msg); // the error message printed in command line
    exit(0);     // exit the program with exit code 0
}  //end functin


/************************************************************************/

// the main program function
int main(int argc, char *argv[])
{
    // declare the socket id, the port and the number of bytes 
    // being read or written 
    int sockfd, portno, n;

    // the struct to store the server address
    struct sockaddr_in serv_addr;
	
    // the struct to point to the server 
    struct hostent *server;

    //declare a buffer th write and recieve char's
    char buffer[BUF];
    
     
    
    //check to see if approiate no. of args were passed through
    // if we get too few arguments, then print a usage message
    if (argc < 3) { 
		printf("%s", argv[2]);
		
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       // program exits with code 0
       exit(0);
    }
    
   // 2nd input from command line (to an integer)
    // store it as the port number
    portno = atoi(argv[2]);
    
    
    
    // create a new socket of family AF-INET
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // if the socket creation was unsuccessfull then print error message
    if (sockfd < 0) 
        error("ERROR opening socket");
        
  
    //argv[1] contains the name of a host on the internet (localHost)
    // storing the results in the server struct (the first arg passed through)
    server = gethostbyname(argv[1]);
    
    // if that lookup failed
    //then print an error message
    if (server == NULL) {
        fprintf(stderr,"ERROR, host entered is invalid\n");
        // and exit with code 0
        exit(0);
    }
    
    
    // write zeros (sizeof(serv_addr)) to the serv_addr structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    //The address family of the socket is equal to AF_INET for the IP
    serv_addr.sin_family = AF_INET;
    
    // copy the characters,the of length server.h_length from the source address
    // server.sin_addr.s_addr to destination server h_addr 
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    
    //convert port number (portno) to the htons (Host Byte Order)
    //let it equal to the sin_port of the server address structure
    serv_addr.sin_port = htons(portno);
    
    //if attempt to connect to the socket is equal or less than 0
    //the the connection failed
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        // print the error message
        error("ERROR connecting");
    
    // ask the user to insert a message from command line
    printf("Please enter the message: ");
    
    // reset the buffer (all zeros)
    bzero(buffer,BUF);
    
    // read a string length up to 255 characters from the console (stdin)
    // store it in the buffer
    fgets(buffer,255,stdin);

    //use write function to write the contents of the buffer 
    //to the socket (sockfd) and take in the number of bytes read in variable n
    n = write(sockfd,buffer,strlen(buffer));
    
    // if that write attempt failed, i.e. nothing in n
    if (n < 0) 
    	// then print an error message
         error("ERROR writing to socket");
         
    bzero(buffer,BUF);
    
    // read data from the socket (sockfd) into the buffer up to 255 chars
    // and store the number read in n
    n = read(sockfd,buffer,255);

	// if that read attempt failed, i.e. nothing in n to read
	if (n < 0) 
	 // then print an error message
         error("ERROR reading from socket");
         
    //print to console the contents of the buffer as a string
    printf("%s\n",buffer);
    
    close(sockfd);
    // exit the program with code 0
    return 0;
} // end main method
