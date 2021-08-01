#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif

struct initialize {
    struct sockaddr_in sockets;
    int network_socket;
};

//creates the socket, the socket() function is not propper as it 
//should follow the function inputs
struct initialize socket_initialise(int ipType, int port, const char * ip) {
    struct initialize setup;
    //struct sockaddr_in server_address = setup.sockets;
    setup.network_socket = socket(AF_INET, SOCK_STREAM, 0); //ip protocal blah

    if(ipType == 1) {
        setup.sockets.sin_family = AF_INET; //set ipv4
    } else {
        setup.sockets.sin_family = AF_INET; //set ipv6
    }

    setup.sockets.sin_port = htons(port); //set port to alocate or target
    setup.sockets.sin_addr.s_addr = inet_addr(ip); // inet_addr was form before

    return setup;
}


//allows other processes to talk with master to ask for data to be 
//sent to them. They will have to recieve the data after after

int listen_socket(int a, int b, const char * c) {
    struct initialize setup = socket_initialise(a, b, c); //iptype port address
    int network_socket = setup.network_socket;
    struct sockaddr_in server_address = setup.sockets;

    bind(network_socket, (struct sockaddr*) &server_address, sizeof(server_address)); //reserves port for server on machine

    listen(network_socket, 10); //listen for clients to connect

    return network_socket;
}

int connect_socket(int a, int b, const char * c) {
    struct initialize setup = socket_initialise(a, b, c); //iptype port address
    int network_socket = setup.network_socket;
    struct sockaddr_in server_address = setup.sockets;

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address)); //Requests to connect to the server
    if (connection_status == -1) //if connection fail print
        printf("Error during connect");

    return network_socket;
}

//exaple 0, depricated!!!
/*
   int main() {
   struct initialize setup = socket_initialise(1, 9001, "0.0.0.0"); //iptype port address
   int network_socket = setup.network_socket;
   struct sockaddr_in server_address = setup.sockets;

   bind(network_socket, (struct sockaddr*) &server_address, sizeof(server_address)); //reserves port for server on machine
   listen(network_socket, 5); //listen for clients to connect
   int client_socket = accept(network_socket, NULL, NULL); //block communications unless a connection is requested

   char value[20] = "Hello World";
   send(network_socket, &value, sizeof(value), 0); //sending the string value to the client

   close(network_socket); //closing connection
   return 0;
   }
   */

//example 2: connect to machine, then send data
/*
   int main() {
   int network_socket_1 = connect_socket(1, 8999, "0.0.0.0");

   int value = 5;
   send(network_socket_1, &value, sizeof(value), 0); //sending the string value to the client

   close(network_socket_1); //closing connection
   return 0;
   }
   */

//example 3: listen for machine to connect, then recieve a message
/*
   int main() {
   int network_socket_2 = listen_socket(1, 8999, "0.0.0.0");

   char server_response[20];
   recv(network_socket_2, &server_response, sizeof(server_response), 0); //Recieve the message sent from server and store it in server_response

   close(network_socket_2); //closing connection
   return 0;
   }
*/
