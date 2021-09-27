#include <stdlib.h>
#include <stdio.h>
typedef int Element;

typedef struct {
    Element *stack;
    int size;
    int top;
} int_Stack, *int_pStack;

int_Stack *init_Stack(int size) {
    int_pStack pStack = (int_pStack) malloc(sizeof(int_Stack));

    if (pStack==NULL) {
        return NULL;
    }

    pStack->stack=(Element*) malloc(sizeof(Element)*size);

    if (pStack->stack==NULL) {
        free(pStack);
        return NULL;
    }


    pStack->size=size;
    pStack->top=-1;

    return pStack;
}

int int_isFullStack(int_pStack p) {
    if (p->size==((p->top)+1)) {
        return 1;//참
    }
    return 0;
}

int int_isEmptyStack (int_pStack p) {
    return (p->top==-1)?1:0;
}

int int_CountStackItem (int_pStack p) {
    return (p->top)+1;
}

void int_push(int_pStack p,Element item) {
    if (int_isFullStack(p)) {
        printf("\n stack is full \n");
    }
    else {
        p->stack[++(p->top)]=item;
    }
}

Element int_pop(int_pStack p) {
    if (int_isEmptyStack(p)) {
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

Element int_top(int_pStack p) {
    return p->stack[p->top];
}

void int_delete_stack (int_pStack p) {
    if (p->size>0) {
        free(p->stack);
    }
    free(p);
}

void int_clearStack (int_pStack p) {
    p->top=-1;
}