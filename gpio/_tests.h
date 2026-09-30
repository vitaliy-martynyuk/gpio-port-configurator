#ifndef TESTS_H
#define TESTS_H

#include "_helpers.h"
#include "_enums.h"
#include "_types.h"
#include <cstdint>

static_assert(sizeof(PinConfig) == 4);
static_assert(sizeof(GpioPort) == 24);

static_assert(Helpers::isPinValid(0));
static_assert(Helpers::isPinValid(15));
static_assert(!Helpers::isPinValid(16));

static_assert(Helpers::fieldMask(0) == 0b1);
static_assert(Helpers::fieldMask(0, PinWidthBits::two) == 0b11);
static_assert(Helpers::fieldMask(15) == 0b1000'0000'0000'0000);
static_assert(Helpers::fieldMask(15, PinWidthBits::two) == 0b1100'0000'0000'0000'0000'0000'0000'0000);

#endif