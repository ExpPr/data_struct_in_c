
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef void* Element;

typedef struct tQueueNode {//real_data_inp
    Element data;
    struct tQueueNode *next;
} QueueNode, *pQueueNode;

typedef struct {//Head
    int count;
    pQueueNode front,rear;
} Queue, *pQueue;

pQueue createQueue(int size) {
    pQueue q=(pQueue) malloc (sizeof(Queue));

    if (q==NULL) {
        printf("Queue is not generated\n\n");
        return NULL;
    }

    q->front=NULL;
    q->rear=NULL;
    q->count=0;

    return q;
}

bool IsEmptyQueue(pQueue q) {
    return q->count==0?1:0;
}  

bool Enqueue(pQueue q,Element item) {
    pQueueNode p = (pQueueNode) malloc(sizeof(QueueNode));
    
    if (p==NULL) {
        printf("Memory Allocationg is not made\n");
        free(q);
        return false;
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
    return true;
}

Element Dequeue(pQueue q) {
    if (IsEmptyQueue(q)) {
        return NULL;
    }

    Element result=(q->front)->data;
    pQueueNode delptr=q->front;
    
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


void destroyQueue(pQueue q) {
    while (q->front!=NULL) {
        pQueueNode delptr=q->front;
        q->front=q->front->next;
        q->count--;
        if (delptr->data!=NULL) {
            free(delptr->data);
        }
        free(delptr);
    }
    free(q);
}

int countQueue (pQueue p) {
    return p->count;
}
