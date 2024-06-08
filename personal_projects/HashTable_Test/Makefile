all: a.exe

a.exe: hashtable.cpp main.cpp
	g++ -Wall -Wuninitialized -Werror hashtable.cpp main.cpp -o a.exe

run: a.exe
	.\a.exe < test.in