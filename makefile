CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -O2
OBJECTS = src/csp.o src/loc.o

sudoku_solver: sudoku_solver.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o sudoku_solver sudoku_solver.o $(OBJECTS)

sudoku_solver.o:
	$(CXX) $(CXXFLAGS) -c sudoku_solver.cpp
