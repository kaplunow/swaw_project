#include "bsp.hpp"
#include <cstdio>

extern "C" {
}

using namespace swaw;


int main() {

    bsp::init();

    while (1) {
        printf("Hello World!\n");
    }

    return 0;
}