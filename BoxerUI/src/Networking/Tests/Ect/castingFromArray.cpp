#include "../../uiBackend.cpp"

struct Data {
    uint32_t value;
    double other_value;
};

int main() {
    Client client;
    client.setTest(1);

    Data data;
    data.value = 26;
    data.other_value = 27.0;

    uint8_t array[500];
    client.serialize<Data>(array, data);

    Resources::check<int>(data.value, (*(Data*)array).value);

}

