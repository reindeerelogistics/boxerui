#include "RoboCMD.cpp"
#include <iostream>

using namespace std;

int main(){

    //Network setup stuff start

    uint8_t array[20] = "Ramsey";
    copyName(UI.name, array, 0);

    setServerAddress("184.146.119.106", 8000);
    joinServer();

    uint8_t name[] = "Ramsey";
    uint8_t sign = '+';
    uint8_t op = '1';
    uint8_t dests[] = "Jeff Mike";
    mutateDestinations(name, '+', '1', dests);
    
    //Network setup stuff end

    RoboCMD <float,float,float,float> cmd;

    //making and sending 1 message (start)
    cmd.set(0x01,75,100,-100,0);

    cmd.sendMsg();

    cmd.clrMsg();
    //making and sending 1 message (end)


    //making and sending another message (start)
    cmd.set(0x01,50,100,-100,0);

    cmd.sendMsg();  

    cmd.clrMsg();   //Clears data in buffer (must be done before another set function, Multi-command yet to be implemented)
    //making and sending another message (end)

return 0;
}