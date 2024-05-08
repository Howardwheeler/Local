all: run
	g++ main.cpp PrintJob.cpp Heap.cpp -Wall -Werror -e a.exe

program: main.cpp Heap.h Heap.cpp PrintJob.h PrintJob.cpp
		$(CXX) -e program -std=c++11 main.cpp Heap.cpp PrintJob.cpp

run_input: program
	./a.exe .\main.cpp .\Heap.cpp .\PrintJob.cpp

run_input1: program
	./program < input.1