// Anthony Gianino (AJG275)
// Project 1 - Part 4 - tree.h
// 10/29/17

typedef struct Node {
   int		kind, value;
   struct	Node *first, *second, *third, *next;
} node;
typedef node	*tree;

extern char TokName[][12];

tree buildTree (int, tree, tree, tree);
tree buildIntTree (int, int);
void printTree (tree);

