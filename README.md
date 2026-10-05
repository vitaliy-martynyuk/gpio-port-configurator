# GPIO Port Configurator

A small C++ simulation of one STM32-style GPIO port. Sixteen pins are
configured, driven and read through the same registers a real
microcontroller exposes — `MODER`, `OTYPER`, `OSPEEDR`, `PUPDR`, `IDR`,
`ODR` and the write-only `BSRR` — using nothing but masks and shifts.

Built as a learning project while working through
[learncpp.com](https://www.learncpp.com/), focused on consolidating
Chapter 13: scoped enums with explicit underlying types, enum-to-string
conversion and `operator<<` overloading, structs with default member
initializers and designated initializers, passing and returning structs,
class templates and CTAD. Earlier material carries real weight in the
design: bit manipulation (Ch O) is the core of every register access,
`constexpr` functions proven with `static_assert` (Ch F) check the bit
maths at compile time, and `std::optional` (Ch 12) reports a register
field that cannot be decoded. It is also a first step toward embedded
work: the register names, encodings and reset state follow the STM32
reference manual.

## What it does

- Models a port as six 32-bit registers; the registers themselves are
  the only storage, exactly as on hardware
- Describes a pin with four scoped enums (`PinMode`, `OutputType`,
  `Speed`, `Pull`) whose values are the real register encodings, gathered
  in a `PinConfig` struct
- `configurePin(port, pin, config)` writes a pin's four fields into
  `moder`, `otyper`, `ospeedr` and `pupdr` without disturbing any other
  pin, setting the mode last
- `readPinConfig(port, pin)` decodes those fields back into a
  `PinConfig`, or returns an empty `std::optional` if the pull field
  holds the reserved encoding `11`
- `applyBsrr(port, bsrr)` updates the output latch from a set/reset
  command: low half sets, high half resets, and set wins when both are
  given
- `writePin(port, pin, level)` drives one pin high or low, going only
  through `applyBsrr`
- `sampleInputs(port, externalLevels)` recomputes the input register
  from each pin's mode: inputs and alternate pins read the outside
  level, push-pull outputs read their own latch, open-drain outputs read
  low when driving and the outside level when released, analog pins
  read 0
- `readPin(port, pin)` returns a pin's level from the input register
- `changedBits(snapshot)` returns the bits that differ between the
  `before` and `after` of a `Snapshot<T>`
- `printPortDiff(snapshot)` prints every register of a
  `Snapshot<GpioPort>`, showing before / after / changed bits for the
  ones that changed
- `getName` and `operator<<` make every enum and `PinConfig` printable
- `static_assert` checks cover pin validity, field masks, struct sizes
  and every enum encoding

## Project structure

```
main.cpp                 // seven-step demo: configure, drive, sample, corrupt
gpio/
  gpio.h / gpio.cpp      // public API: configurePin, readPinConfig, applyBsrr,
                         //   writePin, sampleInputs, readPin
  _enums.h               // PinMode, OutputType, Speed, Pull, PinWidthBits
  _types.h               // PinId, Register, RegisterHalf, PinConfig, GpioPort,
                         //   Snapshot<T>, changedBits
  _constants.h           // resetPort, pin limits, reserved pull encoding
  _helpers.h             // constexpr isPinValid, validatePin, getPinPosition,
                         //   fieldMask
  _names.h / _names.cpp  // getName, operator<<, printPortDiff
  _tests.h               // static_assert proofs, compiled once from gpio.cpp
```

Headers prefixed with `_` are internal; client code includes only
`gpio/gpio.h`.

## Building

Requires a C++20-capable compiler.

```bash
g++ -std=c++20 -Wall -Wextra -Wconversion -Wshadow -Wsign-conversion -o app \
    main.cpp gpio/gpio.cpp gpio/_names.cpp
```

Or open `GPIO Port Configurator.slnx` in Visual Studio.

## Running

```bash
./app
```

Example output (steps 1, 4 and 7 of 7, shortened):

```
== 1. Configure LED pin as push-pull output ==
moder   before  11111111111111111111111111111111
        after   11111111111111111111011111111111
        changed 00000000000000000000100000000000
otyper  (no changes)
ospeedr (no changes)
pupdr   (no changes)
idr     (no changes)
odr     (no changes)
pin 5: output / push-pull / low / none

== 4. Drive LED high, release I2C pin, sample with everything low outside ==
moder   (no changes)
otyper  (no changes)
ospeedr (no changes)
pupdr   (no changes)
idr     before  00000000000000000000000000000000
        after   00000000000000000000000000100000
        changed 00000000000000000000000000100000
odr     before  00000000000000000000000000000000
        after   00000000000000000000001000100000
        changed 00000000000000000000001000100000
LED (pin 5): high
I2C (pin 9): low
button (pin 13): low

== 7. Corrupt one pin's pull field to the reserved value ==
moder   (no changes)
otyper  (no changes)
ospeedr (no changes)
pupdr   before  00000100000001000000000000000000
        after   00000100000001000000000000110000
        changed 00000000000000000000000000110000
idr     (no changes)
odr     (no changes)
pin 2: invalid configuration (reserved pull encoding)
pin 5: output / push-pull / low / none
```

## Notes

Every register write is a read–modify–write: the pin's field is cleared
with its mask, then the new value is shifted into place and masked again
so it can never spill into a neighbouring pin. The field's position is
computed in one place (`getPinPosition`) and shared by the mask and by
the read and write helpers. All shifting is done on `std::uint32_t`
values, because a `std::uint8_t` operand is promoted to `int` first and
shifting that into the top bits changes the sign. `otyper`, `idr` and
`odr` hold one bit per pin and the other registers two, which is why the
field width is a required `PinWidthBits` argument rather than a default.

`configurePin` writes `moder` last, so on real hardware a pin would not
start driving before its output type and speed are set. The reserved
pull encoding is a named constant, not a `Pull` enumerator, so a `Pull`
value can never hold it and `readPinConfig` has to report it through
`std::optional`. `sampleInputs` reads each pin's mode and type directly
from the registers instead of using `readPinConfig`, so a pin with a
corrupted pull field still gets a fresh reading. `readPin` reports what
the last `sampleInputs` call stored; on hardware the input register
refreshes by itself, here it is refreshed on demand.

An invalid pin id is a programmer error: every public function checks
it once through `validatePin`, which asserts and then aborts in every
build. The same helper is `constexpr`, so an invalid pin in a constant
expression is a compile error. `BSRR` is not stored in `GpioPort`
because it is a command, not state; `applyBsrr` clears the reset pins
first and sets the set pins second, which is what makes set win. A
`static_assert` ties `pinsPerPort` to the width of `RegisterHalf`, so
the cast that splits a `BSRR` value into halves is a checked assumption.

`printPortDiff` lists all six registers on every call, with a single
`(no changes)` line for the unchanged ones, so each step of the demo has
the same shape and is easy to scan. `Snapshot<T>` is used with two
types: `Snapshot<GpioPort>` for a whole port and, built with CTAD,
`Snapshot<Register>` for one register passed to `changedBits`.