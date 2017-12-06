// Anthony Gianino (AJG275)
// Project 1 - Part 4 - code.h
// 11/30/17

struct FR {
  long filep;
  int  LChere;
};

void code (int opcode), code1 (int opcode, int arg);
struct FR codeFR (int opcode);
void fixFR (struct FR here, int lc);
void prNL (void);

extern FILE *outfile;
extern int LC;

