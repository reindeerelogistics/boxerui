#include "server.h"

struct Node* first = NULL;
struct Node* last = NULL;

int stringCompare(uint8_t* str1, uint8_t* str2) {
    int i = 0;
    while(true) {
        if(str1[i] != str2[i]) {
            return 0;
        }
        else if(str1[i] == '\0' || str1[i] == NULL) {
            return 1;
        }
        else{
            i += 1;
        }
    }
}

struct Node* searchNodes(struct Node* node, uint8_t* name) {
    if(stringCompare(node->name, name) == 1) {
        return node;
    } else if(node->next == NULL) {
        return 0;
    } else {
        return searchNodes(node->next, name);
    }
}

struct Node* printAllNodes(struct Node* node) {
    if(node == last) {
        printf("Name: %s\nEnd Of Nodes\n", node->name);
        return last;
    } else if(node->next != NULL && node != last) {
        printf("Name: %s\n", node->name);
        return printAllNodes(node->next);
    } else {
        perror("Break in Linked node list");
        return 0;
    }
}

void copyName(uint8_t* name, uint8_t* nameToCopy, int index) {
    int i = 0;
    while(i < 20) {
        if(nameToCopy[i] == '\0')
            break;

        name[index] = nameToCopy[i];
        i += 1;
        index += 1;
    }
}

uint8_t uidCounter;
uint8_t genUID() {
    return (uidCounter += 1);
}

struct KeyValue* findKeyPair(struct KeyValue* dests, uint8_t op) {
    if(dests->op == op) {
        printf("found KeyPair with OP: %d\n", dests->op);
        return dests;
    }
    else if(dests->next == NULL) {
        printf("None of this op\n");
        dests->next = (struct KeyValue*)malloc(sizeof(dests));
        dests->next->op = op;
        printf("No KeyPair associated with OP: %d, Created KeyPair\n", op);
        return dests->next;
    }
    else {
        return findKeyPair(dests->next, op);
    }
}

std::vector<uint8_t> nextName(uint8_t* names) {
    int i = 0;
    std::vector<uint8_t> name;

    while(names[i] != ' ' && names[i] != '\0') {
        name.push_back(names[i]);
        i += 1;
    }

    //MUTATION
    names += (i + 2);
    //END OF MUTATION

    return name;
}

struct NodePtr* lastNodePtr(struct NodePtr* value) {
    printf("Node to start searching from: %s\n", value->node->name);
    printf("started looking for last node\n");
    if(value->next == NULL) {
        printf("Found the last nodePtr which points to: %s\n", value->node->name);
        return value;
    } else {
        printf("did not find last nodePtr, recursing\n");
        return lastNodePtr(value->next);
    }
}

struct ListWrap searchDests(struct NodePtr* nodePtr, uint8_t* name, uint8_t* uid) {
    if(name[0] == '\0' && uid[0] != '\0') {
        //search for uid
    } else if(name[0] != '\0' && uid[0] == '\0') {
        struct NodePtr* temp = nodePtr;
        if(stringCompare(temp->node->name, name) == 1) {
                struct ListWrap wrapNodePtr;
                wrapNodePtr.prev = NULL;
                wrapNodePtr.current = temp;
                wrapNodePtr.next = temp->next;
                return wrapNodePtr;
        }
        while(true) {
            if(temp->next == NULL) {
                struct ListWrap wrapNodePtr;
                wrapNodePtr.current = NULL;
                printf("Failed to find node in dests");
                return wrapNodePtr;
            }
            else if(stringCompare(name, temp->next->node->name) == 1) {
                struct ListWrap wrapNodePtr;
                wrapNodePtr.prev = temp;
                wrapNodePtr.current = temp->next;
                wrapNodePtr.next = temp->next->next;
                return wrapNodePtr;
            }
            temp = temp->next;
        }
    }

}

