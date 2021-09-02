#include <stdio.h>
#include <stdlib.h>

int Test;
void testOutput(const char* value) {
    if(Test == 1)
    printf("[#]%s", value);
}

void testOutput(int value) {
    if(Test == 1)
        printf("%d\n", value);
}
namespace Hash {
    int maxLength = 49;
    int ListSize = 50;

    template <typename Value, typename Key> struct Table {

        private:
            void* List = 0;
            int TableLength = maxLength;

            void allocateTable() {
                if(List != 0) {
                    testOutput("This table has already been allocated\n");
                    exit(0);
                }
                List = calloc(TableLength, sizeof(Value));
            }

            int hash(Key key) {
                return (key*100 + 100)%TableLength;
            }

        public:
            void addElement(Value value, Key key) {
                if(List == 0) {
                    testOutput("First item on the table: Alocating\n");
                    allocateTable();
                }

                int index = hash(key);
                testOutput("The index for the hashed key is ");
                testOutput(index);

                ((Value*)List)[index] = value;
            }

            void removeElement(Key key) {
                int index = hash(key);
            }

            void* getElement(Key key) {
                int index = hash(key);
                return &((Value*)List)[index];
            }

    };
};
