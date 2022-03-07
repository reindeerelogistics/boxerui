	#pragma once

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include "Source Files/socketLibrary.h"

#ifdef _WIN32
/* See http://stackoverflow.com/questions/12765743/getaddrinfo-on-win32 */
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  /* Windows XP. */
#endif
#include <winsock2.h>
#include <Ws2tcpip.h>
#else
/* Assume that any non-Windows platform uses POSIX-style sockets instead. */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#endif


int sockInit(void)
{
#ifdef _WIN32
	WSADATA wsa_data;
	return WSAStartup(MAKEWORD(1, 1), &wsa_data);
#else
	return 0;
#endif
}
int sockQuit(void)
{
#ifdef _WIN32
	return WSACleanup();
#else
	return 0;
#endif
}
int sockClose(SOCKET sock)
{

	int status = 0;

#ifdef _WIN32
	status = shutdown(sock, SD_BOTH);
	if (status == 0) { status = closesocket(sock); }
#else
	status = shutdown(sock, SHUT_RDWR);
	if (status == 0) { status = close(sock); }
#endif

	return status;

}

class BoxerUI_Sockets {
	char name = 'Z';



	//define for if platform is POSIX or Windows
#ifdef _WIN32
	SOCKET server_connect_socket = socket(AF_INET, SOCK_STREAM, 0);  //IP, protocal, blah
	//SOCKET server_connect_socket = connect_socket(1, 9000, "0.0.0.0");;  //IP, protocal, blah
#else
	int network_socket = socket(AF_INET, SOCK_STREAM, 0);
#endif // _WIN32

	//	void PayloadRecv() {
	//		sockInit();
	//
	//		//define for if platform is POSIX or Windows
	//#ifdef _WIN32
	//		SOCKET network_socket = socket(AF_INET, SOCK_STREAM, 0);  //IP, protocal, blah
	//#else
	//		int network_socket = socket(AF_INET, SOCK_STREAM, 0);
	//#endif // _WIN32
	//
	//
	//		//defining client socket
	//		//
	//		struct sockaddr_in server_address; //creatng struct
	//		server_address.sin_family = AF_INET; //type of address
	//		server_address.sin_port = htons(9005); //port
	//		server_address.sin_addr.s_addr = inet_addr("192.168.2.10"); //The servers address, port forwording required most likley
	//
	//		//Attempt to connect to server, error handling will be done 
	//		//shortly
	//		//
	//		int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address)); //Requests to connect to the server
	//		if (connection_status == -1) //if connection fail print
	//			printf("Error during connect");
	//
	//		//Constantly receive data from the server and print
	//		//error handlin will be done later here
	//		//
	//		char server_response[20]; //The max szie the server will send in a string
	//		while (1) {
	//			recv(network_socket, server_response, sizeof(server_response), 0); //Recieve the message sent from server and store it in server_response
	//
	//			//TODO 
	//			printf("%s\n", server_response); //Printig to screan
	//		}
	//
	//		sockClose(network_socket); //closing session
	//
	//	}

public:
	void payloadRecv(int inputData, char inputName, int mission) {
		switch (mission) {
		case 1:
			reqBoxerList();
		case 2:
			sub_Topic();
		default:
			//do a full connection by:
			//1. requesting a list of robots
			//2. determine if the robot has an established topic on server
			//3. send request to server to subscribe to topic
			clientSockInit(inputData, inputName);
		}
	}
	void clientSockInit(int inputData, char inputName) {
		//mission0. Ask robot for data
		//if (mission == 0) {

		sockInit();


		int initialTask = 3;
		//int* temp = &initialTask;
		send(this->server_connect_socket, (char *) initialTask, sizeof(initialTask), 0);
		send(this->server_connect_socket, &name, sizeof(name), 0);



		/*printf("Enter the robot name you wish to request data from\n> ");
		scanf(" %c", &inputName);

		printf("Enter the type of data you want\nThe only option is default (1)\n> ");
		scanf(" %d", &inputData);*/

		send(server_connect_socket, (char*)inputData, sizeof(inputData), 0);
		send(server_connect_socket, &inputName, sizeof(inputName), 0);
		sockClose(server_connect_socket);

		//after asking server what robots exists
		//subscribe to that topic
		reqBoxerList();
		sub_Topic();

		exit(0);

	}
	void reqBoxerList() {
		//mission1. Ask server what robots exist
		//if (mission == 1) {
		int initialTask = 2;
		send(this->server_connect_socket, (char*) initialTask, sizeof(initialTask), 0);
		send(this->server_connect_socket, &name, sizeof(name), 0);
		printf("sent task %d\n", initialTask);

		char names[100];
		int ports[100];
		printf("Waiting to recieve messages\n");
		recv(server_connect_socket, (char*) ports, sizeof(ports), 0);
		recv(server_connect_socket, (char*) names, sizeof(names), 0);
		sockClose(server_connect_socket);
		printf("names   address\n");
		int i = 0;
		while (i < 100) {
			if ((ports[i] > 9000) || (ports[i] < 8000))
				break;
			printf("%c   %d\n", names[i], ports[i]);
			i += 1;
		}
		//exit(0);
		//}
	}
	void sub_Topic() {
		//if (mission == 2) {
		int initialTask = 4;
		send(server_connect_socket, (char*) initialTask, sizeof((char*) initialTask), 0);
		send(server_connect_socket, &name, sizeof(name), 0);

		char robotName;

		printf("Enter the topics name you wish to subscribe to\n> ");
		//scanf(" %c", &robotName);

		send(server_connect_socket, &robotName, sizeof(robotName), 0);

		int fakeD;
		while (1) {
			recv(server_connect_socket, (char*)fakeD, sizeof(fakeD), 0);
			printf("%d\n", fakeD);
		}
		exit(0);
		//}
	}


	//}
};