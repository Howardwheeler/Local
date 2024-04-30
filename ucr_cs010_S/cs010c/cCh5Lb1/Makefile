all: run_input
	g++ main.cpp PrintJob.cpp Heap.cpp -Wall -Werror -o a.out

program: main.cpp Heap.h Heap.cpp PrintJob.h PrintJob.cpp
		$(CXX) -o program -std=c++11 main.cpp Heap.cpp PrintJob.cpp

run: program
	./program

run_input1: program
	./program < input.1