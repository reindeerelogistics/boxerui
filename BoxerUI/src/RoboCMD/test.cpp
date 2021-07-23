#include "RoboCMD.cpp"
#include <iostream>

using namespace std;

int main(){

    RoboCMD <short,short,short,short> cmd;

    cmd.set(0x01,763,1000,-1000,0);

    cmd.disMsg();

return 0;
}