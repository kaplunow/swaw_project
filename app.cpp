#include "bsp.hpp"
#include <cstdio>

extern "C" {
}

using namespace swaw;

int main() {

    bsp::init();

    int hall, prev_hall = 0;
    int periods = 0;

    while (1) {
        if (bsp::tim_get_status() == 1) {
            prev_hall = hall;
            hall = bsp::read_hall();
            if(bsp::detection_moment(hall,prev_hall)){
                float velocity =bsp::calculate_velocity(periods,bsp::get_radius());
                printf("radius = %f\n", bsp::get_radius());
                periods = 0;
            }else{
                periods++;
            }
            bsp::tim_clear_status();
        }
    }

    return 0;
}