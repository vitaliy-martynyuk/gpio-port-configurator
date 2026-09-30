#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "_types.h"

namespace gpio
{
	namespace constants
	{
		inline constexpr GpioPort resetPort{ .moder = 0b1111'1111'1111'1111'1111'1111'1111'1111 };
		inline constexpr PinId maxPin{ 15 };
		inline constexpr PinId minPin{ 0 };
	}
}

#endif