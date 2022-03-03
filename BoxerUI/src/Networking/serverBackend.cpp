#include <inttypes.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/epoll.h>
#include <thread>

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "protocol.h"

//on Msg recive
struct Service {
    private:
        char name[20] = "\0";

        bool set_address;
        struct sockaddr_in server_address;
        socklen_t server_address_length;
        int sockfd;

        int Test;
        void testOutput(const char* value) {
            if(Test == 1)
                printf("[#]%s", value);
        }

        void testOutput(int value) {
            if(Test == 1)
                printf("%d\n", value);
        }

        struct epoll_event epollInit(int fd) {
            struct epoll_event event;
            event.events = EPOLLIN | EPOLLEXCLUSIVE;
            event.data.fd = fd;

            return event;
        }

        void gameLoop() {
            struct sockaddr_in Client;
            socklen_t len;

            struct epoll_event events[1];

            events[0] = epollInit(sockfd);
            int epfd = epoll_create1(0);
            epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events[0]);

            //in future compare and exchange with seperate threads 
            //recieving from linked list que

            Protocol::ServerMsg msg;

            while(true) {
                recvfrom(events[0].data.fd, &msg, sizeof(msg), MSG_PEEK | MSG_DONTWAIT, (struct sockaddr*)&Client, &len);
            uint8_t allBytes[msg.size];
            recvfrom(events[0].data.fd, allBytes, msg.size, MSG_WAITALL | MSG_DONTWAIT, NULL, NULL);

            char ip[30];
            char port[10];
            getnameinfo((struct sockaddr*)&Client, len, ip, sizeof(ip), port, sizeof(port), NI_NUMERICSERV);
            printf("Client address\nIp: %s\nPort: %s\n\n", ip, port);
            //payloadDetection(allBytes);
            }
        }

        void payloadDetection(uint8_t* allBytes) {
        }

        bool authenticate() {
            return false;
        };

        void serverInstruction() {
        };

        //server instructions
        void sendToDests() {
        };

        void sendToDest() {
        };

        void addClient() {
        };

        void addDestList() {
        };

        void addDest() {
        };

    public:
        void setAddress(struct sockaddr_in address) {
            if(set_address == true) {
                testOutput("Tried to set an already set address\n");
                return;
            }
            server_address = address;
            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address));

            set_address = true;
        }

        void setName(char* name_to_assign) {
            //copy name_to_assign to name
        }

        void kill() {
            testOutput("Requested to kill service\n");
            //atempt to shut down and unallocate things
            testOutput("Finished ShutDown task\n");
        }

        void start() {
            if(set_address == false || name[0] == '\0') {
                testOutput("Failed to start service as name or address has not been set\n");
                exit(1);
            }


        }


        //debug
        void printClientInfo() {};
};
