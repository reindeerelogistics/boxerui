#include "RoboCMD.cpp"
#include <iostream>

using namespace std;

int main(){
    uint8_t array[20] = "Ramsey";
    copyName(UI.name, array, 0);

    setServerAddress("184.146.119.106", 8000);
    joinServer();


    uint8_t name[] = "Ramsey";
    uint8_t sign = '+';
    uint8_t op = '1';
    uint8_t dests[] = "Aaron";
    mutateDestinations(name, '+', '1', dests);

    RoboCMD <float,float,float,float> cmd;
    cmd.set(0x01,75,100,-100,0);
    cmd.sendMsg();

return 0;
}