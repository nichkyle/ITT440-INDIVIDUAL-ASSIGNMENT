/*This is my Client C program*/

#include<stdio.h> //needed for printf()
#include<sys/socket.h> //needed for socket & communication
#include<arpa/inet.h> //inet_addr
#include<string.h> //needed for declares string


int main(int argc , char *argv[])
{
	//Declare variable
	int socket_desc;
	struct sockaddr_in server;
	char *message , server_reply[2000];
	
	//Create a socket file here
	socket_desc = socket(AF_INET , SOCK_STREAM , 0); //calling the function
	if (socket_desc == -1)
	{
		printf("No socket creates!"); //if something error will display this
	}

        //Initialize a server address structure
	server.sin_addr.s_addr = inet_addr("192.168.56.119"); //Enter the ip address from Server
	server.sin_family = AF_INET;
	server.sin_port = htons( 22 );

	//To connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Error");
		return 1;
	}
	
	puts("-----Its has connected-----\n"); //Display if it succesfully connected

	//To send some data
	message = "connect";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("-----Opsss! Connection failed-----");
		return 1;
	}
	puts("-----Hello message send-----\n"); //Display if the message has been send
                    
	//Receive a reply from the server
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
		puts("recv failed");
	}
	puts("Reply received\n");
	puts(server_reply);

	return 0;
}
