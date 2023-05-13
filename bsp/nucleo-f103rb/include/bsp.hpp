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

} // namespace swaw::bsp

#endif