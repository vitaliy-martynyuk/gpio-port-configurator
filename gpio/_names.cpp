#include "_names.h"
#include "_types.h"
#include <string_view>
#include <iostream>
#include <iomanip>
#include <bitset>

namespace gpio
{
	namespace
	{
		void printRegisterDiff(std::string_view name, const Snapshot<Register>& registerSnapshot)
		{
			constexpr int nameWidth{ 8 };
			constexpr int labelWidth{ 8 };

			const auto diff{ changedBits(registerSnapshot) };
			if (!diff)
			{
				std::cout << std::left
					<< std::setw(nameWidth) << name << " (no changes)\n";
			}

			std::cout << std::left
				<< std::setw(nameWidth) << name << std::setw(labelWidth) << "before" << std::bitset<32>{ registerSnapshot.before } << '\n'
				<< std::setw(nameWidth) << "" << std::setw(labelWidth) << "after" << std::bitset<32>{ registerSnapshot.after } << '\n'
				<< std::setw(nameWidth) << "" << std::setw(labelWidth) << "changed" << std::bitset<32>{ diff } << '\n';
		}
	}

	void printPortDiff(const Snapshot<GpioPort>& snapshot)
	{
		printRegisterDiff("moder", Snapshot{ snapshot.before.moder, snapshot.after.moder });
		printRegisterDiff("otyper", Snapshot{ snapshot.before.otyper, snapshot.after.otyper });
		printRegisterDiff("ospeedr", Snapshot{ snapshot.before.ospeedr, snapshot.after.ospeedr });
		printRegisterDiff("pupdr", Snapshot{ snapshot.before.pupdr, snapshot.after.pupdr });
		printRegisterDiff("idr", Snapshot{ snapshot.before.idr, snapshot.after.idr });
		printRegisterDiff("odr", Snapshot{ snapshot.before.odr, snapshot.after.odr });
	}
}
