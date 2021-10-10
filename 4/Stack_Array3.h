#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef char* element;

typedef struct {
    element *str_stack;
    int size;
    int top;
} str_stack, *str_pstack;

str_stack *str_createstack(int size) {
    str_pstack p = (str_pstack) malloc(sizeof(str_stack));

    if (p==NULL) {
        return NULL;
    }

    p->str_stack=(element*) malloc(sizeof(element)*size);

    if (p->str_stack==NULL) {
        free(p);
        return NULL;
    }

    for (int i=0;i<size;i++) {
        p->str_stack[i]=(element)malloc(sizeof(char)*1);
        p->str_stack[i][0]='\0';
    }


    p->size=size;
    p->top=-1;

    return p;
}

int str_isFullstack(str_pstack p) {
    if (p->size==((p->top)+1)) {
        return 1;//참
    }
    return 0;
}

int str_isEmptystack (str_pstack p) {
    return (p->top==-1)?1:0;
}

int str_CountstackItem (str_pstack p) {
    return (p->top)+1;
}

void str_push(str_pstack p,element item) {
    if (str_isFullstack(p)) {
        printf("\n str_stack is full \n");
    }
    else {
        int len=strlen(item)+1;
        if (len!=strlen(p->str_stack[++p->top])) {
        p->str_stack[p->top]=(element)realloc(p->str_stack[p->top],sizeof(char)*len); }
        strcpy( p->str_stack[p->top],item);
    }
}

element str_pop(str_pstack p) {
    if (str_isEmptystack(p)) {
      printf("stack is empty\n");
      return NULL;
    }
    else {
        return p->str_stack[(p->top)--];
    }
}

element str_top(str_pstack p) {
    return p->str_stack[p->top];
}

void str_delete_str_stack (str_pstack p) {
    if (p->size>0) {
        for (element dlt=p->str_stack[p->top];p->top>-1;p->top--) {
            free(dlt);
        }
        free(p->str_stack);
    }
    free(p);
}

void str_clearstr_stack (str_pstack p) {
    p->top=-1;
}