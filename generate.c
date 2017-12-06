// Anthony Gianino (AJG275)
// Project 1 - Part 4 - generate.c
// 12/5/17

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "y.tab.h"
#include "instr.h"
#include "code.h"
#include "ST.h"

extern int top;
struct NodeST* HeadST;
int curAddress = 0;

int addr_of(tree t) {return (4 * (t->value -1));}

static void gen_data(tree t) {
  int identCount = 0;
  for (t; t != NULL; t = t->next) {
    if (t->kind == Colon) {
      if (t->first->kind == Var) {
        tree tmp = t->first;
        tmp = tmp->first;
        for (; tmp != NULL; tmp = tmp->next) {
          int pos = tmp->value;
          if (HeadST->data[pos].index == 0) {
            identCount++;
            HeadST->data[pos].index = pos;
            HeadST->data[pos].address = curAddress;
            curAddress = curAddress + 4;
            if (t->second->kind == Int) {
              HeadST->data[pos].type = Integer;
            } else if (t->second->kind == Real) {
              HeadST->data[pos].type = RealConst;
            } else if (t->second->kind == Boolean) {
              HeadST->data[pos].type = Boolean;
            } else {
              HeadST->data[pos].type = NoType;
            }
          }
        }
      }
    }
  }

  if (identCount > 0) {
    pr_directive(".DATA\t");
    int i;
    for (i = 1; i <= top; i++) {
      char name[100]; sprintf(name, "%s", id_name(i));
      if(!isdigit(name[0]) && HeadST->data[i].index != 0) {
        char ident_addr[200];
        snprintf(ident_addr, 200, "%d: %s: ", HeadST->data[i].address, id_name(i));
        pr_directive(ident_addr);
      }
    }
    prNL();
    pr_directive(".CODE");
    prNL();
  }

  //curAddress = curAddress - (identCount * 4);
}

static void gen_expr(tree t)
{
  int n;
  if (t == NULL) {
    fprintf(stderr, "internal error: null expression tree\n");
  }
  switch(n = t->kind) {
    case Eq : case NotEq :
    case Lt : case Le : 
    case Gt : case Ge : {
        gen_expr(t->first);
        gen_expr(t->second);
        if (n == Gt || n == Le) {code(SWAPW);}
        code(SUBI);
        code((n == Eq || n == NotEq) ? TSTEQI : TSTLTI);
        if (n == NotEq || n == Le || n == Ge) {code(NOTW);}
      }
      break;
    case Plus : case Minus : 
    case Star : case Slash : 
    case Div  : {
        gen_expr(t->first); gen_expr(t->second);
        code(n == Plus ? ADDF : n == Minus ? SUBF : n == Star ? MULF : n == Slash ? DIVF : DIVI);
      }
      break;
    case Mod : {
        gen_expr(t->first); gen_expr(t->second);
        code(DUPL); code(DIVI); code(MULI); code(SUBI);
      }
      break;
    case And : case Or :
    case Not : {
        gen_expr(t->first);
        gen_expr(t->second);
        code(n == And ? ANDB : n == Or ? ORB : NOTB);
      }
      break;
    case Ident : {
        int pos = t->value;
        if (HeadST->data[pos].index == 0) {
          struct NodeST* tmp = HeadST;
          while (tmp->data[pos].index == 0 && tmp->next != NULL) {
            tmp = tmp->next;
          }
          code1(PUSHW, tmp->data[pos].address);
        } else {
          code1(PUSHW, HeadST->data[pos].address);
        }
        code(GETSW);
      }
      break;
    case Integer : {
        char intConst[200];
        snprintf(intConst, 200, "%i.0 ", t->value);
        code(PUSHW); pr_directive(intConst);
      }
      break;
    case RealConst : {
        char floatStr[50];
        snprintf(floatStr, 50, "%s", id_name(t->value));
        char realConst[200];
        float f = atof(floatStr);
        snprintf(realConst, 200, "%.2f ", f);
        code(PUSHW); pr_directive(realConst);
      }
      break;
    default :
      fprintf(stderr, "internal error: unknown expression\n");
  }
}

