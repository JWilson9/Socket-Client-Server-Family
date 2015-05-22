/******************
James Wilson
DT211-3 
Assignment2 
Network Programing
http://www.tutorialspoint.com/java/java_networking.htm

*******************/



package ie.dit.student.wilson.james;

import java.net.*;
import java.io.*;

// declare public class SimpleJavaServer,
public class SimpleJavaServer extends Thread
{
	// Declare the serversocket for the connection
   private ServerSocket serverSocket;
   
   //method passes through the port number via command line
   public SimpleJavaServer(int port) throws IOException
   {
      serverSocket = new ServerSocket(port);
      
      
      serverSocket.setSoTimeout(10000);  
   }
	// declare main method
	public static void main(String [] args)
   {
	   
	   int port = 0; // init the port
	   //if the number of arguments is not 1 then print this error message
	   if(args.length != 1){
			System.out.println("invalid arguments passed");
	   }//end if
	   
	  try{
		// user input (string to an int) 
		port = Integer.parseInt(args[0]); 
        
	  }//end try
	  // catch if not a number format
	  catch(NumberFormatException e){
		  System.out.println("invalid port exiting program . . . ");
		  // exit the program 
		  System.exit(0);
	  }// end catch
	  
      try
      {
		  // create a thread on the port passed by the command line
         Thread t = new SimpleJavaServer(port);
         // start the thread
         t.start();
      }//end try
      catch(IOException e)
      {
		 // prints if there was an error with the port on the thread
         e.printStackTrace();
      }//end try & catch
   }//end main

	/** 
	 * function run to run which deals with the input & output streams
	 * once there is a connection established
	*/
   public void run()
   {
	  // run an infinite while loop
      while(true)
      {
		 // print message to console while connecting to client port
		 System.out.println("Waiting for client on port " +
            serverSocket.getLocalPort() + "...");
          // initialise the socket server
          Socket server = new Socket();
		  
         try
         {
            // listens for client, and checks if there is a connection established
            server = serverSocket.accept();
            
         }//end try
         // error if there is a problem with IO (input/ output)
         catch(IOException e)
         {
            System.out.println("ERROR!!  unable to establish a connection");
            // exit the program
            System.exit(0);
         }//end try & catch
         
         // print to console the Socket address it connected to
         System.out.println("Just connected to "
                  + server.getRemoteSocketAddress());
               
               

         try{
			 // retieve the input stream from client
			 BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
      
			 PrintWriter out= new PrintWriter(server.getOutputStream(), true);
			//declare a string builder for client messages
			 StringBuilder sb = new StringBuilder();
			 // string to store line by line
			 String str;
			 // while loop until no more lines to read
			 // str assigned to the value of the readline 
			 while ((str = in.readLine()) != null)
			 {
				 //appending the string to sb
				sb.append(str + "\n");
			 }
			 //sb.toString();
			 str = in.readLine();
			 //printing out the clients message
			
			 System.out.println(sb);
			 
			 
		}//end try
		catch(IOException e)
		{
			// prints if there was an error with the port on the thread
			e.printStackTrace();
		}//end try & catch
          
      }//end while true
   }//end run
   
   
   
}//end class SimpleCServer
