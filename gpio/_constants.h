#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "_types.h"
#include <cstdint>

namespace gpio
{
	namespace constants
	{
		inline constexpr GpioPort resetPort{ .moder = 0b1111'1111'1111'1111'1111'1111'1111'1111 };
		inline constexpr PinId maxPin{ 15 };
		inline constexpr PinId minPin{ 0 };
		inline constexpr std::uint8_t reservedPullEncoding{ 0b11 };
		inline constexpr std::uint8_t registerHalf{ 16 };
	}
}

#endif