CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
GTEST_DIR = /usr/src/gtest
GTEST_LIB = -lgtest -lgtest_main -lpthread

all: string_test

string_test: String.o String.test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIB)

String.o: String.cpp String.hpp
	$(CXX) $(CXXFLAGS) -c String.cpp

String.test.o: String.test.cpp String.hpp
	$(CXX) $(CXXFLAGS) -c String.test.cpp

clean:
	rm -f *.o string_test