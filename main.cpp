#include <iostream>
#include <bitset>
#include <cstdint>
#include "gpio/_enums.h"
#include "gpio/_helpers.h"

int main()
{
	std::cout << std::bitset<32>{Helpers::fieldMask(0, PinWidthBits::one)} << '\n';
	std::cout << std::bitset<32>{Helpers::fieldMask(0, PinWidthBits::two)} << '\n';
	std::cout << std::bitset<32>{Helpers::fieldMask(15, PinWidthBits::one)} << '\n';
	std::cout << std::bitset<32>{Helpers::fieldMask(15, PinWidthBits::two)} << '\n';

	return 0;
}