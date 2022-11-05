main.out: main.o lexer
	gcc -o main.out main.o lexer/lex.yy.o

lexer: .FORCE
	$(MAKE) -C lexer

main.o: main.c
	cc -g -c main.c

clean:
	-rm -rf **/*.out
	-rm -rf **/*.o
	-rm -rf **/*.dSYM

.FORCE: