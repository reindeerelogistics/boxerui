#include "protocol.h"
#include "resources.h"

struct Client {
    private:
        void sendToServer(uint8_t* data, int size) {
        }


    public:
        template<typename T> uint8_t* serialize(uint8_t* array, T data) {
            Resources::stringCopy(array, (uint8_t*)&data);
            return (array + sizeof(data));
        }
        void setTest(int state) {
            Resources::Test = state;
        }

        void join(uint8_t* name, uint8_t* extra) {
            Protocol::ServerMsg msg;
            Protocol::Join payload;

            Resources::stringCopy(payload.name, name);
            Resources::stringCopy(payload.bio, extra);

            msg.size = (sizeof(msg) + sizeof(payload));
            msg.instruction = 1;
            msg.uid = 0;

            uint8_t data[msg.size];
            uint8_t* next_place;

            next_place = serialize(data, msg);
            next_place = serialize(next_place, payload);

            Resources::check<uint64_t>(msg.size, (*(Protocol::ServerMsg*)data).size);

            sendToServer(data, msg.size);
        }

};
