%{
	extern void yyerror();
	#include <math.h>
	#include <cstdio> 
	#include <map>
	#include <utility>
	#include <vector>
	#include <string>
	#include <iostream>
	#include <algorithm>
	#include <iomanip>
	
	using namespace std;
	map<string,vector<string> > tokenLexemeMapping;
 	

%}

%option noyywrap
%option yylineno

COMMENT			\/\/[^\n]*\n	
WHITESPACE		[\t\v\n ]+ 
BASE			base
BOOL			bool
BREAK			break
CASE			case
CATCH			catch
CHAR			char
CLASS			class
CONST			const
CONTINUE		continue
DEFAULT			default
DO			do
ELSE			else
FLASE			false
FINALLY			finally
FOR 			for
FOREACH			foreach
GOTO			goto
IF			if
IN 			in
INT			int
LONG			long
NAMESPACE		namespace
NEW			new 	
NULL			null
OBJECT			object
PARAMS			params
PRIVATE  	  	private
PROTECTED		protected
PUBLIC			public
REF			ref
RETURN			return
STRING			string
STRUCT			struct
SWITCH			switch
THIS			this
THROW			throw
TRUE			true
TRY			try
TYPEOF			typeof
UINT			uint
ULONG			ulong
USING 			using
VOID 			void
WHILE 			while
DIGIT 			[0-9]
HEX_DIGIT		[0-9a-fA-F]
ID 			@?[a-zA-Z_][a-zA-Z0-9_]*
DINT_LITERAL		[0-9]+(UL|Ul|uL|ul|LU|Lu|lU|lu|u|U|l|L)?
HDINT_LITERAL		0[xX][0-9a-fA-F]+(UL|Ul|uL|ul|LU|Lu|lU|lu|u|U|l|L)?	
SIMPLE_ESC_SEQ		\'|\"|\\|\0|\n|\r|\t
CHAR_LITERAL		'([^'\\(\n)]|{SIMPLE_ESC_SEQ})'
REG_STR_LITERAL		\"([^(\")(\\)(\n)]|{SIMPLE_ESC_SEQ}|(\\x[0-9a-fA-F]{1,4})|(\\u[0-9a-fA-F]{4,4})|(\\U[0-9a-fA-F]{8,8}))+\"
VER_STR_LITERAL		@\"([^\"]|\"\")+\"
NULL_LITERAL		lsnull
LBRACE			\}
RBRACE			\{
LBRACKET		\]
RBRACKET		\[
LPARENTHESES		\(
RPARENTHESES		\)
DOT			\.
COMMA			,
COLON			:
SEMICOLON		;
PLUS			\+
MINUS			-
STAR 			\*
DIVIDE			\/
MODULO			%	
AMPERSAND		&
OR			\|
CARET 			\^
EXCLAMATION		!
TILDE			~
EQUALS			=
LESS_THAN		<
GREATER_THAN		>
QUESTION_MARK		\?
DOUBLE_QM		\?\?
DOUBLE_COLON		::
INCREMENT		\+\+
DECREMENT		--
REL_AND			&&
REL_OR			\|\|
REL_EQUALS		==
REL_NOT_EQ		!=
LESS_EQUALS		<=
GREATER_EQUALS		>=	
ASSIGN_PLUS		\+=
ASSIGN_MINUS		-=
ASSIGN_STAR		\*=
ASSIGN_DIV		\/=
ASSIGN_MOD		%=
ASSIGN_AND		&=
ASSIGN_OR		\|=
ASSIGN_CARET		\^=
LEFT_SHIFT		<<
LEFT_SHIFT_EQ		<<=
RIGHT_SHIFT		>>
RIGHT_SHIFT_EQ		>>=
DEFINE			{WHITESPACE}*#{WHITESPACE}*define
UNDEF			{WHITESPACE}*#{WHITESPACE}*undef 

%%

{COMMENT} ;
{WHITESPACE}  ;
{DEFINE}  { tokenLexemeMapping["DEFINE"].push_back(yytext);}
{UNDEF}  { tokenLexemeMapping["UNDEF"].push_back(yytext);}
{BASE}  { tokenLexemeMapping["BASE"].push_back(yytext);}
{BOOL}  { tokenLexemeMapping["BOOL"].push_back(yytext);}
{BREAK}  { tokenLexemeMapping["BREAK"].push_back(yytext);}
{CASE}  { tokenLexemeMapping["CASE"].push_back(yytext);}
{CATCH}  { tokenLexemeMapping["CATCH"].push_back(yytext);}
{CHAR}  { tokenLexemeMapping["CHAR"].push_back(yytext);}
{CLASS}  { tokenLexemeMapping["CLASS"].push_back(yytext);}
{CONST}  { tokenLexemeMapping["CONST"].push_back(yytext);}
{CONTINUE}  { tokenLexemeMapping["CONTINUE"].push_back(yytext);}
{DEFAULT}  { tokenLexemeMapping["DEFAULT"].push_back(yytext);}
{DO}  { tokenLexemeMapping["DO"].push_back(yytext);}
{ELSE}  { tokenLexemeMapping["ELSE"].push_back(yytext);}
{FLASE}  { tokenLexemeMapping["FLASE"].push_back(yytext);}
{FINALLY}  { tokenLexemeMapping["FINALLY"].push_back(yytext);}
{FOR}  { tokenLexemeMapping["FOR"].push_back(yytext);}
{FOREACH}  { tokenLexemeMapping["FOREACH"].push_back(yytext);}
{GOTO}  { tokenLexemeMapping["GOTO"].push_back(yytext);}
{IF}  { tokenLexemeMapping["IF"].push_back(yytext);}
{IN}  { tokenLexemeMapping["IN"].push_back(yytext);}
{INT}  { tokenLexemeMapping["INT"].push_back(yytext);}
{LONG}  { tokenLexemeMapping["LONG"].push_back(yytext);}
{NAMESPACE}  { tokenLexemeMapping["NAMESPACE"].push_back(yytext);}
{NEW}  { tokenLexemeMapping["NEW"].push_back(yytext);}
{NULL}  { tokenLexemeMapping["NULL"].push_back(yytext);}
{OBJECT}  { tokenLexemeMapping["OBJECT"].push_back(yytext);}
{PARAMS}  { tokenLexemeMapping["PARAMS"].push_back(yytext);}
{PRIVATE}  { tokenLexemeMapping["PRIVATE"].push_back(yytext);}
{PROTECTED}  { tokenLexemeMapping["PROTECTED"].push_back(yytext);}
{PUBLIC}  { tokenLexemeMapping["PUBLIC"].push_back(yytext);}
{REF}  { tokenLexemeMapping["REF"].push_back(yytext);}
{RETURN}  { tokenLexemeMapping["RETURN"].push_back(yytext);}
{STRING}  { tokenLexemeMapping["STRING"].push_back(yytext);}
{STRUCT}  { tokenLexemeMapping["STRUCT"].push_back(yytext);}
{SWITCH}  { tokenLexemeMapping["SWITCH"].push_back(yytext);}
{THIS}  { tokenLexemeMapping["THIS"].push_back(yytext);}
{THROW}  { tokenLexemeMapping["THROW"].push_back(yytext);}
{TRUE}  { tokenLexemeMapping["TRUE"].push_back(yytext);}
{TRY}  { tokenLexemeMapping["TRY"].push_back(yytext);}
{TYPEOF}  { tokenLexemeMapping["TYPEOF"].push_back(yytext);}
{UINT}  { tokenLexemeMapping["UINT"].push_back(yytext);}
{ULONG}  { tokenLexemeMapping["ULONG"].push_back(yytext);}
{USING}  { tokenLexemeMapping["USING"].push_back(yytext);}
{VOID}  { tokenLexemeMapping["VOID"].push_back(yytext);}
{WHILE}  { tokenLexemeMapping["WHILE"].push_back(yytext);}
{ID}  { tokenLexemeMapping["ID"].push_back(yytext);}
{DINT_LITERAL}  { tokenLexemeMapping["DINT_LITERAL"].push_back(yytext);}
{HDINT_LITERAL}  { tokenLexemeMapping["HDINT_LITERAL"].push_back(yytext);}
{SIMPLE_ESC_SEQ}  { tokenLexemeMapping["SIMPLE_ESC_SEQ"].push_back(yytext);}
{CHAR_LITERAL}  { tokenLexemeMapping["CHAR_LITERAL"].push_back(yytext);}
{REG_STR_LITERAL}  { tokenLexemeMapping["REG_STR_LITERAL"].push_back(yytext);}
{VER_STR_LITERAL}  { tokenLexemeMapping["VER_STR_LITERAL"].push_back(yytext);}
{NULL_LITERAL}  { tokenLexemeMapping["NULL_LITERAL"].push_back(yytext);}
{LBRACE}  { tokenLexemeMapping["LBRACE"].push_back(yytext);}
{RBRACE}  { tokenLexemeMapping["RBRACE"].push_back(yytext);}
{LBRACKET}  { tokenLexemeMapping["LBRACKET"].push_back(yytext);}
{RBRACKET}  { tokenLexemeMapping["RBRACKET"].push_back(yytext);}
{LPARENTHESES}  { tokenLexemeMapping["LPARENTHESES"].push_back(yytext);}
{RPARENTHESES}  { tokenLexemeMapping["RPARENTHESES"].push_back(yytext);}
{DOT}  { tokenLexemeMapping["DOT"].push_back(yytext);}
{COMMA}  { tokenLexemeMapping["COMMA"].push_back(yytext);}
{COLON}  { tokenLexemeMapping["COLON"].push_back(yytext);}
{SEMICOLON}  { tokenLexemeMapping["SEMICOLON"].push_back(yytext);}
{PLUS}  { tokenLexemeMapping["PLUS"].push_back(yytext);}
{MINUS}  { tokenLexemeMapping["MINUS"].push_back(yytext);}
{STAR}  { tokenLexemeMapping["STAR"].push_back(yytext);}
{DIVIDE}  { tokenLexemeMapping["DIVIDE"].push_back(yytext);}
{MODULO}  { tokenLexemeMapping["MODULO"].push_back(yytext);}
{AMPERSAND}  { tokenLexemeMapping["AMPERSAND"].push_back(yytext);}
{OR}  { tokenLexemeMapping["OR"].push_back(yytext);}
{CARET}  { tokenLexemeMapping["CARET"].push_back(yytext);}
{EXCLAMATION}  { tokenLexemeMapping["EXCLAMATION"].push_back(yytext);}
{TILDE}  { tokenLexemeMapping["TILDE"].push_back(yytext);}
{EQUALS}  { tokenLexemeMapping["EQUALS"].push_back(yytext);}
{LESS_THAN}  { tokenLexemeMapping["LESS_THAN"].push_back(yytext);}
{GREATER_THAN}  { tokenLexemeMapping["GREATER_THAN"].push_back(yytext);}
{QUESTION_MARK}  { tokenLexemeMapping["QUESTION_MARK"].push_back(yytext);}
{DOUBLE_QM}  { tokenLexemeMapping["DOUBLE_QM"].push_back(yytext);}
{DOUBLE_COLON}  { tokenLexemeMapping["DOUBLE_COLON"].push_back(yytext);}
{INCREMENT}  { tokenLexemeMapping["INCREMENT"].push_back(yytext);}
{DECREMENT}  { tokenLexemeMapping["DECREMENT"].push_back(yytext);}
{REL_AND}  { tokenLexemeMapping["REL_AND"].push_back(yytext);}
{REL_OR}  { tokenLexemeMapping["REL_OR"].push_back(yytext);}
{REL_EQUALS}  { tokenLexemeMapping["REL_EQUALS"].push_back(yytext);}
{REL_NOT_EQ}  { tokenLexemeMapping["REL_NOT_EQ"].push_back(yytext);}
{LESS_EQUALS}  { tokenLexemeMapping["LESS_EQUALS"].push_back(yytext);}
{GREATER_EQUALS}  { tokenLexemeMapping["GREATER_EQUALS"].push_back(yytext);}
{ASSIGN_PLUS}  { tokenLexemeMapping["ASSIGN_PLUS"].push_back(yytext);}
{ASSIGN_MINUS}  { tokenLexemeMapping["ASSIGN_MINUS"].push_back(yytext);}
{ASSIGN_STAR}  { tokenLexemeMapping["ASSIGN_STAR"].push_back(yytext);}
{ASSIGN_DIV}  { tokenLexemeMapping["ASSIGN_DIV"].push_back(yytext);}
{ASSIGN_MOD}  { tokenLexemeMapping["ASSIGN_MOD"].push_back(yytext);}
{ASSIGN_AND}  { tokenLexemeMapping["ASSIGN_AND"].push_back(yytext);}
{ASSIGN_OR}  { tokenLexemeMapping["ASSIGN_OR"].push_back(yytext);}
{ASSIGN_CARET}  { tokenLexemeMapping["ASSIGN_CARET"].push_back(yytext);}
{LEFT_SHIFT}  { tokenLexemeMapping["LEFT_SHIFT"].push_back(yytext);}
{LEFT_SHIFT_EQ}  { tokenLexemeMapping["LEFT_SHIFT_EQ"].push_back(yytext);}
{RIGHT_SHIFT}  { tokenLexemeMapping["RIGHT_SHIFT"].push_back(yytext);}
{RIGHT_SHIFT_EQ}  { tokenLexemeMapping["RIGHT_SHIFT_EQ"].push_back(yytext);}
.	{yyerror();}

%%

void yyerror(void){
	cout << "Error in line: " << yylineno << endl;
	exit(1);
}

int main(int argc, char *argv[]){
	if(argc!=2){
		cerr << "Please specify an existing filename." << endl;	
		return 1;
	}
	string s;
	int flag = 0;
	yyin = fopen(argv[1], "r");
	yylex();
	cout << "===============================================================================\n";
	cout << setw(20) << "Tokens" << setw(15) << "Occurences" << setw(45) << "Lexemes\n";
	cout << "===============================================================================\n";
	map<string, vector<string> >::iterator it;
	int siz = 0;
	for (it = tokenLexemeMapping.begin(); it!=tokenLexemeMapping.end(); it++){
		siz = (*it).second.size();
		cout << setw(20) << (*it).first << setw(15) << siz;
		sort((*it).second.begin(), (*it).second.end());
		s = (*it).second[0];
		flag = 0;
		for (int i=1; i<siz; i++){
			if( (*it).second[i] != s){
				if(flag == 0){
					cout<<setw(45)<< s << endl ;
					flag = 1;
				}
				else
					cout << setw(80) << s <<endl;
				s = (*it).second[i];
			}
		}
		if(flag == 0)
			cout<<setw(45)<< s << endl ;
		else
			cout << setw(80) << s <<endl;
	}
	fclose(yyin);
	return 0;
}

