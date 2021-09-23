#include <stdlib.h>
#include <stdio.h>
typedef int Element;

typedef struct {
    Element *data;
    int front,rear;
    int size;    
} Queue, *pQueue;

pQueue creatQueue(int o) {
    Queue *que=(pQueue)malloc(sizeof(Queue));
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

int IsFullQueue(pQueue que) {
    if ((que->rear+1)%que->size==que->front) {
        return 1; //다참
    }
    return 0;
}

int IsEmptyQueue(pQueue q) {
    if ((q->rear)==q->front) {
        return 1;
    }
    return 0;
}

void Enqueue(pQueue p,Element item) {
    if (IsFullQueue(p)) {
        printf("this queue is full.");
        free(p->data);
        free(p);
        exit(1);
    }
    else {
        p->rear=(p->rear+1)%p->size;
        p->data[p->rear]=item;
    }
}

Element Dequeue(pQueue p) {
    if (IsEmptyQueue(p)) {
        printf("this queue is empty.");
        free(p->data);
        free(p);
        exit(1);
    } 
    else {
        p->front=(p->front+1)%p->size;
        return p->data[p->front];
    }
}

void DeleteQueue(pQueue p) {
    free(p->data);
    free(p);
}

Element countQueue(pQueue p) {
    return p->rear-(p->front);
}

