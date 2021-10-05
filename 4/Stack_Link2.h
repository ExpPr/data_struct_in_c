#include <stdlib.h>
#include <stdio.h>
typedef char Element;

typedef struct tStackNode {
    Element data;
    struct tStackNode *next;
} StackNode, *pStackNode;

typedef struct {
    int count;
    StackNode *top;
} Stack, *pStack;


pStack createStack(int size) {
    pStack p=(pStack)malloc(sizeof(Stack));
    if (p==NULL) {
        return NULL;
    }
    p->count=0;
    p->top=NULL;
    return p;
}

int isEmptyStack(pStack p) {
    return (p->count==0)?1:0;
}


void push(pStack p,Element item) {
    pStackNode pNew=(pStackNode)malloc(sizeof(StackNode));
    if (pNew==NULL) {
        printf("\n Appropriate memory allocation is not made. \n");
        return;
    }
    pNew->data=item;
    pNew->next=p->top;
    p->top=pNew;
    p->count++;
}

Element pop(pStack p) {
    if (isEmptyStack(p)) {
        printf("\nStack is empty\n");
        free(p);
        exit(1);
    }
    else {
        Element r=(p->top)->data;
        pStackNode dltPtr=p->top;
        p->top=(p->top)->next;
        --p->count;
        free(dltPtr);
        return r;
    }
}

Element top(pStack p) {
    if (isEmptyStack(p)) {
        printf("\nstack is empty\n");
        return '\0';
    } else {
        return p->top->data;
    }
}

void delete_stack(pStack p) {
    while (p->top!=NULL) {
        pop(p);
    }
    free(p);
}

void clearStack(pStack p) {
    while (p->top!=NULL) {
        pop(p);
    }
}

int countStackItem(pStack p) {
    return (p->count);
}

void printAll(pStack p) {
  printf("STACK Stat : ");
  
  if (isEmptyStack(p)) {
    printf("Empty");
  }
  else {
  pStackNode temp =p->top;
  do {
    printf("%c",temp->data);
    temp=temp->next;
  } while (temp!=NULL);
  }
}