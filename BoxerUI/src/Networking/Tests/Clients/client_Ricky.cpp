#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "../../node.cpp"

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

    uint8_t name[] = " 0 Ricky";
    name[0] = sizeof(name);
    sendto(sockfd, name, sizeof(name), 0, (struct sockaddr*)&Address, sizeof(Address));

    uint8_t uid;
    recvfrom(sockfd, &uid, sizeof(uint8_t), 0, (struct sockaddr*)&Address, &addr_len);
    printf("UID: %d\n", uid);

    uint8_t data;
    recvfrom(sockfd, &data, sizeof(uint8_t), 0, (struct sockaddr*)&Address, &addr_len);
    printf("Ricky recieved: %d\n", data);

}



