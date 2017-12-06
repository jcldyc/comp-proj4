// Anthony Gianino (AJG275)
// Project 1 - Part 4 - tree.c
// 10/29/17

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "y.tab.h"

char *id_name (int);

tree buildTree(int kind, tree one, tree two, tree three)
{
   tree p = (tree)malloc(sizeof(node));
   p->kind = kind;
   p->first = one;
   p->second = two;
   p->third = three;
   p->next = NULL;
   return p;
}

tree buildIntTree(int kind, int val)
{
   tree p = (tree)malloc(sizeof(node));
   p->kind = kind;
   p->value = val;
   p->first = p->second = p->third = NULL;
   p->next = NULL;
   return p;
}

char TokName[][12] = 
{"<eof>",
"Ident", "Integer", "RealConst", "", "", "", "", "", "", "",
"var", "int", "real", "boolean", "record", "end", "bind", "to", "assert", "begin",
"loop", "exit", "when", "if", "then", "elsif", "else", "put", "or", "and",
"Not", "NotEq", "div", "mod", "", "", "", "", "", "",
";", ":", ":=", "<", ">", "=", "<=", ">=", "+", "-",
"*", "/", ".", ",", "(", ")", "<prog>", "", "", "",
"NoType"};

static int indent = 0;

void printTree(tree p)
{
   if (p == NULL) return;
   for (; p != NULL; p = p->next) {
      printf("%*s%s", indent, "", TokName[p->kind]);
      switch(p->kind) {
         case Ident:
            printf("  %s (%d)\n", id_name(p->value), p->value);
            break;
         case Integer:
            printf("  %d\n", p->value);
            break;
         case RealConst:
            printf("  %s\n", id_name(p->value));
            break;
         default:
            printf("\n");
            indent += 2;
            printTree(p->first);
            printTree(p->second);
            printTree(p->third);
            indent -= 2;
      }
   }
}

