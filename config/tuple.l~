/**
 * Copyright (c) 2012 The Tupler Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file. See the AUTHORS file for names of contributors.
 *
 * Author: Hector Gonzalez (hagonzal@gmail.com)
 */

%{
#include <iostream>
#include <cstdlib>

#include "config/tuple.tab.h"

%}

%option noyywrap
%option yylineno

%%

[ \t]              ;
[\n]               ;
[0-9]+             { yylval.sval = new std::string(yytext); return INT; }
[+-]?[0-9]+(\.[0-9]*)? { yylval.sval = new std::string(yytext); return FLOAT; }
\"(\\.|[^\\"])*\"  { yylval.sval = new std::string(yytext); return STRING; }
[a-z_][a-z0-9_\.]*   { yylval.sval = new std::string(yytext); return ID; }
"{"                { return LB; }
"}"                { return RB; }
":"                { return COLON; }
"="                { return EQ; }
";"                { return END; }
"NULL"             { return NULLV; }
"//".*             ;

"/*" {
  int c;
  for ( ; ; ) {
    while ( (c = yyinput()) != '*' && c != EOF ) {
      /* eat up text of comment */
    }

    if ( c == '*' ) {
      while ( (c = yyinput()) == '*' ) {
      }

      if ( c == '/' ) {
        break;    /* found the end */
      }
    }

    if ( c == EOF ) {
      unput(c);
      break;
    }
  }
}

%%
