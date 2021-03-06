#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef char* Element;

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

int IsEmptyQueue(pQueue q) {
    return q->count==0?1:0;
}  

void Enqueue(pQueue q,Element item) {
    pQueueNode p = (pQueueNode) malloc(sizeof(QueueNode));
    
    if (p==NULL) {
        printf("Memory Allocationg is not made\n");
        free(q);
        exit(1);
    }
    int len=strlen(item)+1;
    p->data=(Element) malloc (sizeof(char)*len);
    strcpy(p->data,item);
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

void printQueue(pQueue q) {//Queue에 있는 모든 데이터 출력. (str, count)
    pQueueNode temp=q->front;
    int count=0;
        printf("(");

        if (!IsEmptyQueue(q)) {
        while (temp!=NULL) {
        printf(" %s %d ",temp->data,++count);
        if (temp->next==NULL) {
            break;
        }
        printf(" , ");
        temp=temp->next;
        }
        }
        printf(")\n\n");


}

int countQueue (pQueue p) {
    return p->count;
}