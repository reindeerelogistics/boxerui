//Sample protocol
//
//Sending data
//{Server instruction (byte)} {UID (byte)} {Operation Number (byte)} {Payload (dynamic)}
//
//Initial M=Signup
//{Server instruction (byte)} {Name (dynamic)}

//+(Bob 2){Ricky Tommy John}
//-(Bob 2){Ricky John}
//
//BBut = 0x02
//
//ButtonA : 0x01
//ButtonB : 0x02

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

//#include "node.cpp"

int node_index = 0;
char uid_index = 2;
int sockfd;

int thread_index = 0;
std::thread* threads = (std::thread*)calloc(1, 10*sizeof(std::thread));

struct epoll_event epollInit(int fd) {
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLEXCLUSIVE;
    event.data.fd = fd;

    return event;
}

struct Node {
    uint8_t* name;
    char uid;
    int temperature;

    struct sockaddr_in Address;

    int dict_index;
    struct Destinations* DestinationDictionary;
};

struct Destinations {
    uint8_t op;
    struct Node** value;
};

// global list of hosts for all
struct Node* Nodes = (struct Node*)calloc(1, 10*sizeof(struct Node));


void addNode(uint8_t* name, struct sockaddr_in address) {
    Nodes[node_index].name = name;
    Nodes[node_index].uid = uid_index;
    Nodes[node_index].Address = address;
    Nodes[node_index].temperature = 100;
    Nodes[node_index].dict_index = 0;

    struct Destinations* DestinationDictionary = (struct Destinations*)calloc(1, 10*sizeof(struct Destinations));
    Nodes[node_index].DestinationDictionary = DestinationDictionary;

    node_index += 1;
    uid_index += 1;
}

struct Node** searchDict(struct Node* Client, uint8_t op) {
    int counter = 0;
    while(counter < Client->dict_index) {
        if(Client->DestinationDictionary[counter].op == op)
            return Client->DestinationDictionary[counter].value;
        counter += 1;
    }
    return 0;
}

void addToDests(struct Node* Client, struct Node* ClientToAdd, uint8_t op) {
    struct Node** Destinations = searchDict(Client, op);
    int i = 0;

    while(true) {
        if(Destinations[i] == 0) {
            Destinations[i] = ClientToAdd;
            return;
            printf("John Cena");
        }
        i += 1;
    }
}

void addToDict(struct Node* Client, uint8_t op) {
    struct Node** Destinations = (struct Node**)calloc(1, 10*sizeof(struct Node*));

    Client->DestinationDictionary[Client->dict_index].value = Destinations;
    Client->DestinationDictionary[Client->dict_index].op = op;

    Client->dict_index += 1;
}

struct Node* searchNodes(uint8_t uid) {
    int i = 0;
    while(i < node_index) {
        if(Nodes[i].uid == 0) {
            return 0;
        }
        else if(Nodes[i].uid == 1) {
            continue;
        }
        else if(uid == Nodes[i].uid) {
            return &Nodes[i];
        }
        i += 1;
    }
    return 0;
}

struct Node* searchNodes(uint8_t* name) {
    int i = 0;
    while(i < node_index) {
        if(Nodes[i].name == name)
            return &Nodes[i];
        i += 1;
    }
    return 0;
    //fail
}

struct Node* authenticateNode(char uid, sockaddr_in Address) {
    struct Node* Self = searchNodes(uid);
    if(Self == 0) {
        perror("Client had wrong uid: REJECTED\n");
        return 0;
    } 
    if(Self->Address.sin_port != Address.sin_port) {
        perror("Client had wrong port: REJECTED\n");
        return 0;
    }
    if(Self->Address.sin_addr.s_addr != Address.sin_addr.s_addr) {
        perror("Client had wrong ip: REJECTED\n");
        return 0;
    }
    else {
        return Self;
    }
}

void initialConnect(uint8_t* msg, sockaddr_in Address) {
    if(searchNodes(msg) == 0) {
        //check if other stuff is in use
        char fail[1] = {'0'};
        sendto(sockfd, fail, sizeof(char), 0, (struct sockaddr*)&Address, sizeof(Address));
    }
    else {
        addNode(msg, Address);
        char* uid = &searchNodes(msg)->uid;
        sendto(sockfd, uid, sizeof(char), 0, (struct sockaddr*)&Address, sizeof(Address));
    }
}

void sendToDestinations(uint8_t* msg, struct Node** Destinations) {
    int i = 0;
    while(true) {
        if(Destinations[i]->uid == 0)
            break;
        sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&Destinations[i]->Address, sizeof(Destinations[i]->Address));
    }
}

void passData(uint8_t* msg, sockaddr_in Address) {
    struct Node* Self = authenticateNode(msg[0], Address);
    if(Self == 0) {
        //notify client he was not permitted
    } else {
        sendToDestinations(msg + 1, searchDict(Self, msg[1]));
    }
}

void chooseDirection(uint8_t* msg, sockaddr_in Address) {
    switch(msg[0]) {
        case 0:
            initialConnect(msg + 1, Address);
            break;
        case 1:
            //querry
            break;
        case 2:
            passData(msg + 1, Address);
            break;
    }
}


void serverThread() {
    //epoll stuff
    struct sockaddr_in Client;
    struct epoll_event events[1];

    events[0] = epollInit(sockfd);
    int epfd = epoll_create1(0);
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &events[0]);

    uint8_t data_size;
    uint8_t* data;

    while(true) {
        epoll_wait(epfd, events, 1, -1);
        recvfrom(events[0].data.fd, &data_size, sizeof(data_size), MSG_PEEK | MSG_DONTWAIT, (struct sockaddr*)&Client, NULL);
        recvfrom(events[0].data.fd, &data, data_size, MSG_DONTWAIT, (struct sockaddr*)&Client, NULL);

        chooseDirection(data + 1, Client);
    }

}

void spawnThread() {
    std::thread* thread = (std::thread*)calloc(1, sizeof(std::thread));
    thread(serverThread);
    threads[thread_index] = thread;
    thread_index += 1;
}

//internal use only
void printNamesInDests(struct Node* Client, uint8_t op) {
    struct Node** Destinations = searchDict(Client, op);
    int i = 0;

    printf("Names in %s's destination list of %d op\n", Client->name, op);
    while(true) {
        if(Destinations[i] == 0)
            break;
        printf("%s\n", Destinations[i]->name);
        i += 1;
    }
}
