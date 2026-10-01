#ifndef HELPERS_H
#define HELPERS_H

#include "_types.h"
#include "_enums.h"
#include "_constants.h"
#include <cstdint>
#include <cassert>
#include <cstdlib>

namespace gpio
{
	namespace helpers
	{
		inline constexpr bool isPinValid(PinId pin)
		{
			return pin <= gpio::constants::maxPin;
		}

		inline constexpr void validatePin(PinId pin)
		{
			if (!helpers::isPinValid(pin)) {
				assert(false && "Invalid pin ID!");
				std::abort();
			}
		}

		inline constexpr std::uint8_t getPinPosition(PinId pin, PinWidthBits width)
		{
			validatePin(pin);

			return static_cast<std::uint8_t>(pin * static_cast<std::uint8_t>(width));
		}

		inline constexpr Register fieldMask(PinId pin, PinWidthBits width)
		{
			validatePin(pin);

			constexpr Register mask{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };

			const Register pinMask{ (1u << static_cast<Register>(width)) - 1u };
			const auto pinPosition{ getPinPosition(pin, width) };

			return mask | (pinMask << pinPosition);
		}
	}
}

#endif