#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
typedef char* Element;

typedef struct tpStackNode {
    Element data;
    struct tpStackNode *next;
} str_StackNode, *str_pStackNode;

typedef struct {
    int count;
    str_StackNode *top;
} str_Stack, *str_pStack;


str_pStack str_createStack(int size) {
    str_pStack p=(str_pStack)malloc(sizeof(str_Stack));
    if (p==NULL) {
        return NULL;
    }
    p->count=0;
    p->top=NULL;
    return p;
}

int str_isEmptyStack(str_pStack p) {
    return (p->count==0)?1:0;
}


void str_push(str_pStack p,Element item) {
    str_pStackNode pNew=(str_pStackNode)malloc(sizeof(str_StackNode));
    if (pNew==NULL) {
        printf("\n Appropriate memory allocation is not made. \n");
        return;
    }
    pNew->data=(Element)malloc(sizeof(char)*(strlen(item)+1));
    strcpy(pNew->data,item);
    pNew->next=p->top;
    p->top=pNew;
    p->count++;
}

Element str_pop(str_pStack p) {
    if (str_isEmptyStack(p)) {
        printf("\nStack is empty\n");
        return NULL;
    }
    else {
        Element r=(Element)malloc(sizeof(char)*(strlen(p->top->data)+1));
        strcpy(r,p->top->data);
        str_pStackNode dltPtr=p->top;
        p->top=(p->top)->next;
        --p->count;
        free(dltPtr->data);
        free(dltPtr);
        return r;
    }
}

Element str_top(str_pStack p) {
    if (str_isEmptyStack(p)) {
        printf("\nstack is empty\n");
        return NULL;
    } else {
        return p->top->data;
    }
}


void str_clearStack(str_pStack p) {
    while (p->count>0) {
    str_pStackNode dltPtr=p->top;
        p->top=(p->top)->next;
        --p->count;
        free(dltPtr->data);
        free(dltPtr);
    }
}

void str_delete_stack(str_pStack p) {
    str_clearStack(p);
    free(p);
}



int countStackItem(str_pStack p) {
    return (p->count);
}

void str_printAll(str_pStack p) {
  printf("STACK Stat : ");
  
  if (str_isEmptyStack(p)) {
    printf("Empty");
  }
  else {
  str_pStackNode temp =p->top;
  do {
    printf("%s ",temp->data);
    temp=temp->next;
  } while (temp!=NULL);
  }
}