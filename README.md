# IEEE754 Pee Pee

~Piss shrimple~ Unnecessarily over-engineered & complex IEEE754 single/double-precision floating-pointer converter made for concept-reinforcement. This took embarrassingly long because of endianness skill issues and a stubborn obstinacy w.r.t using muh modern C++ features to an egregious extent.

The double-precision version hasn't been tested yet, but I'm fairly certain it's correct, and just can't be bothered to test it. Feel free to brutally disabuse me of this notion.

## Observations

- My LSP (Clangd) and compile times grew noticeably more sluggish as I kept introducing more modern CPP slop.
- TL;DR: This shit isn't worth it.

## Usage

```bash
git clone https://github.com/masroof-maindak/ieee754-pee-pee.git
cd ieee754-pee-pee
bear -- make # In case you want to hack away at the file; else, just `make` will suffice
./main
```

## TODO

- [x] Replace std::bitset w/ std::string_views
- [x] CLI arguments + Take input from stdin
- [x] Use std::print where applicable
- [x] Handle edge cases: +/-0, infinity, NaN and shit

## Acknowledgements

- [How Floating-Point Numbers are Represented - Spanning Tree](https://youtu.be/bbkcEiUjehk?feature=shared)
- [IEEE-754 Floating Point Converter - h-schmidt](https://www.h-schmidt.net/FloatConverter/IEEE754.html)
- ["C++11 reverse range-based for-loop" - StackOverflow](https://stackoverflow.com/a/66053335)
- [What Every Programmer Should Know About Floating-Point Arithmetic - Department of Physics, University of Connecticut](https://www.phys.uconn.edu/~rozman/Courses/P2200_15F/downloads/floating-point-guide-2015-10-15.pdf)
