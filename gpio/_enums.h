#ifndef GPIO_ENUMS_H
#define GPIO_ENUMS_H

#include <cstdint>
#include <string_view>
#include <ostream>

namespace gpio
{
	enum class PinMode : std::uint8_t
	{
		input		= 0b00,
		output		= 0b01,
		alternate	= 0b10,
		analog		= 0b11,
	};

	enum class OutputType : std::uint8_t
	{
		pushPull	= 0b00,
		openDrain	= 0b01,
	};

	enum class Speed : std::uint8_t
	{
		low			= 0b00,
		medium		= 0b01,
		high		= 0b10,
		veryHigh	= 0b11,
	};

	enum class Pull : std::uint8_t
	{
		none		= 0b00,
		up			= 0b01,
		down		= 0b10,
	};

	enum class PinWidthBits : std::uint8_t
	{
		one = 1,
		two = 2,
	};
}

#endif
