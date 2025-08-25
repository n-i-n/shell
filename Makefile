<<<<<<< HEAD
all: MyShell

MyShell: keyhandles.o main.o
	gcc main.o -o MyShell -Wall -Wextra -pedantic 

main.o: main.c
	gcc -c main.c -o main.o

keyhandles.o: keyhandles.c
	gcc -c keyhandles.c -o keyhandles.o

clean:
	rm *.o MyShell.exe
=======
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
OBJ = main.o sh_exec.o sh_builtins.o
LIBS = -lreadline -lncurses

all: MyShell

MyShell: $(OBJ)
	$(CXX) $(CXXFLAGS) -o MyShell $(OBJ) $(LIBS)

main.o: main.cpp sh_exec.h 
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

sh_exec.o: sh_exec.cpp sh_exec.h
	$(CXX) $(CXXFLAGS) -c sh_exec.cpp -o sh_exec.o

sh_builtins.o: sh_builtins.cpp sh_builtins.h
	$(CXX) $(CXXFLAGS) -c sh_builtins.cpp -o sh_builtins.o
	
clean:
	rm -f *.o MyShell
>>>>>>> 0ef9fdd (Done)
