#ifndef TESTS_H
#define TESTS_H

#include "_helpers.h"
#include "_enums.h"
#include "_types.h"
#include "_constants.h"
#include <cstdint>

static_assert(sizeof(gpio::PinConfig) == 4);
static_assert(sizeof(gpio::GpioPort) == 24);

static_assert(gpio::helpers::isPinValid(gpio::constants::minPin));
static_assert(gpio::helpers::isPinValid(gpio::constants::maxPin));
static_assert(!gpio::helpers::isPinValid(16));

static_assert(gpio::helpers::fieldMask(gpio::constants::minPin, gpio::PinWidthBits::one) == 0b1);
static_assert(gpio::helpers::fieldMask(gpio::constants::minPin, gpio::PinWidthBits::two) == 0b11);
static_assert(gpio::helpers::fieldMask(gpio::constants::maxPin, gpio::PinWidthBits::one) == 0b1000'0000'0000'0000);
static_assert(gpio::helpers::fieldMask(gpio::constants::maxPin, gpio::PinWidthBits::two) == 0b1100'0000'0000'0000'0000'0000'0000'0000);

static_assert(static_cast<std::uint8_t>(gpio::PinMode::input) == 0b00);
static_assert(static_cast<std::uint8_t>(gpio::PinMode::output) == 0b01);
static_assert(static_cast<std::uint8_t>(gpio::PinMode::alternate) == 0b10);
static_assert(static_cast<std::uint8_t>(gpio::PinMode::analog) == 0b11);

static_assert(static_cast<std::uint8_t>(gpio::OutputType::pushPull) == 0b00);
static_assert(static_cast<std::uint8_t>(gpio::OutputType::openDrain) == 0b01);

static_assert(static_cast<std::uint8_t>(gpio::Speed::low) == 0b00);
static_assert(static_cast<std::uint8_t>(gpio::Speed::medium) == 0b01);
static_assert(static_cast<std::uint8_t>(gpio::Speed::high) == 0b10);
static_assert(static_cast<std::uint8_t>(gpio::Speed::veryHigh) == 0b11);

static_assert(static_cast<std::uint8_t>(gpio::Pull::none) == 0b00);
static_assert(static_cast<std::uint8_t>(gpio::Pull::up) == 0b01);
static_assert(static_cast<std::uint8_t>(gpio::Pull::down) == 0b10);

static_assert(static_cast<std::uint8_t>(gpio::PinWidthBits::one) == 1);
static_assert(static_cast<std::uint8_t>(gpio::PinWidthBits::two) == 2);

#endif