//rewrite using SearchDests
int addToDests(struct KeyValue* pair, uint8_t* names, uint8_t* uids) {
    printf("Names still in list\n");
    std::vector<uint8_t> name = nextName(names);
    struct Node* newNode = searchNodes(first, &name[0]);
    struct NodePtr* ptr = (struct NodePtr*)malloc(sizeof(struct NodePtr));
    ptr->node = newNode;
    ptr->next = NULL;
    printf("Allocated a new nodePtr that points to: %s\n", ptr->node->name);

    if(pair->value == 0) {
        printf("The list of NodePtr's was NULL, initialised\n");
        pair->value = ptr;
    } else {
        struct NodePtr* lastDest = lastNodePtr(pair->value);
        lastDest->next = ptr;
    }

    if(*(names + name.size()) == '\0') {
        printf("Finished all names\n");
        if(uids[0] == '\0') {
            printf("FInished all uid\nReturning state\n");
            return 1;
        }
    }
    return addToDests(pair, names + name.size() + 1, uids);
}

bool checkIfNodeToRemove(struct KeyValue* pair, struct NodePtr* nodePtr, struct Node* nodeToRemove) {
    if(pair->value->node == nodeToRemove) {
        //deallocate nodePtr for node to remove
        pair->value = pair->value->next;
        return true;
    } else if(nodePtr->next->node == nodeToRemove) {
        //deallocate nodePtr->next
        if(nodePtr->next->next == NULL) {
            nodePtr->next = NULL;
            return true;
        } else{
            nodePtr->next = nodePtr->next->next;
            return true;
        }
    } else {
        return false;
    }
}

//rewrite using SearchDests
int removeFromDests(struct KeyValue* pair, struct NodePtr* nodePtr, uint8_t* names, uint8_t* uids) {
    std::vector<uint8_t> name = nextName(names);
    struct Node* nodeToRemove = searchNodes(first, &name[0]);

    if(checkIfNodeToRemove(pair, nodePtr, nodeToRemove) == true) {
        if(*(names + name.size()) == '\0') {
            printf("Finished all names\n");
            if(uids[0] == '\0') {
                printf("FInished all uid\nReturning state\n");
                return 1;
            }
        }
        return removeFromDests(pair, pair->value, names + name.size() + 1, uids);
    } 
    else if(nodePtr->next == NULL) {
        printf("Failed to find node %s in destination list", &name[0]);
        if(*(names + name.size()) == '\0') {
            printf("Finished all names\n");
            if(uids[0] == '\0') {
                printf("FInished all uid\nReturning state\n");
                return 1;
            }
        }
        return removeFromDests(pair, pair->value, names + name.size() + 1, uids);
    }
    else {
        return removeFromDests(pair, nodePtr->next, names, uids);
    }


}

int changeDict(struct Node* node, struct MutateDest dests) {
    //Find key-par
    struct KeyValue* keyValue = findKeyPair(node->DestinationDictionary, dests.op);

    if(dests.sign == '+') {
        addToDests(keyValue, dests.names, dests.uids);
        return 1;
    } else if(dests.sign == '-') {
        removeFromDests(keyValue, keyValue->value, dests.names, dests.uids);
        return 1;
    }
    return 0;
}

//Return uid
uint8_t addNode(struct Join Client, struct sockaddr_in Address, socklen_t len) {
    uint8_t uid = genUID();
    if(last == NULL) {
        last = (struct Node*)malloc(sizeof(struct Node));
        //CHeck for failed allocation

        last->next = NULL;
        last->uid = uid;
        last->temperature = 100;
        last->Address = Address;
        last->len = len;
        copyName(last->name, Client.name, 0);

        first = last;
    }
    else {
        last->next = (struct Node*)malloc(sizeof(struct Node));
        //CHeck for failed allocation

        last->next->next = NULL;
        last->next->uid = uid;
        last->next->temperature = 100;
        last->next->Address = Address;
        last->next->len = len;
        copyName(last->next->name, Client.name, 0);

        last = last->next;
    }

    return uid;
}


