#include "bsp.hpp"
#include <cstdio>

extern "C" {
}

using namespace swaw;

int main() {

    bsp::init();

    int raw_hall;

    while (1) {
        if (bsp::tim_get_status() == 1) {
            raw_hall = bsp::read_hall();
            printf("raw_hall = %d\n", raw_hall);
            bsp::tim_clear_status();
        }
    }

    return 0;
}