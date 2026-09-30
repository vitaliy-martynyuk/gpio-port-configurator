#ifndef ENUMS_H
#define ENUMS_H

#include <cstdint>

enum class PinMode : std::uint8_t
{
	input		= 0b00,
	output		= 0b01,
	alternate	= 0b10,
	analog		= 0b11,
};

enum class OutputType : std::uint8_t
{
	pushPull,
	openDrain,
};

enum class Speed : std::uint8_t
{
	low,
	medium,
	high,
	veryHigh,
};

enum class Pull : std::uint8_t
{
	none,
	up,
	down,
};

enum class PinWidthBits : std::uint8_t
{
	one = 1,
	two = 2,
};

#endif