#ifndef HELPERS_H
#define HELPERS_H

#include "_types.h"
#include "_enums.h"
#include <cstdint>

namespace Helpers
{
	inline constexpr bool isPinValid(PinId pin)
	{
		if (pin >= 0 && pin <= 15) return true;

		return false;
	}

	inline constexpr std::uint32_t fieldMask(PinId pin, PinWidthBits width = PinWidthBits::one)
	{
		constexpr std::uint32_t mask{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
		const auto pinMask{ static_cast<std::uint8_t>((width == PinWidthBits::one) ? 0b1 : 0b11) };
		const auto pinPosition{ pin * static_cast<std::uint8_t>(width) };

		return mask | (pinMask << pinPosition);
	}
}

#endif