#include "bsp.hpp"
#include <cstdio>

extern "C" {
}

using namespace swaw;


int main() {

    bsp::init();

    while (1) {
        bsp::HelloWorld();
        printf("Hello World!");
        printf("\n");
    }

    return 0;
}