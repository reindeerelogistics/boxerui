#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "uiBackend.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


int main() {
    struct sockaddr_in Address;
    socklen_t addr_len;
    Address.sin_family = AF_INET;
    Address.sin_port = htons(8000);
    Address.sin_addr.s_addr = inet_addr("0.0.0.0");
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    uint8_t array[20] = "Aaron";
    copyName(UI.name, array, 0);

    setServerAddress("0.0.0.0", 8000);
    joinServer();

    uint8_t name[] = "Aaron";
    uint8_t sign = '+';
    uint8_t op = '1';
    uint8_t dests[] = "Ricky Jeff";
    mutateDestinations(name, '+', '1', dests);

    uint8_t data[] = "This is a test for the programs input";
    sendToClients(data, sizeof(data), '1');

}

