all: MyShell

MyShell: keyhandles.o main.o
	gcc main.o -o MyShell -Wall -Wextra -pedantic 

main.o: main.c
	gcc -c main.c -o main.o

keyhandles.o: keyhandles.c
	gcc -c keyhandles.c -o keyhandles.o

clean:
	rm *.o MyShell.exe
