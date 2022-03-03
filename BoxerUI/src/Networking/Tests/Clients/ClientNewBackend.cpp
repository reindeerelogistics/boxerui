#include "../../uiBackend.cpp"

int main() {
    Client client;
    uint8_t name[20] = "Aaron";
    uint8_t bio[20] = "Mechatronics";
    client.setTest(1);
    client.join(name, bio);
}
