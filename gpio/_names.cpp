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
			const auto diff{ changedBits(registerSnapshot) };
			if (!diff)
			{
				return;
			}

			constexpr int nameWidth{ 8 };
			constexpr int labelWidth{ 8 };

			std::cout << std::left
				<< std::setw(nameWidth) << name << std::setw(labelWidth) << "before" << std::bitset<32>{ registerSnapshot.before } << '\n'
				<< std::setw(nameWidth) << "" << std::setw(labelWidth) << "after" << std::bitset<32>{ registerSnapshot.after } << '\n'
				<< std::setw(nameWidth) << "" << std::setw(labelWidth) << "changed" << std::bitset<32>{ diff } << '\n';
		}
	}

	void printPortDiff(const Snapshot<GpioPort>& snapshot)
	{
		printRegisterDiff("moder", Snapshot<Register>{.before{ snapshot.before.moder }, .after{ snapshot.after.moder }});
		printRegisterDiff("otyper", Snapshot<Register>{.before{ snapshot.before.otyper }, .after{ snapshot.after.otyper }});
		printRegisterDiff("ospeedr", Snapshot<Register>{.before{ snapshot.before.ospeedr }, .after{ snapshot.after.ospeedr }});
		printRegisterDiff("pupdr", Snapshot<Register>{.before{ snapshot.before.pupdr }, .after{ snapshot.after.pupdr }});
		printRegisterDiff("idr", Snapshot<Register>{.before{ snapshot.before.idr }, .after{ snapshot.after.idr }});
		printRegisterDiff("odr", Snapshot<Register>{.before{ snapshot.before.odr }, .after{ snapshot.after.odr }});
	}
}