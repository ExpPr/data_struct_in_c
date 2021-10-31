#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int element;

typedef struct int_tStackNode {
    element data;
    struct int_tStackNode *next;
} int_StackNode, *int_pStackNode;

typedef struct {
    int count;
    int_StackNode *top;
} int_Stack, *int_pStack;


int_pStack init_Stack(int size) {
    int_pStack p=(int_pStack)malloc(sizeof(int_Stack));
    if (p==NULL) {
        return NULL;
    }
    p->count=0;
    p->top=NULL;
    return p;
}

int int_isEmptyStack(int_pStack p) {
    return (p->count==0)?1:0;
}


bool int_push(int_pStack p,element item) {
    int_pStackNode pNew=(int_pStackNode)malloc(sizeof(int_StackNode));
    if (pNew==NULL) {
        printf("\n Appropriate memory allocation is not made. \n");
        return false;
    }
    pNew->data=item;
    pNew->next=p->top;
    p->top=pNew;
    p->count++;
    return true;
}

element int_pop(int_pStack p) {
    if (int_isEmptyStack(p)) {
        printf("\n stack is empty \n");
        while (p->top!=NULL) {
        int_pop(p);
        }
        free(p);
        exit(1);
    }
    else {
        element r=(p->top)->data;
        int_pStackNode dltPtr=p->top;
        p->top=(p->top)->next;
        --p->count;
        free(dltPtr);
        return r;
    }
}

element int_top(int_pStack p) {
    if (int_isEmptyStack(p)) {
        printf("\n stack is empty \n");
    } else {
        return p->top->data;
    }
}

void int_delete_stack(int_pStack p) {
    while (p->top!=NULL) {
        int_pop(p);
    }
    free(p);
}

void int_clearStack(int_pStack p) {
    while (p->top!=NULL) {
        int_pop(p);
    }
}

int int_CountStackItem(int_pStack p) {
    return p->count;
}