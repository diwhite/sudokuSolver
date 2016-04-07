all: solver.exe

solver.exe: solver.cpp
	 g++ -o solver.exe solver.cpp
     
clean:
	 rm solver.o solver.exe