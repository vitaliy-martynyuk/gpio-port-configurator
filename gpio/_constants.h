#ifndef GPIO_CONSTANTS_H
#define GPIO_CONSTANTS_H

#include "_types.h"
#include <cstdint>

namespace gpio
{
	namespace constants
	{
		inline constexpr GpioPort resetPort{ .moder = 0b1111'1111'1111'1111'1111'1111'1111'1111 };
		inline constexpr std::uint8_t pinsPerPort{ 16 };
		inline constexpr PinId maxPin{ pinsPerPort - 1 };
		inline constexpr PinId minPin{ 0 };
		inline constexpr std::uint8_t reservedPullEncoding{ 0b11 };
	}
}

#endif
