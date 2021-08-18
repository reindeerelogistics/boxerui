#include <stdio.h>
#include <cstdlib>

struct Header {
    int type;
    Header* next;
};

struct MsgImg {
    struct Header Head;
    int payload;
};

struct MsgCon {
    struct Header Head;
    char payload;
};

struct Header* lastHeader;
struct Header* Start;

void appendInfo(struct Header* NewHeadInfo) {
    switch(NewHeadInfo->type) {
        case 0: {
            struct MsgImg* Temp = (struct MsgImg*)lastHeader;
            Temp->Head.type = NewHeadInfo->type;
            Temp->payload = ((struct MsgImg*)NewHeadInfo)->payload;
            break;
                }
        case 1: {
            struct MsgCon* Temp = (struct MsgCon*)lastHeader;
            Temp->Head.type = NewHeadInfo->type;
            Temp->payload = ((struct MsgCon*)NewHeadInfo)->payload;
            break;

                }
        default:
                printf("Not a valid type\n");
            break;
    }
}

void append(struct Header* NewHead) {
    lastHeader->next = (struct Header*)malloc(sizeof(NewHead));
    printf("Alocated Address: %d\n", lastHeader->next);
    lastHeader = lastHeader->next;
    lastHeader->next = NULL;

    appendInfo(NewHead);

}

void print(struct Header* CurrentHead) {
    printf("Type: %d\n", CurrentHead->type);
    if(CurrentHead->next != NULL) {
    printf("Address of next: %d\n", CurrentHead->next);
    } else {
        printf("End of list\n");
    }
}

int main() {
    struct MsgCon Con1;
    Con1.Head.type = 1;
    Con1.payload = 20;
    Start = &Con1.Head;
    lastHeader = &Con1.Head;

    struct MsgImg Img1;
    Img1.Head.type = 0;
    Img1.payload = 21;
    append(&Img1.Head);

    struct MsgCon Con2;
    Con2.Head.type = 1;
    Con2.payload = 22;
    append(&Con2.Head);

    print(Start);
    print(Start->next);
    print(Start->next->next);

    //print(lastHeader->next->next);
}
