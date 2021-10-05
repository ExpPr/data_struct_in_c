#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef char* Element;

typedef struct {
    Element *data;
    int front,rear;
    int size;    
} Queue, *pQueue;

pQueue createQueue(int o) {
    Queue *que=(pQueue)malloc(sizeof(Queue));
    if (que == NULL) {
        return NULL;
    }
    que->data=(Element*) malloc (sizeof(Element)*o);

    if (que->data==NULL) {
        free(que);
        return NULL;
    }

    for (int i=0;i<o;i++) {
        que->data[i]=(Element)malloc(sizeof(char));
        que->data[i][0]='\0';
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
        printf("this queue is full.\n");
    }
    else {
        int len=strlen(item)+1;
        p->rear=(p->rear+1)%p->size;
        if (strlen(p->data[p->rear])!=len) {
        p->data[p->rear]= (Element) realloc (p->data[p->rear],sizeof(char)*len); }
        else if (p->data[p->rear]==NULL) {
            p->data[p->rear]=(Element) malloc (sizeof(char)*len);
        }
        strcpy(p->data[p->rear],item);
    }
}

Element Dequeue(pQueue p) {
    if (IsEmptyQueue(p)) {
        return NULL;
    } 
    else {
        p->front=(p->front+1)%p->size;
        return p->data[p->front];
    }
}

void destroyQueue(pQueue p) {
  int len=p->size;
    for (int i=0;i<len;i++) {
        if (p->data[i]!=NULL) {
        free(p->data[i]);
        p->data[i]=NULL;
        }
    }
    free(p->data);
    p->data=NULL;
    free(p);
    p=NULL;
}

int countQueue(pQueue p) {
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

void printQueue(pQueue p) {
    printf("( ");
    if (!IsEmptyQueue(p)) {
        int count=0;
        if(p->rear>p->front) {
            for (int i=p->front+1;i<p->rear;i++) {
                printf("%s %d ,",p->data[i],++count);
            }
            printf("%s %d ",p->data[p->rear],++count);
        }
        else {
            for (int i=p->front+1;i<p->size;i++) {
           printf("%s %d ,",p->data[i],++count);
            }
            for (int i=0;i<p->rear;i++) {
            printf("%s %d ,",p->data[i],++count);
        }
        printf("%s %d ",p->data[p->rear],++count);
            
        }
    }
    printf(")\n\n");
}