void testAddNode() {
    printf("[*]TEST: AddNode\n");
    struct sockaddr_in Addr;
    socklen_t len;

    struct Join Aaron;
    uint8_t name1[20] = "Aaron";
    copyName(Aaron.name, name1, 0);

    struct Join Roger;
    uint8_t name2[20] = "Roger";
    copyName(Roger.name, name2, 0);

    struct Join Mike;
    uint8_t name3[20] = "Mike";
    copyName(Mike.name, name3, 0);

    addNode(Aaron, Addr, len);
    addNode(Roger, Addr, len);
    addNode(Mike, Addr, len);

    last = printAllNodes(first);
    printf("[*]END TEST: AddNode\n\n");
}

void testFindKeyValue() {
    printf("[*]TEST: FindKeyValue\n");
    first->DestinationDictionary = (KeyValue*)malloc(sizeof(struct KeyValue));
    first->DestinationDictionary->op = 1;
    first->DestinationDictionary->value = 0;

    first->DestinationDictionary->next = (KeyValue*)malloc(sizeof(KeyValue*));
    first->DestinationDictionary->next->op = 2;
    first->DestinationDictionary->next->value = 0;

    first->DestinationDictionary->next->next = (KeyValue*)malloc(sizeof(struct KeyValue));
    first->DestinationDictionary->next->next->op = 3;
    first->DestinationDictionary->next->next->value = 0;

    uint8_t op = 3;
    KeyValue* dests = findKeyPair(first->DestinationDictionary, op);
    if(dests->op == op) {
        printf("[*]TEST: PASSED \n");
        printf("OP found is: %d\n", dests->op);
    } else {
        printf("[!]TEST: FAILED \n");
        printf("Did not find OP\n");
    }
    printf("Value of op1: %d\n", first->DestinationDictionary->value);
    printf("[*]END TEST: FindKeyValue\n\n");
}

void testSearchNodes() {
    printf("[*]TEST: SearchNodes\n");
    uint8_t name[20] = "Mike";
    struct Node* foundNode = searchNodes(first, name);
    if(stringCompare(name, foundNode->name) == 1) {
        printf("[*]TEST: PASSED \n");
        printf("Found node. Searched %s, found %s\n", name, foundNode->name);
    } else {
        printf("[!]TEST: FAILED \n");
        printf("Failed to find node with name %s\n", name);
    }
    printf("[*]END TEST: SearchNodes\n\n");
}
void testNextName() {
    printf("[*]TEST: NextName\n");

    uint8_t names[] = "Aaron Boby K Joe";
    uint8_t* namesPtr = names;
    std::vector<uint8_t> name;

    while(namesPtr[0] != '\0') {
        name = nextName(namesPtr);
        printf("Next name: %s\n", &name[0]);
        namesPtr += name.size() + 1;
        printf("vec size: %d\n", (int)name.size());
    }

    printf("[*]END TEST: NextName\n\n");
}

void testAddToDests() {
    printf("[*]TEST: AddToDests\n");
    uint8_t nodesToAdd[] = "Mike Roger";
    uint8_t nodesToChange[] = "Aaron";
    uint8_t uids[] = "";

    struct Node* node = searchNodes(first, nodesToChange);
    printf("Our nodes name %s\n", node->name);

    struct KeyValue* keyPair = findKeyPair(node->DestinationDictionary, 1);
    addToDests(keyPair, nodesToAdd, uids);
    printf("Node1: %s\n", node->DestinationDictionary->value->node->name);
    printf("Node2: %s\n", node->DestinationDictionary->value->next->node->name);
    printf("[*]END TEST: AddToDests\n\n");
}

void testSearchDict() {
    printf("[*]TEST: SearchDict\n");
    uint8_t name[] = "Aaron";
    uint8_t nameToFind[] = "Roger";
    uint8_t uids[] = "";

    struct Node* node = searchNodes(first, name);
    struct ListWrap nodePtrWrap = searchDests(node->DestinationDictionary->value, nameToFind, uids);
    printf("Node found: %s\n", ((struct NodePtr*)nodePtrWrap.current)->node->name);
    printf("[*]END TEST: SearchDict\n\n");
}

int main() {
    testAddNode();
    testFindKeyValue();
    testSearchNodes();
    testNextName();
    printf("First is %s\n", first->name);
    testAddToDests();
    testSearchDict();

}
