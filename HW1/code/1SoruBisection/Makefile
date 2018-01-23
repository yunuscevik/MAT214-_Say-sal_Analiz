all: exe

exe: main.o -lm
	gcc main.o -lm -o  exe

main.o: main.c
	 gcc -c -pedantic-errors -Wall main.c


clean:
	rm *.o exe 
