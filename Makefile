INCLUDE=./include
SOURCE=./src
OUTPUT=./build

objects = $(patsubst src/%.c,build/%.o,$(wildcard src/*.c))

$(OUTPUT)/a.out: $(objects)
	$(CC) -o $@ $(objects)

$(OUTPUT)/%.o: $(SOURCE)/%.c $(SOURCE)/*.h $(INCLUDE)/*.h
	$(CC) -g -c -I $(INCLUDE) -o $@ $<

$(SOURCE)/parser.c: $(SOURCE)/parser.y
	yacc -r all -d -o $@ $(SOURCE)/parser.y

$(SOURCE)/lexer.c: $(SOURCE)/lexer.x
	lex -o $@ $(SOURCE)/lexer.x

.PHONY: clean
clean:
	-rm -rf ./build/*
	-rm -rf *.dSYM
