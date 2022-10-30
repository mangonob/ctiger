main.out: main.o foo.o
	gcc -o main.out main.o foo.o

foo.o: foo.c foo.h
	cc -g -c foo.c

main.o: main.c foo.h
	cc -g -c main.c

clean:
	-rm -rf *.out
	-rm -rf *.o
	-rm -rf *.dSYM
