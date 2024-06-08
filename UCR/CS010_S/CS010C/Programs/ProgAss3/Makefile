CXX = g++

CXXFLAGS = -Wall -Werror -Wuninitialized

TARGET = a.exe

SRCS = Node.cpp Tree.cpp main.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	.\$(TARGET) < test.in