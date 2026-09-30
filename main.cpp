#include <iostream>
#include <bitset>
#include <cstdint>
#include "gpio/enums.h"
#include "gpio/helpers.h"

int main()
{
	std::cout << std::bitset<32>{Helpers::fieldMask(15, PinWidthBits::one)} << '\n';

	return 0;
}