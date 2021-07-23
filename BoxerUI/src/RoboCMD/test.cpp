#include "RoboCMD.cpp"
#include <iostream>

using namespace std;

int main(){

    RoboCMD <float,float,float,float> cmd;

    cmd.set(0x06,0.5,2);

    vector<uint8_t> msg = cmd.getMsg();

    for(int i = 0; i<msg.size(); i++){

        printf("%#x ", msg.at(i));
    }

     printf("\nuint16 of byte 2&3: %d", ((uint16_t)msg.at(1) << 8) | msg.at(2));

    cmd.clrMsg();

return 0;
}