#ifndef BSP_HPP_
#define BSP_HPP_

#include <cstdint>

#define HALL_SENSOR_VCC 3.3
#define HALL_SENSOR_OFFSET 1.65
#define DETECTION_TRESHOLD 120
#define DETECTION_RESET_TRESHOLD 10
#define HALL_SENSOR_PERIOD 1.0



namespace swaw::bsp {

    /**
     * @brief Initializes platform
     */
    void init() noexcept;

    /**
     * @brief Led blinking test function
     */
    void HelloWorld() noexcept;

    int read_hall();

    bool detection_moment(int,int);

    bool detection_able_reset(int,bool);

    float calculate_velocity(int,float);
    
    int tim_get_status();

    float get_radius();

    void tim_clear_status();
} // namespace swaw::bsp

#endif