all: solver

solver: main.o -lm
	gcc main.o -lm -o  solver

main.o: main.c
	 gcc -c  main.c
clean:
	rm *.o solver 
