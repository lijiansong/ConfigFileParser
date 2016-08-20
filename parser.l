%{
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include"parser.tab.h"

%}
%option noyywrap
%option yylineno

%%
[ \t]	;
[\n]	;
[0-9]+	{yylval.sval=new std::string(yytext); return INT;}
[+-]?[0-9]+(\.[0-9]*)? { yylval.sval = new std::string(yytext); return FLOAT; }
\"(\\.|[^\\"])*\"  { yylval.sval = new std::string(yytext); return STRING; }
[a-z_][a-z0-9_\.]*   { yylval.sval = new std::string(yytext); return ID; }
"{"	{ return LB; }
"}"	{ return RB; }
":"	{ return COLON; }
"="	{ return EQ; }
";"	{ return END; }
"NULL"	{ return NULLV; }
"//".*	;
"/*"{
	int c;
	for(;;)
	{
		while((c=yyinput())!='*'&&c!=EOF);
		if(c=='*')
		{
			while((c=yyinput())=='*');
			if(c=='/')
				break;
		}
		if(c==EOF)
		{
			unput(c);
			break;
		}
	}
}

%%
