#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
typedef int Element;

#define _INT -2147483648

typedef struct {
    Element *data;
    int front,rear;
    int size;    
} int_Queue, *int_pQueue;

int_pQueue int_createQueue(int o) {
    int_Queue *que=(int_pQueue)malloc(sizeof(int_Queue));
    if (que == NULL) {
        return NULL;
    }
    que->data=(Element*) malloc (sizeof(Element)*o);

    if (que->data==NULL) {
        free(que);
        return NULL;
    }

    que->size=o;
    que->front=0;
    que->rear=0;

    return que;
}

int int_IsFullQueue(int_pQueue que) {
    if ((que->rear+1)%que->size==que->front) {
        return 1; //다참
    }
    return 0;
}

int int_IsEmptyQueue(int_pQueue q) {
    if ((q->rear)==q->front) {
        return 1;
    }
    return 0;
}

void int_Enqueue(int_pQueue p,Element item) {
    if (int_IsFullQueue(p)) {
        printf("this queue is full.\n");
    }
    else {
        p->rear=(p->rear+1)%p->size;
        p->data[p->rear]=item;
    }
}

Element int_Dequeue(int_pQueue p) {
    if (int_IsEmptyQueue(p)) {
        return _INT;
    } 
    else {
        p->front=(p->front+1)%p->size;
        return p->data[p->front];
    }
}

void int_destroyQueue(int_pQueue p) {
  if (p->data!=NULL) {
  free(p->data); }

  free(p);
}

int int_countQueue(int_pQueue p) {
    if (p->rear>=p->front) {
    return p->rear-(p->front); }
    else {
        int count=0;
        for (int i=p->front+1;i<p->size;i++) {
            count++;
        }
        for (int i=0;i<=p->rear;i++) {
            count++;
        }
        return count;
    }
}

void int_printQueue(int_pQueue p) {
    printf("( ");
    if (!int_IsEmptyQueue(p)) {
        int count=0;
        if(p->rear>p->front) {
            for (int i=p->front+1;i<p->rear;i++) {
                printf("%d %d ,",p->data[i],++count);
            }
            printf("%d %d ",p->data[p->rear],++count);
        }
        else {
            for (int i=p->front+1;i<p->size;i++) {
           printf("%d %d ,",p->data[i],++count);
            }
            for (int i=0;i<p->rear;i++) {
            printf("%d %d ,",p->data[i],++count);
        }
        printf("%d %d ",p->data[p->rear],++count);
            
        }
    }
    printf(")\n\n");
}


