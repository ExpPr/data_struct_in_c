#include "Queue_Link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main_select() {
    printf("In(0), Out(1) , Exit(2) : ");
    int result;
    scanf("%d",&result);
    getchar();
    return result;
}

void select_one(pQueue p) {
    printf("Customer : ");
    char *name=(char*)malloc(sizeof(char)*50);
    scanf("%[^\n]",name);
    name[strlen(name)]='\0';
    Enqueue(p,name);
    getchar();//\n처리

    printf("The current status of Queue : ");
    printQueue(p);
}

void select_two(pQueue p) {
    char* tempcode=Dequeue(p);
    if (tempcode!=NULL) {
    printf("Customer dequeued : %s\n",tempcode); 
    free(tempcode);
    tempcode=NULL;
    printf("The current status of Queue : ");
    printQueue(p);
    }
    else {
        printf("Queue is empty!\n");
    }
}

int main(void) {
    pQueue custom=createQueue(100);
    int select=-1;

    while(1) {
        select=main_select();
        if (select==0) {
            select_one(custom);
        }
        else if (select==1) {
            select_two(custom);
        }
        else if (select==2) {
            destroyQueue(custom);
            break;
        }
        else {
            printf("\n**** Wrong number ****\n\n");
        }
    }
    return 0;
}

