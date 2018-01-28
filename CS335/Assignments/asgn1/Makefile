all: 
	flex src/asgn1.lex
	g++ lex.yy.c -lfl -o lexer
	mv lexer bin/lexer
	rm lex.yy.c

clean:
	rm bin/lexer