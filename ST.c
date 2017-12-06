// Anthony Gianino (AJG275)
// Project 1 - Part 4 - ST.c
// 12/5/17

#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

void push(struct NodeST** head_ref, STentry* new_data)
{
  struct NodeST* new_node = (struct NodeST*)malloc(sizeof(struct NodeST));
  //new_node->data = malloc(sizeof(STentry));
  new_node->next = (*head_ref);
  new_node->prev = NULL;

  if((*head_ref) != NULL) {
    (*head_ref)->prev = new_node;
  }

  (*head_ref) = new_node;

  new_node->data = new_data;

  return;
}

void pop(struct NodeST **head_ref, struct NodeST *del)
{
  if (*head_ref == NULL || del == NULL) { return; }
  if (*head_ref == del) { *head_ref = del->next; }
  if (del->next != NULL) { del->next->prev = del->next; }
  if (del->prev != NULL) { del->prev->next = del->next; }
  
  free(del);

  return;
}

extern STentry ST[];

