/*This is my Server C program*/

#include <stdio.h> //needed for printf()
#include <sys/socket.h> //needed for socket & communication
#include <unistd.h> //needed for fork() and getpid()
#include <stdlib.h> //needed for define exit
#include <netinet/in.h>  //needed initialize a variable of struct in6_addr
#include <string.h> //needed for declares string
#include <arpa/inet.h> //inet_addr

//HTML LINE
char hello[]="HTTP/1.1 200 OK\r\n Content-Type: text/html: charset=UTF=8\r\n\r\n<!DOCTYPE html>\r\n<html><head><title>ITT440 INDIVIDUAL ASSIGNMENT</title>\r\n<style>body {background-color: #F4D03F }</style></head>\r\n<body><center><h1>HELLO, MY NAME IS MAHIRAH</h1><p>I AM FROM CS2554A</p><br>\r\n<img src=https:miuc.org/wp-content/uploads/2020/08/6-Reasons-why-you-should-learn-Programming-737x366.png></center></body></html>\r\n";

#define PORT 8080 //port for HTTP
int main(int argc, char const *argv[])
{
    //Create a socket file here & Declare a variable
    struct sockaddr_in address;
    int fd_server, fd_client;
    long valread;
    int addrlen = sizeof(address);

    fd_server  = socket(AF_INET, SOCK_STREAM, 0); //calling the function
    if (fd_server < 0)
    {
        perror("Socket");//if something error will display "socket"
        exit(1);
    }

    //Initialize a server address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.56.119");
    address.sin_port = htons( 8080 );

   //Set up the socket properties
    memset(address.sin_zero, '\0', sizeof address.sin_zero);

   //Create a bind
    if (bind(fd_server, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("Bind");//If something error will display "Bind"
        exit(1);
  }
  //Create a listen
    if (listen(fd_server, 10) < 0)
    {
        perror("Listen");//If something error will display "Listen"
        exit(1);
    }

    //While loop
    while(1)//The action start
    {
        printf("\n\n%%%%%%Waiting for new connection%%%%%%\n\n");//This message display for waiting the connection
        if ((fd_client = accept(fd_server, (struct sockaddr *)&address, (socklen_t*)&addrlen)) ==  -1)
        {
            perror("Accept");
            exit(1);
        }

        //Child process
        char buffer[30000] = {0};
        valread = read( fd_client , buffer, 30000);
        printf("%s\n",buffer );
        write(fd_client , hello , strlen(hello));
        printf("\n\n::::::::::Hello message sent::::::::::\n\n");//This message will display if the code is successful
        close(fd_client);//Parent process
    }
    return 0;
}

