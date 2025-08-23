# IEEE754-PeePee

Piss shrimple IEEE754 single-precision floating-pointer converter made for concept-reinforcement. This took embarrassingly long because of endianness skill issues and a stubborn obstinacy w.r.t using muh modern C++ features to an egregious extent.

## Usage

```bash
git clone https://github.com/masroof-maindak/IEEE754-PeePee
cd IEEE754-PeePee
bear -- make # In case you want to hack away at the file; else, just `make` will suffice
./main
```

## TODO

- [ ] Handle edge cases: +/-0, infinity, NaN and shit
- [ ] Take input from stdin

## Acknowledgements

- [How Floating-Point Numbers are Represented - Spanning Tree](https://youtu.be/bbkcEiUjehk?feature=shared)
- [IEEE-754 Floating Point Converter - h-schmidt](https://www.h-schmidt.net/FloatConverter/IEEE754.html)
- ["C++11 reverse range-based for-loop" - StackOverflow](https://stackoverflow.com/a/66053335)
- [What Every Programmer Should Know About Floating-Point Arithmetic - Department of Physics, University of Connecticut](https://www.phys.uconn.edu/~rozman/Courses/P2200_15F/downloads/floating-point-guide-2015-10-15.pdf)
