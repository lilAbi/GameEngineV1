#include "archetype.h"

int ECS::Archetype::GetNextFreePosition() {
    //loop through each bit in index
    for(int i = 0; i < 32; i++){
        int mask = 1 << i;

        //if bit is 0 set it
        if((index & mask) == 0) {
            index |= mask;
            return i;
        }

    }

    return -1;
}
