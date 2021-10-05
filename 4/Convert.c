#include "Stack_Link.h"
#include <stdio.h>

int main(void) {
    int in,mod;
    printf("Enter a number : ");
    scanf("%d",&in);
    int copy=in;

    int_pStack p=init_Stack(100);

    while (in!=0) {
        mod=in%2;
        in/=2;
        int_push(p,mod);   
    }

    printf("The binary number of %d : ",copy);
    while (!int_isEmptyStack(p)) {
        printf("%d",int_pop(p));
    }
    int_delete_stack(p);
    return 0;
}