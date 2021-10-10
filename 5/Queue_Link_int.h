#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define _INT -2147483648
typedef int Element;

typedef struct int_tQueueNode {//real_data_inp
    Element data;
    struct int_tQueueNode *next;
} int_QueueNode, *int_pQueueNode;

typedef struct {//Head
    int count;
    int_pQueueNode front,rear;
} int_Queue, *int_pQueue;

int_pQueue int_createQueue(int size) {
    int_pQueue q=(int_pQueue) malloc (sizeof(int_Queue));

    if (q==NULL) {
        printf("Queue is not generated\n\n");
        return NULL;
    }

    q->front=NULL;
    q->rear=NULL;
    q->count=0;

    return q;
}

int int_IsEmptyQueue(int_pQueue q) {
    return q->count==0?1:0;
}  

void int_Enqueue(int_pQueue q,Element item) {
    int_pQueueNode p = (int_pQueueNode) malloc(sizeof(int_QueueNode));
    
    if (p==NULL) {
        printf("Memory Allocationg is not made\n");
        free(q);
        exit(1);
    }
    p->data=item;
    p->next=NULL;

    if (q->count<=0) {
        q->front=p;
        q->rear=p;
    }
    else {
        q->rear->next=p;
        q->rear=p;
    }
    q->count++;
}

Element int_Dequeue(int_pQueue q) {
    if (int_IsEmptyQueue(q)) {
        return _INT;
    }

    Element result=(q->front)->data;
    int_pQueueNode delptr=q->front;
    
    if (q->count==1) {
        q->front=NULL;
        q->rear=NULL;
    }
    else {
        q->front=(q->front)->next;
    }
    q->count--;
    free(delptr);
    return result;
}


void int_destroyQueue(int_pQueue q) {
    while (q->front!=NULL) {
        int_pQueueNode delptr=q->front;
        q->front=q->front->next;
        q->count--;
        free(delptr);
    }
    free(q);
}

void int_printQueue(int_pQueue q) {//Queue에 있는 모든 데이터 출력. (str, count)
    int_pQueueNode temp=q->front;
    int count=0;
        printf("(");

        if (!int_IsEmptyQueue(q)) {
        while (temp!=NULL) {
        printf(" %d %d ",temp->data,++count);
        if (temp->next==NULL) {
            break;
        }
        printf(" , ");
        temp=temp->next;
        }
        }
        printf(")\n\n");


}

int int_countQueue (int_pQueue p) {
    return p->count;
}