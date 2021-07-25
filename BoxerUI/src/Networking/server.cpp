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

#include "backend.cpp"

int node_index = 0;
char uid_index = 2;

int sockfd;

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

struct Node** searchDict(struct Node* Address, uint8_t op) {
    int counter = 0;
    while(counter < Address->dict_index) {
        if(Address->DestinationDictionary[counter].op == op)
            return Address->DestinationDictionary[counter].value;
        counter += 1;
    }
    return 0;
}

void addToDests(uint8_t op, struct Node* Address, struct Node* AddressToAdd, int index) {
    if(index == -1) {
        //loop throught and add on struct that has null values
        return;
        printf("John Cena");
    }
    struct Node** Destinations = searchDict(Address, op);
    Destinations[index] = AddressToAdd; //I think this "&AddressToAdd" is incorrect. I belive is address of local variable
}

void addToDict(struct Node* Address, uint8_t op) {
    struct Node** Destinations = (struct Node**)calloc(1, 10*sizeof(struct Node*));

    Address->DestinationDictionary[Address->dict_index].value = Destinations;
    Address->DestinationDictionary[Address->dict_index].op = op;

    Address->dict_index += 1;
}


void serverThread() {
    //epoll stuff

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
        if(Nodes[i].name = name)
            return &Nodes[i];
        i += 1;
    }
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
        sendToDestinations(msg + 2, searchDict(Self, msg[1]));
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

void printNamesInDests(struct Node* Address, uint8_t op) {
    struct Node** Destinations = searchDict(Address, op);
    int i = 0;

    printf("Names in %s's destination list of %d op\n", Address->name, op);
    while(true) {
        if(Destinations[i] == 0)
            break;
        printf("%s\n", Destinations[i]->name);
        i += 1;
    }
}
