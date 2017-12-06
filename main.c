// Anthony Gianino (AJG275)
// Project 1 - Part 4 - main.c
// 12/3/17

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

extern FILE *yyin;
tree root;
FILE *outfile;

void main(int argc, char **argv)
{
   if (argc != 3) {
      fprintf(stderr, "%s: insufficient arguments\n", argv[0]);
      exit(1);
   }

   if ((yyin = fopen(argv[1], "r")) == 0L) {
      fprintf(stderr, "%s: can't open input file '%s'\n", argv[0], argv[1]);
      exit(1);
   }
   yyparse();
   //printTree(root);

   check(root);
   
   close(yyin);
   if ((yyin = fopen(argv[1], "r")) == 0L) {
      fprintf(stderr, "%s: can't open input file '%s'\n", argv[0], argv[1]);
      exit(1);
   }
   yyparse();

   if ((outfile = fopen (argv[2], "w")) == 0L) {
      fprintf (stderr, "%s: can't open outfile file '%s'\n", argv[0], argv[2]);
      exit(1);
   }
   gen_program (root);

   close(outfile);
   close(yyin);
}

