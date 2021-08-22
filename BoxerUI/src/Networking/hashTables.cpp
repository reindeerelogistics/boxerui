#include <stdio.h>
#include <stdlib.h>
int Test = 1;

void testOutput(const char* value) {
    if(Test == 1)
    printf("[#]%s", value);
}

void testOutput(int value) {
    if(Test == 1)
        printf("%d\n", value);
}

int maxLength = 49;

const int ListSize = 50;
enum key_types{name, uid};
enum value_types{client, destLists};

struct Client {
    char name[20];
    char uid;
    int badgeNumber;
};

struct DestLists {
    int op;
    Client* clientPtr;

};

union Values {
    Client client;
    DestLists destLists;
};

struct Value {
    int type;
    Values value;
};

union Keys {
    char name[20];
    char uid;
};

struct Key {
    int type;
    Keys keys;

};

struct HashTable {

    private:
        int valueType = -1;
        void* List = 0;
        const int TableLength = maxLength;

    void allocateTable(int type) {
        if(List != 0) {
            testOutput("This table has already been allocated\n");
            exit(0);
        }
        switch(type) {
            case value_types(client):
                testOutput("Allocated table of clients\n");
                List = calloc(TableLength, sizeof(Client));
                break;
            case value_types(destLists):
                testOutput("Allocated table of destination lists\n");
                List = calloc(TableLength, sizeof(DestLists));
                break;
            default:
                testOutput("Triend to make hash table of type that does not exist\n");
                exit(0);
        }
    }

        void addClient(Client client, int index) {
            ((Client*)List)[index] = client;
            testOutput("Added client at index ");
            testOutput(index);
        }

        void addDestList(DestLists destList, int index) {
            ((DestLists*)List)[index] = destList;
        }

        int hashChar(char key) {
            return (key*100 + 100)%TableLength;
        }

        int hashString(char* string) {
            int value = 0;
            int i = 0;

            while(string[i] != '\0') {
                value += (int)string[i];
            }
            return value%TableLength;
        }

        int hash(Key key) {
            switch(key.type) {
                case key_types(uid):
                    return hashChar(key.keys.uid);
                    break;
                case key_types(name):
                    return hashString(key.keys.name);
                    break;
                default:
                    testOutput("No hash function for this type\n");
                    exit(0);
            }
        }
    public:
        void addElement(Value value, Key key) {
            if(List == 0) {
                valueType = value.type;
                testOutput("First item on the table: Alocating\n");
                allocateTable(valueType);
            }

            if(value.type != valueType) {
                testOutput("Tried to add wrong type of value\n");
                exit(0);
            }

            int index = hash(key);
            testOutput("The index for the hashed key is ");
            testOutput(index);
            switch(valueType) {
                case value_types(client):
                    addClient(value.value.client, index);
                    break;
                case value_types(destLists):
                    addDestList(value.value.destLists, index);
                    break;
                default:
                    testOutput("Trying to add Element which has no type\n");
                    exit(0);
            }
        }

        void removeElement(Key key) {
            int index = hash(key);
        }

        void* getElement(Key key, int type) {
            int index = hash(key);
            switch(type) {
                case value_types(client):
                    return &((Client*)List)[index];
                    break;
                case value_types(destLists):
                    return &((DestLists*)List)[index];
                    break;
                default:
                    testOutput("Trying to get an elemnt of a non existiong type\n");
                    exit(0);
            }

        }
};

int main() {
    HashTable main_table;

    //Client1
    Client Rick;
    Rick.uid = 'X';
    Rick.badgeNumber = 57;

    Value RicksValue;
    RicksValue.type = value_types(client);
    RicksValue.value.client = Rick;

    Key RicksKey;
    RicksKey.type = key_types(uid);
    RicksKey.keys.uid = Rick.uid;
    //

    //Client2
    Client Roger;
    Rick.uid = 'X';
    Rick.badgeNumber = 57;

    Value RogersValue;
    RogersValue.type = value_types(client);
    RogersValue.value.client = Roger;

    Key RogersKey;
    RogersKey.type = key_types(uid);
    RogersKey.keys.uid = Roger.uid;
    //

    main_table.addElement(RicksValue, RicksKey);
    main_table.addElement(RogersValue, RogersKey);
    
    Client* RickPtr = (Client*)main_table.getElement(RicksKey, value_types(client));
    printf("Ricks uid stored in the table: %c\n", RickPtr->uid);
}

