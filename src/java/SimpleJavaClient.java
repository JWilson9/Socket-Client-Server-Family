package ie.dit.student.wilson.james;

/********************************
 * 	James Wilson
 * 	DT211/3
 *  Network Programming
 * 	SimpleJavaClient
 *  05/03/2015
 *********************************/

import java.net.*;
import java.io.*;

public class SimpleJavaClient {
	public static void main(String[] args) {

		// initialize variables that will be used in try & catch
		PrintWriter out = null;
		String clientInput = new String();
		Socket client = new Socket();

		// if the number of args passed through was not 2 then return error
		if (args.length != 2) {
			System.out.println("invalid number of arguments");
			System.exit(0);
		}
		// the name of the server input via command line & port number
		String serverName = args[0];
		int port = 0;

		// test to see if the port is correct (like the server)
		try {
			port = Integer.parseInt(args[1]);
		} // end try
		catch (NumberFormatException e) {
			System.out.println("ERROR incorrect port");
		}// end catch

		// prints off the server name and the port on which it is connecting to
		System.out.println("Connecting to " + serverName + " on port " + port);

		try {
			// the server name and the port number are passed though the socket
			client = new Socket(serverName, port);
		} catch (IOException e) {
			// printing off the appropiate error message to console
			System.out.println("creating socket failed");
			System.exit(0);
		}

		// print off the socket address of the client
		System.out.println("Just connected to "
				+ client.getRemoteSocketAddress());
		
		
		try {
			// printwriter gets the output strem from the socket
			out = new PrintWriter(client.getOutputStream(), true);
		}

		catch (IOException e) {
			System.out.println("creating output stream was unsuccessfull");
			System.exit(2);
		}

		try {
			// declare a buffer reader for reading the user's input from the
			// system
			BufferedReader in = new BufferedReader(new InputStreamReader(
					System.in));
			// the client's input is read
			clientInput = in.readLine();
		}// end try
		catch (IOException e) {
			// printing off the error message
			System.out.println("ERROR! could not read message from client");
			System.exit(3);
		}// end catch

		// prints out the client input
		out.println("the clients message\n" + clientInput);
		// close the client's socket connection
		
		try {
			client.close();
		} catch (IOException e) {
			// print off the error message
			System.out.println("error closing connection");
			System.exit(4);
		}// end catch
	}// method main
}// end class SimpleJavaClient

