#ifndef HELPERS_H
#define HELPERS_H

#include "_types.h"
#include "_enums.h"
#include "_constants.h"
#include <cstdint>
#include <cassert>

namespace Helpers
{
	inline constexpr bool isPinValid(PinId pin)
	{
		return pin <= Constants::maxPin;
	}

	inline constexpr std::uint32_t fieldMask(PinId pin, PinWidthBits width)
	{
		constexpr std::uint32_t mask{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
		if (!isPinValid(pin)) {
			assert(false && "Invalid pin ID!");
			return mask;
		}

		const std::uint32_t pinMask{ (1u << static_cast<std::uint32_t>(width)) - 1u };
		const auto pinPosition{ pin * static_cast<std::uint8_t>(width) };

		return mask | (pinMask << pinPosition);
	}
}

#endif