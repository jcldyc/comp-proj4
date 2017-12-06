%{
// Anthony Gianino (AJG275)
// Project 1 - Part 4 - .l file
// 11/25/17
#include <stdio.h>
#include <string.h>
#include "tree.h"
#include "y.tab.h"

void yyerror (char * s);
int line = 1;
int pos = 1;
%}

ID	[a-zA-Z][a-zA-Z0-9_]*
INTEGER	[0-9]+
REAL	([0-9]+"."[0-9]+)|([0-9]+"."[0-9]+("E+"|"e+"|"E-"|"e-")[0-9]+)|([0-9]+("E+"|"e+"|"E-"|"e-")[0-9]+)|([0-9]+"."[0-9]+("E+"|"e+"|"E-"|"e-")[0-9]+"."[0-9]+)|([0-9]+("E+"|"e+"|"E-"|"e-")[0-9]+"."[0-9]+)

%%
{INTEGER}	{pos += yyleng; yylval.i = atoi(yytext); return Integer;}
{REAL}		{pos += yyleng; yylval.i = lookup(yytext); return RealConst;}
"var"		{pos += 3; return Var;}
"int"		{pos += 3; return Int;}
"real"		{pos += 4; return Real;}
"boolean"	{pos += 7; return Boolean;}
"record"	{pos += 6; return Record;}
"end"		{pos += 3; return End;}
"bind"		{pos += 4; return Bind;}
"to"		{pos += 2; return To;}
"assert"	{pos += 6; return Assert;}
"begin"		{pos += 5; return Begin;}
"loop"		{pos += 4; return Loop;}
"exit"		{pos += 4; return Exit;}
"when"		{pos += 4; return When;}
"if"		{pos += 2; return If;}
"then"		{pos += 4; return Then;}
"elsif"		{pos += 5; return ElsIf;}
"else"		{pos += 4; return Else;}
"put"		{pos += 3; return Put;}
"or"		{pos += 2; return Or;}
"and"		{pos += 3; return And;}
"not"		{pos += 3; return Not;}
"not="		{pos += 4; return NotEq;}
"div"		{pos += 3; return Div;}
"mod"		{pos += 3; return Mod;}
";"		{pos++; return Semicolon;}
":"		{pos++; return Colon;}
":="		{pos += 2; return ColonEq;}
"<"		{pos++; return Lt;}
">"		{pos++; return Gt;}
"="		{pos++; return Eq;}
"<="		{pos += 2; return Le;}
">="		{pos += 2; return Ge;}
"+"		{pos++; return Plus;}
"-"		{pos++; return Minus;}
"*"		{pos++; return Star;}
"/"		{pos++; return Slash;}
"."		{pos++; return Dot;}
","		{pos++; return Comma;}
"("		{pos++; return LParen;}
")"		{pos++; return RParen;}
{ID}		{pos += yyleng; yylval.i = lookup(yytext); return Ident;}
[ \t]		{pos++;}
[\n]		{line++; pos = 1;}
.		{pos += yyleng; yyerror("Unknown character");}
%%

int yywrap (void) {return 1;}
void yyerror (char s[]) {
   printf("Error: %s: '%s' at line %d, position %d\n", s, yytext, line, pos);
}

typedef char name[15];
static char Names[200][15] = {"<none>"};
int top = 0;

int lookup (char s[])
{
   int i;
   for (i = 1; i <= top; i++)
      if (strcmp(s, Names[i]) == 0) return i;
   strcpy(Names[++top], s);
   return top;
}

void printNames (void)
{
   int i = 0;
   for (; i <= top; i++)
      printf("%d\t%s\n", i, Names[i]);
}

char *id_name (int i)
{
   return Names[i];
}

