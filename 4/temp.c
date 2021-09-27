#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack_Link2.h"


void change10_to_nfix(int p,int n,char* inp) {
    pStack st=createStack(100);
    char temp[30];
    int count=0;
    int dived=0;
    while (p!=0) {
        dived=p%n;
        if (dived>=0 && dived<=9) {
            push(p,'0'+dived);
        }
        else {
            push(p,'A'+(dived-10));
        }
        p=p/12;
    }

    while (!int_isEmptyStack(st)) {
        inp[count++]=pop(p);
    }
    inp[count]='\0';
    delete_stack(st);
    
}

int main(void) {
    char temp[20];
    change10_to_nfix(10,12,temp);
    printf("%s\n",temp);
    return 0;
}