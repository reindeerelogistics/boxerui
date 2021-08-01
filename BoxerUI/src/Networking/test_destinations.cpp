#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sys/epoll.h>
#include <thread>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "server.cpp"

int main() {
    struct sockaddr_in address;

    struct Identity Roger;
    Roger.Address = address;
    Roger.temperature = 5;

    struct Identity Bob;
    Bob.Address = address;
    Bob.temperature = 10;

    struct Identity Ricky;
    Ricky.Address = address;
    Ricky.temperature = 15;

    Identities[0] = Roger;
    Identities[1] = Bob;
    Identities[2] = Ricky;


}
