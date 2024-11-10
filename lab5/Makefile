CXXFLAGS=-g -Wall -Wextra -Werror -std=c++20

all: normpath

normpath: main.o normpath.o
	$(CXX) $(CXXFLAGS) -o normpath main.o normpath.o

main.o: main.cpp normpath.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

normpath.o: normpath.cpp normpath.hpp
	$(CXX) $(CXXFLAGS) -c normpath.cpp

clean:
	rm -f normpath *.o