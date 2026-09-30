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

		std::uint8_t getPinBits(const Register& reg, PinId pin, PinWidthBits width)
		{
			const Register mask{ helpers::fieldMask(pin, width) };
			const auto pinPosition{ helpers::getPinPosition(pin, width) };

			return static_cast<std::uint8_t>((reg & mask) >> pinPosition);
		}
	}

	void configurePin(GpioPort& port, PinId pin, const PinConfig& config)
	{
		if (!helpers::isPinValid(pin)) {
			assert(false && "Invalid pin ID!");
			std::abort();
		}

		setPinBits(port.pupdr, pin, PinWidthBits::two, config.pull);
		setPinBits(port.otyper, pin, PinWidthBits::one, config.outputType);
		setPinBits(port.ospeedr, pin, PinWidthBits::two, config.speed);
		setPinBits(port.moder, pin, PinWidthBits::two, config.mode);
	}

	std::optional<PinConfig> readPinConfig(const GpioPort& port, PinId pin)
	{
		const auto pupdrV{ getPinBits(port.pupdr, pin, PinWidthBits::two) };
		if (pupdrV == static_cast<std::uint8_t>(Pull::invalid)) return std::nullopt;
		const auto otyperV{ getPinBits(port.otyper, pin, PinWidthBits::one) };
		const auto ospeedrV{ getPinBits(port.ospeedr, pin, PinWidthBits::two) };
		const auto moderV{ getPinBits(port.moder, pin, PinWidthBits::two) };

		PinConfig config{};
		config.mode = static_cast<PinMode>(moderV);
		config.outputType = static_cast<OutputType>(otyperV);
		config.speed = static_cast<Speed>(ospeedrV);
		config.pull = static_cast<Pull>(pupdrV);

		return config;
	}
}