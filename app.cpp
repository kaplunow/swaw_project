#include "bsp.hpp"
#include <cstdio>

extern "C" {
}

using namespace swaw;

int main() {

    bsp::init();

    int hall, prev_hall = 0;
    int periods = 0;
    bool able_to_detect = true;
    while (1) {
        if (bsp::tim_get_status() == 1) {
            prev_hall = hall;
            hall = bsp::read_hall();
            //printf("HALL : %d\n", able_to_detect);    
            if(able_to_detect){
                if(bsp::detection_moment(hall,prev_hall)){
                    float velocity =bsp::calculate_velocity(periods,bsp::get_radius());
                    printf("%.2f km/h \n", velocity);
                    
                    periods = 0;
                }else{
                    periods++;
                }
            };
            //printf("%d HALL \n", hall);
            able_to_detect = bsp::detection_able_reset(hall,able_to_detect);     
            bsp::tim_clear_status();
        }
    }
    return 0;
}