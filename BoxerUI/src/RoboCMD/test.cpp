#include "RoboCMD.cpp"
#include <iostream>

using namespace std;

int main(){

    RoboCMD <float,float,float,float> cmd;

    cmd.set(0x01,75,100,-100,0);

    vector<uint8_t> msg = cmd.getMsg();

    for(int i = 0; i<msg.size(); i++){

        printf("%#x ", msg.at(i));
    }

     printf("\nuint16 of byte 2&3: %d", ((uint16_t)msg.at(2) << 8) | msg.at(3));

    cmd.clrMsg();

    printf("\n\n RECIVER \n\n");

    cmd.setMsg(msg);

    printf("Command: %d\n", cmd.getCom());
    printf("Direction: %d\n", cmd.getDir());
    printf("Scaller: %f\n", cmd.getScaller());

return 0;
}