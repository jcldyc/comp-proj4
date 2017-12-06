%{
// Anthony Gianino (AJG275)
// Project 1 - Part 4 - .y file
// 11/24/17 
#include "tree.h"
#include <stdlib.h>

extern tree root;
%}

%token <i> Ident 1 Integer 2 RealConst 3
%token Var 11 Int 12 Real 13 Boolean 14 Record 15 End 16 Bind 17 To 18 Assert 19 Begin 20
%token Loop 21 Exit 22 When 23 If 24 Then 25 ElsIf 26 Else 27 Put 28 Or 29 And 30
%token Not 31 NotEq 32 Div 33 Mod 34
%token Semicolon 41 Colon 42 ColonEq 43 Lt 44 Gt 45 Eq 46 Le 47 Ge 48 Plus 49 Minus 50
%token Star 51 Slash 52 Dot 53 Comma 54 LParen 55 RParen 56 Prog 57
%token NoType 61

%start program

%union { tree p; int i; }

%type <p> pStateDeclSeq idList type fieldList stateDecls declaration statement ref endIf
%type <p> expr andExpr notExpr relExpr sum prod factor basic

%%
program
	: pStateDeclSeq
		{ root = buildTree(Prog, $1, NULL, NULL); }
	;
pStateDeclSeq
	: /* empty */
		{ $$ = NULL; }
	| statement Semicolon pStateDeclSeq
		{ $$ = $1; $$->next = $3; }
	| Var idList Colon type Semicolon pStateDeclSeq
		{ $$ = buildTree(Colon, buildTree(Var, $2, NULL, NULL), $4, NULL); $$->next = $6; }
	;
idList
	: Ident
		{ $$ = buildIntTree(Ident, $1); }
	| Ident Comma idList
		{ $$ = buildIntTree(Ident, $1); $$->next = $3; }
	;
type
	: Int
		{ $$ = buildTree(Int, NULL, NULL, NULL); }
	| Real
		{ $$ = buildTree(Real, NULL, NULL, NULL); }
	| Boolean
		{ $$ = buildTree(Boolean, NULL, NULL, NULL); }
	| Record fieldList End Record
		{ $$ = buildTree(Record, $2, NULL, NULL); }
	;
fieldList
	: idList Colon type
		{ $$ = buildTree(Colon, $1, $3, NULL); }
	| idList Colon type Semicolon fieldList
		{ $$ = buildTree(Colon, $1, $3, NULL); $$->next = $5; }
	;
stateDecls
	: /* empty */
		{ $$ = NULL; }
	| statement Semicolon stateDecls
		{ $$ = $1; $$->next = $3; }
	| declaration Semicolon stateDecls
		{ $$ = $1; $$->next = $3; }
declaration
	: Var idList Colon type
		{ $$ = buildTree(Colon, buildTree(Var, $2, NULL, NULL), $4, NULL); }
	| Bind idList To ref
		{ $$ = buildTree(Bind, $2, $4, NULL); }
	| Bind Var idList To ref
		{ $$ = buildTree(Bind, buildTree(Var, $3, NULL, NULL), $5, NULL); }
	;
statement
	: ref ColonEq expr
		{ $$ = buildTree(ColonEq, $1, $3, NULL);}
	| Assert expr
		{ $$ = buildTree(Assert, $2, NULL, NULL); }
	| Begin stateDecls End
		{ $$ = buildTree(Begin, $2, NULL, NULL); }
	| Loop stateDecls End Loop
		{ $$ = buildTree(Loop, $2, NULL, NULL); }
	| Exit
		{ $$ = buildTree(Exit, NULL, NULL, NULL); }
	| Exit When expr
		{ $$ = buildTree(Exit, buildTree(When, $3, NULL, NULL), NULL, NULL); }
	| If expr Then stateDecls endIf
		{ $$ = buildTree(If, $2, buildTree(Then, $4, NULL, NULL), $5); }
	;
ref
	: Ident
		{ $$ = buildIntTree(Ident, $1);  }
	| Ident Dot Ident
		{ $$ = buildTree(Dot, buildIntTree(Ident, $1), buildIntTree(Ident, $3), NULL); }
	;
endIf
	: End If
		{ $$ = buildTree(End, NULL, NULL, NULL); }
	| Else stateDecls End If
		{ $$ = buildTree(Else, $2, NULL, NULL); }
	| ElsIf expr Then stateDecls endIf
		{ $$ = buildTree(ElsIf, $2, buildTree(Then, $4, NULL, NULL), NULL); $$->next = $5; }
	;
expr
	: expr Or andExpr
		{ $$ = buildTree(Or, $1, $3, NULL); }
	| andExpr
		{ $$ = $1; }
	;
andExpr
	: andExpr And notExpr
		{ $$ = buildTree(And, $1, $3, NULL); }
	| notExpr
		{ $$ = $1; }
	;
notExpr
	: Not notExpr
		{$$ = buildTree(Not, $2, NULL, NULL); }
	| relExpr
		{ $$ = $1; }
	;
relExpr
	: sum
		{ $$ = $1; }
	| relExpr Eq sum
		{ $$ = buildTree(Eq, $1, $3, NULL); }
	| relExpr NotEq sum
		{ $$ = buildTree(NotEq, $1, $3, NULL); }
	| relExpr Lt sum
		{ $$ = buildTree(Lt, $1, $3, NULL); }
	| relExpr Le sum
		{ $$ = buildTree(Le, $1, $3, NULL); }
	| relExpr Gt sum
		{ $$ = buildTree(Gt, $1, $3, NULL); }
	| relExpr Ge sum
		{ $$ = buildTree(Ge, $1, $3, NULL); }
	;
sum
	: prod
		{ $$ = $1; }
	| sum Plus prod
		{ $$ = buildTree(Plus, $1, $3, NULL); }
	| sum Minus prod
		{ $$ = buildTree(Minus, $1, $3, NULL); }
	;
prod
	: factor
		{ $$ = $1; }
	| prod Star factor
		{ $$ = buildTree(Star, $1, $3, NULL); }
	| prod Slash factor
		{ $$ = buildTree(Slash, $1, $3, NULL); }
	| prod Div factor
		{ $$ = buildTree(Div, $1, $3, NULL); }
	| prod Mod factor
		{ $$ = buildTree(Mod, $1, $3, NULL); }
	;
factor
	: Plus basic
		{ $$ = buildTree(Plus, $2, NULL, NULL); }
	| Minus basic
		{ $$ = buildTree(Minus, $2, NULL, NULL); }
	| basic
		{ $$ = $1; }
	;
basic
	: ref 
		{ $$ = $1; }
	| LParen expr RParen
		{ $$ = $2; }
	| Integer
		{ $$ = buildIntTree(Integer, $1); }
	| RealConst
		{ $$ = buildIntTree(RealConst, $1); }
	;
%%
