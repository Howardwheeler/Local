all: run_input
program2: main.cpp Node.h Node.cpp BSTree.h BSTree.cpp
		$(CXX) -o program2 -std=c++11 main.cpp Node.cpp BSTree.cpp

run: program2
	./program2 < input.1

run_input2: program2
	./program2 < input.2