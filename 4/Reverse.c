#include <stdio.h>
#include <stdlib.h>
#include "Stack_LinkedList.h"

int main(void) {
    int sp;
    int_pStack p=init_Stack();

    while (1) {
        int verification=0;
        printf("Enter a number : <Ctrl + D> to stop : ");
        verification=scanf("%d",&sp);

        if (verification!=1) {
            break;
        }
        push(p,sp);
    }
    

    while (!isEmptyStack(p)) {
        printf("%d\n",pop(p));
    }

    delete_stack(p);
    return 0;
}