Default: build

build:
	g++ main.cpp -std=c++23 -o main

debug:
	g++ main.cpp -DDEBUG -std=c++23 -o main
