all:
	bison -d parser.y
	flex lexer.l
	g++ -o sketches parser.tab.c lex.yy.c -lfl
