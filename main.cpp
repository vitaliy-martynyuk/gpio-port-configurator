#include <iostream>
#include <bitset>
#include <cstdint>
#include "gpio/gpio.h"

int main()
{
	std::cout << std::bitset<32>{gpio::helpers::fieldMask(0, gpio::PinWidthBits::one)} << '\n';
	std::cout << std::bitset<32>{gpio::helpers::fieldMask(0, gpio::PinWidthBits::two)} << '\n';
	std::cout << std::bitset<32>{gpio::helpers::fieldMask(15, gpio::PinWidthBits::one)} << '\n';
	std::cout << std::bitset<32>{gpio::helpers::fieldMask(15, gpio::PinWidthBits::two)} << '\n';
	std::cout << std::bitset<16>{static_cast<std::uint16_t>(0b1111'1111'1111'1111'0101'1010'1010'1010 >> 16)} << '\n';

	return 0;
}