static void generate (tree t)
{
  for (t; t != NULL; t = t->next) {
    switch(t->kind) {
      case Prog : {
          {STentry NewST[100];
          push(&HeadST, NewST);
          int i;
          for (i = 0; i < 100; i++) {
            HeadST->data[i].index = 0;
            HeadST->data[i].address = 0;
            HeadST->data[i].type = NoType;
            int j;
            for (j = 0; j < 100; j++) {
              HeadST->data[i].fields[j].index = 0;
              HeadST->data[i].fields[j].type = NoType;
            }
          }}
          gen_data(t->first);
          generate(t->first);
        }
        break;
      case Colon : {}
        break;
      case ColonEq : {
          prLC();
          tree tmp1 = t->first;
          int pos = tmp1->value;
          if (HeadST->data[pos].index == 0) {
            struct NodeST* tmp2 = HeadST;
            while (tmp2->data[pos].index == 0 && tmp2->next != NULL) {
              tmp2 = tmp2->next;
            }
            code1(PUSHW, tmp2->data[pos].address);
          } else {
            code1(PUSHW, HeadST->data[pos].address);
          }
          gen_expr(t->second);
          code(PUTSW);
          prNL();
        }
        break;
      case Assert : {
          struct FR fix1;
          prLC();
          gen_expr(t->first);
          code(NOTW);
          fix1 = codeFR(RGOZ);
          fixFR(fix1, LC+1);
          code(HALT);
          prNL();
        }
        break;
      case If : {
          struct FR fix1, fix2;
          prLC();
          gen_expr(t->first);
          fix1 = codeFR(RGOZ);
          prNL();
          generate(t->second);
          if (t->third != NULL) {
            prLC();
            fix2 = codeFR(RGOTO);
            fixFR(fix1, LC);
            prNL();
            generate(t->third);
            fixFR(fix2, LC);
          } else {
            fixFR(fix1, LC);
          }
        }
        break;
      case ElsIf : {
          struct FR fix1;
          prLC();
          gen_expr(t->first);
          fix1 = codeFR(RGOZ);
          prNL();
          generate(t->second);
          fixFR(fix1, LC);
        }
        break;
      case Then : case Else : {
          {STentry NewST[100];
          push(&HeadST, NewST);
          int i;
          for (i = 0; i < 100; i++) {
            HeadST->data[i].index = 0;
            HeadST->data[i].address = 0;
            HeadST->data[i].type = NoType;
            int j;
            for (j = 0; j < 100; j++) {
              HeadST->data[i].fields[j].index = 0;
              HeadST->data[i].fields[j].type = NoType;
            }
          }}
          gen_data(t->first);
          generate(t->first);
          pop(&HeadST, HeadST);
        }
        break;
      case Begin : {
          {STentry NewST[100];
          push(&HeadST, NewST);
          int i;
          for (i = 0; i < 100; i++) {
            HeadST->data[i].index = 0;
            HeadST->data[i].address = 0;
            HeadST->data[i].type = NoType;
            int j;
            for (j = 0; j < 100; j++) {
              HeadST->data[i].fields[j].index = 0;
              HeadST->data[i].fields[j].type = NoType;
            }
          }}
          gen_data(t->first);
          generate(t->first);
          pop(&HeadST, HeadST);
        }
        break;
      case Loop: {
          {STentry NewST[100];
          push(&HeadST, NewST);
          int i;
          for (i = 0; i < 100; i++) {
            HeadST->data[i].index = 0;
            HeadST->data[i].address = 0;
            HeadST->data[i].type = NoType;
            int j;
            for (j = 0; j < 100; j++) {
              HeadST->data[i].fields[j].index = 0;
              HeadST->data[i].fields[j].type = NoType;
            }
          }}
          struct FR fix1;
          gen_data(t->first);
          int start = LC;
          generate(t->first);
          prLC();
          code1(RGOTO, start - (LC+3));
          prNL();
          pop(&HeadST, HeadST);
        }
        break;
      case Exit : {
          if (t->first->kind == When) {
            struct FR fix1;
            prLC();
            tree tmp = t->first;
            gen_expr(tmp->first);
            fix1 = codeFR(RGOZ);
            fixFR(fix1, LC+3);
            prNL();
          }
        }
        break;
      default :
        fprintf(stderr, "internal error: bad node\n");
    }
  }
}

void gen_program(tree t)
{
  generate(t);
  prLC();
  pr_directive("HALT .ENTRY 0");
  prNL();
}
