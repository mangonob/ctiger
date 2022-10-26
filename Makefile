main.out: main.c
	gcc -g -o main.out main.c

clean:
	-rm -rf *.out
	-rm -rf *.o
	-rm -rf *.dSYM
