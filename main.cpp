#include "gpio/gpio.h"
#include <iostream>
#include <optional>
#include <string_view>

namespace
{
	constexpr gpio::PinId ledPin{ 5 };
	constexpr gpio::PinId i2cPin{ 9 };
	constexpr gpio::PinId buttonPin{ 13 };
	constexpr gpio::PinId corruptedPin{ 2 };

	void printStep(std::string_view title)
	{
		std::cout << "\n== " << title << " ==\n";
	}

	void printLevel(const gpio::GpioPort& port, std::string_view name, gpio::PinId pin)
	{
		std::cout << name << " (pin " << static_cast<int>(pin) << "): "
			<< (gpio::readPin(port, pin) ? "high" : "low") << '\n';
	}

	void printLevels(const gpio::GpioPort& port)
	{
		printLevel(port, "LED", ledPin);
		printLevel(port, "I2C", i2cPin);
		printLevel(port, "button", buttonPin);
	}

	void printConfig(const gpio::GpioPort& port, gpio::PinId pin)
	{
		const std::optional<gpio::PinConfig> config{ gpio::readPinConfig(port, pin) };

		std::cout << "pin " << static_cast<int>(pin) << ": ";

		if (config)
		{
			std::cout << *config << '\n';
		}
		else
		{
			std::cout << "invalid configuration (reserved pull encoding)\n";
		}
	}
}

int main()
{
	using namespace gpio;

	GpioPort port{ constants::resetPort };
	GpioPort before{ port };

	printStep("1. Configure LED pin as push-pull output");
	configurePin(port, ledPin, { .mode = PinMode::output });
	printPortDiff(Snapshot{ before, port });
	printConfig(port, ledPin);

	printStep("2. Configure button pin as input with pull-up");
	before = port;
	configurePin(port, buttonPin, { .mode = PinMode::input, .pull = Pull::up });
	printPortDiff(Snapshot{ before, port });
	printConfig(port, buttonPin);

	printStep("3. Configure I2C pin as open-drain, high speed, pull-up");
	before = port;
	configurePin(port, i2cPin, {
		.mode = PinMode::output,
		.outputType = OutputType::openDrain,
		.speed = Speed::high,
		.pull = Pull::up,
		});
	printPortDiff(Snapshot{ before, port });
	printConfig(port, i2cPin);

	printStep("4. Drive LED high, release I2C pin, sample with everything low outside");
	before = port;
	writePin(port, ledPin, true);
	writePin(port, i2cPin, true);
	sampleInputs(port, 0);
	printPortDiff(Snapshot{ before, port });
	printLevels(port);

	printStep("5. Sample again with I2C and button lines high outside");
	before = port;
	const RegisterHalf externalLevels{ (1u << i2cPin) | (1u << buttonPin) };
	sampleInputs(port, externalLevels);
	printPortDiff(Snapshot{ before, port });
	printLevels(port);

	printStep("6. One BSRR write that both sets and resets the LED pin (set wins)");
	before = port;
	const Register setLed{ 1u << ledPin };
	const Register resetLed{ 1u << (ledPin + constants::pinsPerPort) };
	applyBsrr(port, setLed | resetLed);
	sampleInputs(port, externalLevels);
	printPortDiff(Snapshot{ before, port });
	printLevel(port, "LED", ledPin);

	printStep("7. Corrupt one pin's pull field to the reserved value");
	before = port;
	constexpr Register reservedPullBits{ 0b11 };
	constexpr Register pullFieldWidth{ 2 };
	port.pupdr |= reservedPullBits << (corruptedPin * pullFieldWidth);
	printPortDiff(Snapshot{ before, port });
	printConfig(port, corruptedPin);
	printConfig(port, ledPin);

	return 0;
}
