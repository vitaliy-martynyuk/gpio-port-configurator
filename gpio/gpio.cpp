#include "gpio.h"
#include "_tests.h"
#include <cstdint>
#include <optional>
#include <cassert>
#include <cstdlib>

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

		std::uint8_t getPinBits(Register reg, PinId pin, PinWidthBits width)
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

		const auto pullBits{ getPinBits(port.pupdr, pin, PinWidthBits::two) };

		if (pullBits == constants::reservedPullEncoding)
		{
			return std::nullopt;
		}

		const auto typeBits{ getPinBits(port.otyper, pin, PinWidthBits::one) };
		const auto speedBits{ getPinBits(port.ospeedr, pin, PinWidthBits::two) };
		const auto modeBits{ getPinBits(port.moder, pin, PinWidthBits::two) };

		return PinConfig{
			.mode = static_cast<PinMode>(modeBits),
			.outputType = static_cast<OutputType>(typeBits),
			.speed = static_cast<Speed>(speedBits),
			.pull = static_cast<Pull>(pullBits),
		};
	}

	void applyBsrr(GpioPort& port, Register bsrr)
	{
		const Register bsrrReset{ static_cast<RegisterHalf>(bsrr >> constants::pinsPerPort) };
		const Register bsrrSet{ static_cast<RegisterHalf>(bsrr) };

		port.odr &= ~bsrrReset;
		port.odr |= bsrrSet;
	}

	void writePin(GpioPort& port, PinId pin, bool level)
	{
		helpers::validatePin(pin);

		const Register pinBsrr{ 1u << (level ? pin : pin + constants::pinsPerPort) };
		applyBsrr(port, pinBsrr);
	}

	void sampleInputs(GpioPort& port, RegisterHalf externalLevels)
	{
		for (PinId pin{ 0 }; pin < constants::pinsPerPort; ++pin)
		{
			const auto pinOdrValue{ getPinBits(port.odr, pin, PinWidthBits::one) };
			const auto pinModeValue{ static_cast<PinMode>(getPinBits(port.moder, pin, PinWidthBits::two)) };
			const auto pinOutputTypeValue{ static_cast<OutputType>(getPinBits(port.otyper, pin, PinWidthBits::one)) };
			const auto pinExternalValue{ getPinBits(externalLevels, pin, PinWidthBits::one) };
			std::uint8_t pinIdrValue{};

			if (pinModeValue == PinMode::analog)
			{
				pinIdrValue = 0;
			}
			else if (pinModeValue == PinMode::output)
			{
				switch (pinOutputTypeValue)
				{
				case OutputType::pushPull:
					pinIdrValue = pinOdrValue;
					break;
				case OutputType::openDrain:
					pinIdrValue = pinOdrValue ? pinExternalValue : 0u;
					break;
				default:
					assert(false && "Invalid pin OutputType!");
					std::abort();
				}
			}
			else
			{
				pinIdrValue = pinExternalValue;
			}

			setPinBits(port.idr, pin, PinWidthBits::one, pinIdrValue);
		}
	}

	bool readPin(const GpioPort& port, PinId pin)
	{
		helpers::validatePin(pin);

		return static_cast<bool>(getPinBits(port.idr, pin, PinWidthBits::one));
	}
}
