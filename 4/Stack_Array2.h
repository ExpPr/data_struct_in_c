#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef char element;

typedef struct {
    element *stack;
    int size;
    int top;
} Stack, *pStack;

Stack *createStack(int size) {
    pStack p = (pStack) malloc(sizeof(Stack));

    if (p==NULL) {
        return NULL;
    }

    p->stack=(element*) malloc(sizeof(element)*size);

    if (p->stack==NULL) {
        free(p);
        return NULL;
    }


    p->size=size;
    p->top=-1;

    return p;
}

int isFullStack(pStack p) {
    if (p->size==((p->top)+1)) {
        return 1;//참
    }
    return 0;
}

int isEmptyStack (pStack p) {
    return (p->top==-1)?1:0;
}

int CountStackItem (pStack p) {
    return (p->top)+1;
}

void push(pStack p,element item) {
    if (isFullStack(p)) {
        printf("\n stack is full \n");
    }
    else {
        p->stack[++(p->top)]=item;
    }
}

element pop(pStack p) {
    if (isEmptyStack(p)) {
      if (p->size>0) {
        free(p->stack);
      }
      free(p);
      exit(1);
    }
    else {
        return p->stack[(p->top)--];
    }
}

element top(pStack p) {
    return p->stack[p->top];
}

void delete_stack (pStack p) {
    if (p->size>0) {
        free(p->stack);
    }
    free(p);
}

void clearStack (pStack p) {
    p->top=-1;
}