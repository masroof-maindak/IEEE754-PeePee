#include <algorithm>
#include <bitset>
#include <cmath>
#include <iostream>
#include <ranges>

void showcase_single_to_decimal(const std::bitset<32> single) {
	std::string converted{single.to_string()};

	std::cout << "Original: " << converted << "\n\n";

	std::reverse(converted.begin(), converted.end());

	const char sign_bit{converted[0]};
	const std::string exponent_str{converted.substr(1, 8)};
	const std::string mantissa_str{converted.substr(9, 23)};

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
}

int main() {
	std::bitset<32> num{0b00000000000000000001111000011110};
	showcase_single_to_decimal(num);

	return 0;
}
