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

	return 0;
}