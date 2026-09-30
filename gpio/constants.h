#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "types.h"

namespace Constants
{
	inline constexpr GpioPort resetPort{ .moder{ 0b1111'1111'1111'1111'1111'1111'1111'1111 } };
}

#endif