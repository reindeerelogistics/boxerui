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

//#include "frame_computation.cpp"
//Protocol
struct MsgHeader {
    int type;
    MsgHeader* next;
};

struct MsgImg {
    struct MsgHeader Head;
   // cv::Mat frame;
};

struct MsgCon {
    struct MsgHeader Head;
    std::vector<uint8_t> coms;
};

struct MutateDest {
    uint8_t nameToMutate[20];
    uint8_t sign;
    uint8_t op;

    uint8_t* names; //Names seperated by a space
    uint8_t* uids; //uids seperated by a space
};

struct Join {
    uint8_t name[20];
    uint8_t bio[20];
};

struct Leave {
    uint8_t uid;
    uint8_t name[20];
};

struct ServerMsg {
    uint64_t size;
    uint8_t instruction;
    uint8_t uid;

    uint8_t op;
    void* payload;
    //The address after this is the payload
};
//Protocol

//Turn into Linked lists
struct Node {
    struct Node* next;

    uint8_t name[20];
    uint8_t uid;
    int temperature;
    struct sockaddr_in Address;
    socklen_t len;

    struct KeyValue* DestinationDictionary; //Become linked list
};

struct NodePtr {
    struct NodePtr* next;
    struct Node* node;
};

struct KeyValue {
    struct KeyValue* next;

    uint8_t op;
    struct NodePtr* value;
};

struct ListWrap {
    void* prev;
    void* current;
    void* next;
};
