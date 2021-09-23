#include <stdlib.h>
typedef int Element;

typedef struct {
    Element *stack;
    int size;
    int top;
} int_Stack, *p_intStack;

int_Stack *init_Stack(int size) {
    p_intStack pStack = (p_intStack) malloc(sizeof(int_Stack));

    if (pStack==NULL) {
        return NULL;
    }

    pStack->stack=(Element*) malloc(sizeof(Element)*size);

    if (pStack->size==NULL) {
        free(pStack);
        return NULL;
    }


    pStack->size=size;
    pStack->top=-1;

    return pStack;
}

int isFullStack(p_intStack p) {
    if (p->size==((p->top)+1)) {
        return 1;//참
    }
    return 0;
}

int isEmptyStack (p_intStack p) {
    return (p->top==-1)?1:0;
}

int CountStackItem (p_intStack p) {
    return (p->top)+1;
}

void push(p_intStack p,Element item) {
    if (isFullStack(p)) {
    }
    else {
        p->stack[++(p->top)]=item;
    }
}

Element pop(p_intStack p) {
    if (isEmptyStack(p)) {

    }
    else {
        return p->stack[(p->top)--];
    }
}

Element top(p_intStack p) {
    return p->stack[p->top];
}

void destroyStack (p_intStack p) {
    if (p->size>0) {
        free(p->stack);
    }
    free(p);
}

void clearStack (p_intStack p) {
    p->top=-1;
}