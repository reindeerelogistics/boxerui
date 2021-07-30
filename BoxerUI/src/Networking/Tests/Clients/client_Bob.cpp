#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "../../node.cpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

void addSize(uint8_t* array, uint64_t size) {
    //right shift and put in indexes in array??
    //ask ramsey
}

int main() {
    struct sockaddr_in Address;
    socklen_t addr_len;
    Address.sin_family = AF_INET;
    Address.sin_port = htons(8000);
    Address.sin_addr.s_addr = inet_addr("0.0.0.0");
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    uint8_t name[] = "        0 Bob";
    addSize(name, (uint64_t)sizeof(name));

    sendto(sockfd, name, sizeof(name), 0, (struct sockaddr*)&Address, sizeof(Address));

    uint8_t uid;
    recvfrom(sockfd, &uid, sizeof(uint8_t), 0, (struct sockaddr*)&Address, &addr_len);
    printf("UID: %d\n", uid);

    u_int8_t mutation[] = " 3 + Bob:1 Ricky Jeff John \0\0\0";
    mutation[0] = sizeof(mutation);
    sendto(sockfd, mutation, sizeof(mutation), 0, (struct sockaddr*)&Address, sizeof(Address));

    uint8_t data[7] = {6, '2', ' ', uid, '1', 25, '\0'};
    sendto(sockfd, data, sizeof(data), 0, (struct sockaddr*)&Address, sizeof(Address));
    printf("Bob sent Data: %d\n", data[6]);

}

