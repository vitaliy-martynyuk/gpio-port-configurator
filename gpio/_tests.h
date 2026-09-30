#ifndef TESTS_H
#define TESTS_H

#include "_helpers.h"
#include "_enums.h"
#include "_types.h"
#include "_constants.h"
#include <cstdint>

static_assert(sizeof(PinConfig) == 4);
static_assert(sizeof(GpioPort) == 24);

static_assert(Helpers::isPinValid(Constants::minPin));
static_assert(Helpers::isPinValid(Constants::maxPin));
static_assert(!Helpers::isPinValid(16));

static_assert(Helpers::fieldMask(Constants::minPin, PinWidthBits::one) == 0b1);
static_assert(Helpers::fieldMask(Constants::minPin, PinWidthBits::two) == 0b11);
static_assert(Helpers::fieldMask(Constants::maxPin, PinWidthBits::one) == 0b1000'0000'0000'0000);
static_assert(Helpers::fieldMask(Constants::maxPin, PinWidthBits::two) == 0b1100'0000'0000'0000'0000'0000'0000'0000);

static_assert(static_cast<std::uint8_t>(PinMode::input) == 0b00);
static_assert(static_cast<std::uint8_t>(PinMode::output) == 0b01);
static_assert(static_cast<std::uint8_t>(PinMode::alternate) == 0b10);
static_assert(static_cast<std::uint8_t>(PinMode::analog) == 0b11);

static_assert(static_cast<std::uint8_t>(OutputType::pushPull) == 0b00);
static_assert(static_cast<std::uint8_t>(OutputType::openDrain) == 0b01);

static_assert(static_cast<std::uint8_t>(Speed::low) == 0b00);
static_assert(static_cast<std::uint8_t>(Speed::medium) == 0b01);
static_assert(static_cast<std::uint8_t>(Speed::high) == 0b10);
static_assert(static_cast<std::uint8_t>(Speed::veryHigh) == 0b11);

static_assert(static_cast<std::uint8_t>(Pull::none) == 0b00);
static_assert(static_cast<std::uint8_t>(Pull::up) == 0b01);
static_assert(static_cast<std::uint8_t>(Pull::down) == 0b10);

static_assert(static_cast<std::uint8_t>(PinWidthBits::one) == 1);
static_assert(static_cast<std::uint8_t>(PinWidthBits::two) == 2);

#endif