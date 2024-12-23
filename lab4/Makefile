CXX = g++
CXXFLAGS = -Wall -Wextra -g
TARGET = mines

all: $(TARGET)

$(TARGET): mines.o Board.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) mines.o Board.o

mines.o: mines.cpp Board.hpp
	$(CXX) $(CXXFLAGS) -c mines.cpp

Board.o: Board.cpp Board.hpp
	$(CXX) $(CXXFLAGS) -c Board.cpp

clean:
	rm -f $(TARGET) *.o