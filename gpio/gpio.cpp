#include "_tests.h"
#include "gpio.h"
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <optional>

namespace gpio
{
	namespace
	{
		template <typename T>
		void setPinBits(Register& reg, PinId pin, PinWidthBits width, T bits)
		{
			const Register mask{ helpers::fieldMask(pin, width) };
			const Register clearedBits{ reg & ~mask };
			const Register shiftedBits{ static_cast<Register>(bits) << helpers::getPinPosition(pin, width) };

			reg = clearedBits | (shiftedBits & mask);
		}

		std::uint8_t getPinBits(const Register reg, PinId pin, PinWidthBits width)
		{
			const Register mask{ helpers::fieldMask(pin, width) };
			const auto pinPosition{ helpers::getPinPosition(pin, width) };

			return static_cast<std::uint8_t>((reg & mask) >> pinPosition);
		}
	}

	void configurePin(GpioPort& port, PinId pin, const PinConfig& config)
	{
		helpers::validatePin(pin);

		setPinBits(port.pupdr, pin, PinWidthBits::two, config.pull);
		setPinBits(port.otyper, pin, PinWidthBits::one, config.outputType);
		setPinBits(port.ospeedr, pin, PinWidthBits::two, config.speed);
		setPinBits(port.moder, pin, PinWidthBits::two, config.mode);
	}

	std::optional<PinConfig> readPinConfig(const GpioPort& port, PinId pin)
	{
		helpers::validatePin(pin);

		const auto pupdrV{ getPinBits(port.pupdr, pin, PinWidthBits::two) };
		if (pupdrV == constants::reservedPullEncoding) return std::nullopt;
		const auto otyperV{ getPinBits(port.otyper, pin, PinWidthBits::one) };
		const auto ospeedrV{ getPinBits(port.ospeedr, pin, PinWidthBits::two) };
		const auto moderV{ getPinBits(port.moder, pin, PinWidthBits::two) };

		return PinConfig{
			.mode = static_cast<PinMode>(moderV),
			.outputType = static_cast<OutputType>(otyperV),
			.speed = static_cast<Speed>(ospeedrV),
			.pull = static_cast<Pull>(pupdrV),
		};
	}

	void applyBsrr(GpioPort& port, Register bsrr)
	{
		const Register bsrrReset{ static_cast<std::uint16_t>(bsrr >> constants::registerHalf) };
		const Register bsrrSet{ static_cast<std::uint16_t>(bsrr) };

		port.odr &= ~bsrrReset;
		port.odr |= bsrrSet;
	}
}