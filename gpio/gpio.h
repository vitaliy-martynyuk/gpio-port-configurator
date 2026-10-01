#ifndef GPIO_H
#define GPIO_H

#include "_constants.h"
#include "_enums.h"
#include "_helpers.h"
#include "_types.h"
#include <optional>
#include <cstdint>

namespace gpio
{
	void configurePin(GpioPort& port, PinId pin, const PinConfig& config);
	[[nodiscard]] std::optional<PinConfig> readPinConfig(const GpioPort& port, PinId pin);
	void applyBsrr(GpioPort& port, Register bsrr);
	void writePin(GpioPort& port, PinId pin, bool level);
	void sampleInputs(GpioPort& port, std::uint16_t externalLevels);
	[[nodiscard]] bool readPin(const GpioPort& port, PinId pin);
	template <typename T>
	T changedBits(const Snapshot<T>& snapshot) {};
}

#endif