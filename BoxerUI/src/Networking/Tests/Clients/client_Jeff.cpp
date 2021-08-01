
#include <vector>
#include <string.h>
#include <iostream>
#include <cstdlib>

#include "../../../RoboCMD/RoboCMD.cpp"

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

    uint8_t array[20] = "Jeff";
    copyName(UI.name, array, 0);

    setServerAddress("0.0.0.0", 8000);
    joinServer();
    
    RoboCMD <float, float, float, float> cmd;
    cmd.setMsg(recvFromClient());
    cmd.disMsg();


}


