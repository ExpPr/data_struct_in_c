#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;

typedef struct Queue{
   element* queue;
   int size;
   int front, rear;
}Queue;

Queue* CreateQueue(int size)
{
   Queue *pQueue=(Queue*)malloc(sizeof(Queue));
   if (pQueue==NULL)
      return NULL;
    
   pQueue->queue = (element*)malloc(size*sizeof(element));
   if(pQueue->queue == NULL)
   {
      free(pQueue);
      return NULL;
   }
   pQueue->size = size;
   pQueue->front =0;
   pQueue->rear = 0;

   return pQueue;
}

int IsFullQueue(Queue* q)
{
   if (q->rear+1 % q->size == q->front)
      return 1;
  else
      return 0;
}

int IsEmptyQueue(Queue* q)
{
  if (q->front ==q->rear)
    return 1;
  else 
    return 0;
}

void Enqueue(Queue* q, element item)
{
  if (IsFullQueue(q))
  {
    printf("Queue is full.\n");
    return ;
  }
  else
  {
    q->rear = (q->rear + 1)%q->size;
    q->queue[q->rear]=item;
  }
}

element Dequeue(Queue *q)
{
  if (IsEmptyQueue(q))
  {
    printf("Queue is empty.\n");
    return 0;
  }
  else
  {
    q->front = (q->front+1)%q->size;
    return q->queue[q->front] ;
  }
}

void printQ(Queue *q)
{
  int i=q->front;

  while(1){
    i = (i+1)%q->size;
    if(i <= q->rear)
      printf("%s ", q->queue[i]);
    else
      break;  
  }
  printf("\n");
}

int main(void)
{
  Queue *q = CreateQueue(100);
  Enqueue(q, "a");
  Enqueue(q, "b");
  Enqueue(q, "c");
  printQ(q);
  printf("%s\n",Dequeue(q));
  printf("%s\n",Dequeue(q));
  printf("%s\n",Dequeue(q));

  Queue *q2 = CreateQueue(100);
  char temp[100];
  char* item;
  for (int i=0;i<3;i++)
  {
    printf("단어 입력:");
    scanf("%s",temp);
    item=temp;
    Enqueue(q2, item);
    printQ(q2);
  }

  return 0;
}