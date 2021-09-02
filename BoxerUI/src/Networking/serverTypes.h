#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "hashTableTypes.h"

namespace Server {
    struct Client {
        char name[20];
        char uid;
        int temperature;
        struct sockaddr_in Address;
        socklen_t len;

        Hash::Table<struct DestLists, char> DestTable;
    };

    struct DestLists {
        int op;
        Client* clientPtr;
    };

};
