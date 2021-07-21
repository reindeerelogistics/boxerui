#include "RoboCMD.cpp"
#include <iostream>

using namespace std;

int main(){

    RoboCMD <short,short,short,short> cmd;

    cmd.set(0x00,16384);

    cmd.disMsg();


return 0;
}