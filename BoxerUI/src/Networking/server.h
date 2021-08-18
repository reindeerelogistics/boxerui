//Protocol
struct MsgHeader {
    int type;
    Header* next;
};

struct MsgImg {
    struct Header Head;
    cv::Mat frame;
};

struct MsgCon {
    struct Header Head;
    std::vector<uint8_t> coms;
};

struct MutateDest {
    uint8_t nameToMutate[20];
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
    //The address after this is the payload
};
//Protocol

//Turn into Linked lists
struct Node {
    uint8_t name[20];
    uint8_t uid;
    int temperature;

    struct sockaddr_in Address;
    socklen_t len;

    int dict_index;
    struct Destinations* DestinationDictionary; //Become linked list
};

struct Destinations {
    uint8_t op;
    struct Node** value;
};
//Turn into Linked lsist

//Rewrite Tomorrow
void addNode(uint8_t* name, struct sockaddr_in address, socklen_t len);

struct Node** searchDict(struct Node* Client, uint8_t op);

void addToDests(struct Node* Client, struct Node* ClientToAdd, uint8_t op);

void addToDict(struct Node* Client, uint8_t op);

struct Node* searchNodes(uint8_t uid);

struct Node* searchNodes(uint8_t* name);

struct Node* authenticateNode(char uid, sockaddr_in Address);
//Rewrite Tomorrow

//Rewrite Today
void initialConnect(struct Join Client, sockaddr_in Address, socklen_t len);

void sendToDestinations(uint8_t* msg, struct Node** Destinations);

void passData(struct Header Head, sockaddr_in Address);

void mutateDestination(struct MutateDest Dests, struct sockaddr_in Client);

void chooseDirection(uint8_t* msg, sockaddr_in Address, socklen_t len);

void serverThread();

void waitMessage(/*Thread*/); //Replace with serverThread
//Rewrite Today
