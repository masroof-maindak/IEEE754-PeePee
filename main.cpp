#include <cmath>
#include <expected>
#include <iostream>
#include <ranges>
#include <string_view>

std::expected<void, std::string>
is_valid_float_str(std::string_view float_str) {
	if (float_str.length() != 32)
		return std::unexpected("Invalid string length.");

	for (auto c : float_str)
		if (c != '0' && c != '1')
			return std::unexpected("Malformed binary string.");

	return {};
}

std::expected<void, std::string>
showcase_single_to_decimal(std::string_view float_str) {
	if (auto valid = is_valid_float_str(float_str); !valid)
		return valid;

	const char sign_bit{float_str[0]};
	std::string_view exponent_str{float_str.begin() + 1,
								  float_str.begin() + 1 + 8};
	std::string_view mantissa_str{float_str.begin() + 9,
								  float_str.begin() + 9 + 23};

	std::cout << "Sign-Bit: " << sign_bit << "\n";
	std::cout << "Exponent: " << exponent_str << "\n";
	std::cout << "Mantissa: " << mantissa_str << "\n\n";

	// 1. Resolve mantissa
	float mantissa{1};
	int power{2};

	for (auto c : mantissa_str) {
		if (c == '1') {
			std::cout << "Adding to mantissa: " << "1 / " << power << " = "
					  << (1.0f / power) << "\n";
			mantissa += (1.0f / power);
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
			std::cout << "Adding to exponent: " << "2^" << power << " = "
					  << powf(2, power) << "\n";
			exponent += powf(2, power);
		}

		power++;
	}

	std::cout << "\nExponent: " << exponent << "\n";
	exponent -= 127;
	std::cout << "Exponent after 'normalizing': " << exponent << "\n\n";

	// 3. Bring it all together
	if (sign_bit == '1')
		mantissa *= -1;

	printf("Decimal value: %.100g * 2^%d = %.100g\n\n", mantissa, exponent,
		   mantissa * powf(2, exponent));

	return {};
}

int main() {
	std::string_view num{"01111000011110000000000000000000"};
	auto r = showcase_single_to_decimal(num);

	std::string_view num{"01111000011110000000000000000000"};
	auto ret = showcase_single_to_decimal(num);

	if (!ret) {
		std::cerr << ret.error() << "\n";
		return 4;
	}

	return 0;
}
