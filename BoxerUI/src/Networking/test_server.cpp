#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "node.cpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    struct Node node;

    //Setting personnel information
    unsigned char name[16] = "Robot";
    char ip[30] = "0.0.0.0";
    int port = 8005;
    int transport = socket(AF_INET, SOCK_DGRAM, 0);

    node.setPersonnelAddress(name, port, ip, transport);

    node.listen();

}
