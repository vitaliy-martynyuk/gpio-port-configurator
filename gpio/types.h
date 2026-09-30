#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

using std::uint8_t;
using std::uint32_t;
using PinId = uint8_t;
using Register = uint32_t;

enum class PinMode : uint8_t
{
	input,
	output,
	alternate,
	analog,
};

enum class OutputType : uint8_t
{
	pushPull,
	openDrain,
};

enum class Speed : uint8_t
{
	low,
	medium,
	high,
	veryHigh,
};

enum class Pull : uint8_t
{
	none,
	up,
	down,
};

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

#endif