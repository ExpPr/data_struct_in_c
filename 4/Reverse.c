#include <stdio.h>
#include <stdlib.h>
#include "Stack_Link.h"

int main(void) {
    int sp;
    int_pStack p=init_Stack();

    while (1) {
        int verification=0;
        printf("Enter a number : <Ctrl + D> to stop : ");
        verification=scanf("%d",&sp);
        rewind(stdin);
        if (verification!=1) {
            break;
        }
        int_push(p,sp);
    }
    
    printf("\nThe List of Numbers reversed : \n");
    while (!int_isEmptyStack(p)) {
        printf("%d\n",int_pop(p));
    }

    int_delete_stack(p);
    return 0;
}