#ifndef GPIO_NAMES_H
#define GPIO_NAMES_H

#include "_enums.h"
#include "_types.h"

namespace gpio
{
	inline constexpr std::string_view getName(PinMode value)
	{
		switch (value)
		{
		case PinMode::input:
			return "input";
		case PinMode::output:
			return "output";
		case PinMode::alternate:
			return "alternate";
		case PinMode::analog:
			return "analog";
		default:
			return "unknown";
		}
	}

	inline constexpr std::string_view getName(OutputType value)
	{
		switch (value)
		{
		case OutputType::pushPull:
			return "push-pull";
		case OutputType::openDrain:
			return "open-drain";
		default:
			return "unknown";
		}
	}

	inline constexpr std::string_view getName(Speed value)
	{
		switch (value)
		{
		case Speed::low:
			return "low";
		case Speed::medium:
			return "medium";
		case Speed::high:
			return "high";
		case Speed::veryHigh:
			return "very high";
		default:
			return "unknown";
		}
	}

	inline constexpr std::string_view getName(Pull value)
	{
		switch (value)
		{
		case Pull::none:
			return "none";
		case Pull::down:
			return "down";
		case Pull::up:
			return "up";
		default:
			return "unknown";
		}
	}

	inline std::ostream& operator<<(std::ostream& out, PinMode value)
	{
		out << getName(value);

		return out;
	}

	inline std::ostream& operator<<(std::ostream& out, OutputType value)
	{
		out << getName(value);

		return out;
	}

	inline std::ostream& operator<<(std::ostream& out, Speed value)
	{
		out << getName(value);

		return out;
	}

	inline std::ostream& operator<<(std::ostream& out, Pull value)
	{
		out << getName(value);

		return out;
	}

	inline std::ostream& operator<<(std::ostream& out, PinConfig config)
	{
		out << config.mode << " / " << config.outputType << " / " << config.speed << " / " << config.pull;

		return out;
	}

	void printPortDiff(const Snapshot<GpioPort>& snapshot);
}

#endif
