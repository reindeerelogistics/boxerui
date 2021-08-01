#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include "frame_computation.cpp"

#include <opencv2/highgui/highgui.hpp>

int status;

//Mat -> string
std::string serealizeFrame(cv::Mat new_frame, std::vector<unsigned char> compressed_frame) {
    std::vector<unsigned char> vec;
    if(compressed_frame.size() != 0){
        std::cout<<"Seriliased jpg/png encoding\n";
        vec = compressed_frame;
    } else {
        std::vector<unsigned char> frameVec(new_frame.begin<unsigned char>(), new_frame.end<unsigned char>());
        vec = frameVec;
    }

    std::stringstream ss;
    {
        cereal::BinaryOutputArchive archive(ss);
        archive(CEREAL_NVP(vec));
    }

    return ss.str();

}

//i32 i32 -> u1
struct sockaddr_in sendFrameOverhead(int rows, int cols, struct sockaddr_in serveraddr, struct sockaddr_in clientaddr, int sockfd) {
    socklen_t clientaddrLength, serveraddrLength;

    bool activity = false;
    while(activity == false)
        status = recvfrom(sockfd, &activity, sizeof(bool), 0, (struct sockaddr*)&clientaddr, &clientaddrLength);
    if(status < 0)
        perror("recv error");

    std::cout<<activity<<'\n';

    status = sendto(sockfd, &rows, sizeof(int), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0)
        perror("semd error");
    status = sendto(sockfd, &cols, sizeof(int), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0)
        perror("send error");

    std::cout<<"Sent row col stp: "<<rows<<" "<<cols<<'\n';

    return clientaddr;
}


struct FrameStructure {
    int rows = 0;
    int cols = 0;
};

struct FrameStructure recvFrameOverhead(int sockfd, struct sockaddr_in serveraddr) {
    socklen_t clientaddrLength, serveraddrLength;
    struct FrameStructure Overhead;

    bool activity = true;
    status = sendto(sockfd, &activity, sizeof(bool), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if(status < 0)
        perror("send failed");
    std::cout<<"sent activity\n";

    recvfrom(sockfd, &Overhead.rows, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);
    recvfrom(sockfd, &Overhead.cols, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);

    std::cout<<"\nReceived rows cols: "<<Overhead.rows<<" "<<Overhead.cols<<'\n';
    std::cout<<"size of frame "<<Overhead.rows * Overhead.cols<<'\n';

    return Overhead;
}

void sendFrame(cv::Mat new_frame, struct sockaddr_in serveraddr, struct sockaddr_in clientaddr, int sockfd) {
    socklen_t clientaddrLength, serveraddrLength;

    std::vector<unsigned char> encode_vec = encodeFrame(new_frame, 0);
    std::string str = serealizeFrame(new_frame, encode_vec);

    int size = str.length();

    const char* cstr = str.c_str();

    std::cout<<"size of frame is "<<size<<'\n';
    status = sendto(sockfd, &size, sizeof(int), 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0) {
        perror("Perameter <size> failed to send..");
        exit(0);
    }

    std::cout<<"Size of frame "<<size<<'\n';
    status = sendto(sockfd, cstr, size, 0, (struct sockaddr*)&clientaddr, sizeof(clientaddr));
    if(status < 0) {
        perror("Perameter <cstr> failed to send..");
        exit(0);
    }
}

cv::Mat recvFrame(int sockfd, struct sockaddr_in serveraddr) {
    socklen_t clientaddrLength, serveraddrLength;
    int size;

    std::cout<<"Starting to recieve\n";
    status = recvfrom(sockfd, &size, sizeof(int), 0, (struct sockaddr*)&serveraddr, &serveraddrLength);
    if(status < 0)
        perror("recv error");

    char cstr[size];
    std::cout<<"Size of frame "<<size<<'\n';
    status = recvfrom(sockfd, cstr, size, MSG_WAITALL, (struct sockaddr*)&serveraddr, &serveraddrLength);
    if(status < 0)
        perror("recv error");
    std::cout<<"recieved data\n";


    std::vector<unsigned char> vec = deserializeFrame(cstr, size);

    return decodeFrame(vec);
}

