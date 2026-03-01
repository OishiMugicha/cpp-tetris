CXX = g++
CXXFLAGS = -Wall -std=c++23 -g3 -O0 -W -Wall -Wextra -Wconversion -Wpedantic -Wshadow -Werror -mwindows

main: main.o
	$(CXX) $(CXXFLAGS) main.o

main.o:
	$(CXX) $(CXXFLAGS) -c cpp-tetris/main.cpp