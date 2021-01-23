CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic-errors -O2
OBJECTS = src/csp.o src/loc.o sudoku_solver.o

sudoku_solver: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o sudoku_solver $(OBJECTS)
