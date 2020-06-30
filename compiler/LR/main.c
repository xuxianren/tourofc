#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
先将文本流解析成词
注意的问题
内存的申请和释放
不要释放栈上内存
*/

char* KeyWord[] = {
	"main",
	"int",
	"unsigned"
	"char",
	"float",
	"double",
	"long",

	"typedef",

	"struct",
	"enum",
	"if",
	"else",
	"switch",
	"case",

	"do",
	"while",
	"for",
	"continue",
	"break",
	"default",
	"goto",


	"return",
	"const",
	"static",
	"private",
};

int IsKeyWord(char* str1) {
	for (int i = 0; i < 24; i++) {
		char* str2 = KeyWord[i];
		if (strcmp(str1, str2) == 0) {
			return 1;
		}
	}
	return 0;
}

//初始化运算符表
char* Operator[] = {
	"+",
	"-",
	"*",
	"/",
	"<",
	"<=",
	">",
	">=",
	"!=",
	"==",
	"=",
};


char* Boundary[] = {
	"(",
	")",
	",",
	";",
	"{",
	"}",
	"#",
};

enum kind {
	id,
	number,
	keyword,
	operator,
	boundary,
};

struct Token
{
	enum kind k;
	char* lexeme;

};

#define is_num(c) ('0'<=c && c<='9')
#define is_alpha(c) (('a'<=c && c<='z') || ('A'<=c && c<='Z'))


char* p;

char get_char() {
	return *p++;
}
void roll_back() {
	p--;
}


struct Token* NextToken() {
	struct Token* token = malloc(sizeof(struct Token));
	char c;
	while ((c = get_char()) != EOF)
		switch (c)
		{
		case('a'):
		case('b'):
		case('c'):
		case('d'):
		case('e'):
		case('f'):
		case('g'):
		case('h'):
		case('i'):
		case('j'):
		case('k'):
		case('l'):
		case('m'):
		case('n'):
		case('o'):
		case('p'):
		case('q'):
		case('r'):
		case('s'):
		case('t'):
		case('u'):
		case('v'):
		case('w'):
		case('x'):
		case('y'):
		case('z'):
		case('A'):
		case('B'):
		case('C'):
		case('D'):
		case('E'):
		case('F'):
		case('G'):
		case('H'):
		case('I'):
		case('J'):
		case('K'):
		case('L'):
		case('M'):
		case('N'):
		case('O'):
		case('P'):
		case('Q'):
		case('R'):
		case('S'):
		case('T'):
		case('U'):
		case('V'):
		case('W'):
		case('X'):
		case('Y'):
		case('Z'):
		case('_'):
		{
			c = get_char();
			int length = 1;
			while (c && (is_num(c) || is_alpha(c) || c == '_'))
			{
				length += 1;
				c = get_char();
			}
			roll_back();
			token->k = id;
			token->lexeme = malloc(length + 1);
			strncpy_s(token->lexeme, length + 1, p - length, length);
			return token;
		}

		case('0'):
		case('1'):
		case('2'):
		case('3'):
		case('4'):
		case('5'):
		case('6'):
		case('7'):
		case('8'):
		case('9'):
		{
			int length = 1;
			c = get_char();
			while (c && is_num(c))
			{
				length += 1;
				c = get_char();
			}
			roll_back();
			token->k = number;
			token->lexeme = malloc(length + 1);
			strncpy_s(token->lexeme, length, p - length, 1);
			return token;
		}

		case('+'):
			token->k = operator;
			token->lexeme = Operator[0];
			return token;
		case('-'):
			token->k = operator;
			token->lexeme = Operator[1];
			return token;
		case('*'):
			token->k = operator;
			token->lexeme = Operator[2];
			return token;
		case('/'):
			token->k = operator;
			token->lexeme = Operator[3];
			return token;

		case('<'):
		{
			c = get_char();
			if (c == '=') {
				token->lexeme = Operator[5];
			}
			else {
				token->lexeme = Operator[4];
				roll_back();
			}
			return token;
		}
		case('='):
		{
			c = get_char();
			if (c == '=') {
				token->lexeme = Operator[9];
			}
			else {
				token->lexeme = Operator[10];
				roll_back();
			}
			return token;
		}
		case('>'):
		{
			c = get_char();
			if (c == '=') {
				token->lexeme = Operator[7];
			}
			else {
				token->lexeme = Operator[6];
				roll_back();
			}
			return token;
		}

		case('('):
			token->k = boundary;
			token->lexeme = Boundary[0];
			return token;
		case(')'):
			token->k = boundary;
			token->lexeme = Boundary[1];
			return token;

		case('{'):
			token->k = boundary;
			token->lexeme = Boundary[4];
			return token;
		case('}'):
			token->k = boundary;
			token->lexeme = Boundary[5];
			return token;

		case('['):
			token->k = boundary;
			token->lexeme = "[";
			return token;
		case(']'):
			token->k = boundary;
			token->lexeme = "]";
			return token;
		case(','):
			token->k = boundary;
			token->lexeme = ",";
			return token;
		case(';'):
			token->k = boundary;
			token->lexeme = ";";
			return token;
		default:
			printf("空白符\n");
			break;
		};
}


int main() {

	char text[] = { 'i', 'n', 't', ' ', 'm', 'a', 'i', 'n', '(', ')', ' ', '{', '}', EOF };
	p = text;
	while (*p != EOF)
	{
		struct Token* token = NextToken();
		printf("当前token值：%s\n", token->lexeme);
		if ((token->k == id) || (token->k == number))
			free(token->lexeme);
		free(token);
	}
}