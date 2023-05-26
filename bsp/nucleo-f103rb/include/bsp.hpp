#ifndef BSP_HPP_
#define BSP_HPP_

#include <cstdint>

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

    int tim_get_status();

    void tim_clear_status();
} // namespace swaw::bsp

#endif