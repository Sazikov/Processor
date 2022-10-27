FLAGS=-Wall -Wextra -Wpedantic

all:
	g++ $(FLAGS) cpu.cpp cpu_functions.cpp ..\Stack\CPP\stack.cpp -o main