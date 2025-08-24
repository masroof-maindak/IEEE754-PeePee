#include <cmath>
#include <expected>
#include <print>
#include <ranges>
#include <string_view>

std::expected<void, std::string> is_valid_float_str(std::string_view floatstr) {
	if (floatstr.length() != 32)
		return std::unexpected("Invalid string length.");

	for (auto c : floatstr)
		if (c != '0' && c != '1')
			return std::unexpected("Malformed binary string.");

	return {};
}

std::expected<void, std::string>
showcase_singles_conversion(std::string_view floatstr) {
	if (auto valid = is_valid_float_str(floatstr); !valid)
		return valid;

	const char sign_bit{floatstr[0]};
	std::string_view exponent_str{floatstr.begin() + 1, floatstr.begin() + 9};
	std::string_view mantissa_str{floatstr.begin() + 9, floatstr.begin() + 32};

	std::println("Sign-Bit: {}", sign_bit);
	std::println("Exponent: {}", exponent_str);
	std::println("Mantissa: {}\n", mantissa_str);

	// 1. Resolve mantissa
	float mantissa{1};
	int power{2};

	for (auto c : mantissa_str) {
		if (c == '1') {
			std::println("Adding to mantissa: 1 / {} = {}", power, 1.0 / power);
			mantissa += (1.0 / power);
		}

		power *= 2;
	}

	// CHECK: Is this a standards violation? Fuck it.
	printf("\nMantissa: %.100g\n\n", mantissa);

	// 2. Determine exponent
	int exponent{0};
	power = 0;

	for (auto c : exponent_str | std::views::reverse) {
		if (c == '1') {
			std::println("Adding to exponent: 2^{} = {}", power, (1 << power));
			exponent += (1 << power);
		}

		power++;
	}

	std::println("\nExponent: {}", exponent);
	exponent -= 127;
	std::println("Exponent after 'normalizing': {}", exponent);

	// 3. Bring it all together
	if (sign_bit == '1')
		mantissa *= -1;

	printf("\nDecimal value: %.100g * 2^%d = %.100g\n", mantissa, exponent,
		   mantissa * powf(2, exponent));

	return {};
}

int main(int argc, char *argv[]) {
#ifdef DEBUG
	std::string_view num{"01111000011110000000000000000000"};
#else
	if (argc != 2) {
		std::cerr << "Usage: " << argv[0] << " <binarystring>\n";
		return 4;
	}

	std::string_view num{argv[1]};
#endif

	auto ret = showcase_singles_conversion(num);

	if (!ret) {
		std::println(stderr, "{}", ret.error());
		return 4;
	}

	return 0;
}
