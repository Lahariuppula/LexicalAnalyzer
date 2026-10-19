a.out: main.o lexer.o
	gcc -o a.out main.o lexer.o
main.o: main.c
	gcc -c main.c
lexer.o: lexer.c lexer.h
	gcc -c lexer.c
clean:
	rm -f a.out main.o lexer.o