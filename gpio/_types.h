#ifndef TYPES_H
#define TYPES_H

#include "_enums.h"
#include <cstdint>

namespace gpio
{
	using PinId = std::uint8_t;
	using Register = std::uint32_t;

	struct PinConfig
	{
		PinMode mode{ PinMode::analog };
		OutputType outputType{ OutputType::pushPull };
		Speed speed{ Speed::low };
		Pull pull{ Pull::none };
	};

	struct GpioPort
	{
		Register moder{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
		Register otyper{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
		Register ospeedr{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
		Register pupdr{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
		Register idr{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
		Register odr{ 0b0000'0000'0000'0000'0000'0000'0000'0000 };
	};

	template <typename T>
	struct Snapshot
	{
		T before{};
		T after{};
	};

	template <typename T>
	Snapshot(T, T) -> Snapshot<T>;
}

#endif