
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree_Queue.h"

typedef struct {
  int count;
  struct vertex* first;
  int (*compare)(void *a1, void *a2);
} Gragh, *pGragh;

typedef struct vertex {
  struct vertex* pnextvertex;
  void* data;
  int inDegree;
  int OutDegree;
  short processed;
  struct arc* fpArk;
} Vertex, *pVertex;

typedef struct arc {
  struct vertex* destination;
  struct arc* next;
} ARC, *pArc;

pGragh CreateGragh(int comp(void *a1, void *a2)) {
    pGragh temp = (pGragh) malloc(sizeof(Gragh));
    if (temp==NULL) {
      return NULL;
    }
    temp->count=0;
    temp->first=NULL;//초기화
    temp->compare=comp;
    return temp;
}

pVertex addVertex(pGragh head,void* item) {
  pVertex temp = (pVertex) malloc(sizeof(Vertex));
  if (temp==NULL) {
    return NULL;
  }
  temp->data=item;
  head->count++;
  temp->pnextvertex=NULL;
  temp->inDegree=0;
  temp->OutDegree=0;
  temp->fpArk=NULL;

  if (head->first==NULL) {//헤드 vertex가 빈공간일 경우
    head->first=temp;
    return temp;
  }

  pVertex check=head->first;//헤드 vertex가 빈공간이 아닐 경우 마지막 vertex를 찾는 과정
  while (check->pnextvertex!=NULL) {
    check=check->pnextvertex;
  }
  check->pnextvertex=temp;
  return temp;
}

pArc return_last_arc(pVertex check) {//어떤 vertex의 마지막 arc 포인터를 return, 없을경우 NULL 리턴됨
  if (check->fpArk==NULL) {
    return NULL;
  }
  else {
    pArc test=check->fpArk;
    while (test->next!=NULL) {
      test=test->next;
    }
    return test;
  }
}

pVertex check_list(pGragh head,pVertex check) {
  pVertex temp=NULL;
  for (temp=head->first;temp!=NULL;temp=temp->pnextvertex) {
    if (temp==check) {
      break;
    }
  }
  return temp;
}

bool add_arc(pGragh head,pVertex superior, pVertex inferior) {
  if (check_list(head,superior)==NULL || check_list(head,inferior)==NULL) {
    return false;
  }
  pArc temp=(pArc) malloc(sizeof(ARC));
  if (temp==NULL) {
    return false;
  }
  temp->destination=inferior;
  temp->next=NULL;

  pArc inp=return_last_arc(superior);

  if (inp==NULL) {
    superior->fpArk=temp;
  }
  else {
    inp->next=temp;
  }

  superior->OutDegree++;
  inferior->inDegree++;
  return true;
}

//superior -> inferior 꼴 관계를 삭제함 "만약 있다면.""
bool delete_arc(pGragh head,pVertex superior,pVertex inferior) {
  if (check_list(head,superior)==NULL || check_list(head,inferior)==NULL) {
    return false;
  }

  if (superior->fpArk==NULL || superior==NULL || superior->OutDegree==0) {
    return false;
  }
  if (superior==inferior) {//delete_edge용 동일 상황인 경우를 
    return false;
  }

  pArc inp=superior->fpArk;
  if (superior->fpArk->destination==inferior) {
    inp=superior->fpArk;
    superior->fpArk=superior->fpArk->next;
    free(inp);
    superior->OutDegree--;
    inferior->inDegree--;
    return true;
  }

  while (inp->next!=NULL) {
    if (inp->next->destination==inferior) {
      break;
    }
    inp=inp->next;
  }

  if (inp->next==NULL) {
    return false;
  }
  else {
    pArc pdelete_arc=inp->next;
    inp->next=(inp->next)->next;//중간에 삭제되고 끊킨 부분 연결 혹은 NULL 처리 (끝단처리)
    free(pdelete_arc);//동적할당해제
    superior->OutDegree--;
    inferior->inDegree--;
    return true;
  }
}


bool delete_all_arc(pGragh head,pVertex vertex) {//vertex에서의 모든 outdegree관계(arc) 제거함. 이때 indegree들도 고려해야함
  if (check_list(head,vertex)==NULL) {
    return false;
  }
  if (vertex->OutDegree==0) {
    return false;
  }
  pArc temp=NULL;
  while (vertex->fpArk!=NULL) {
    temp=vertex->fpArk;
    vertex->fpArk=vertex->fpArk->next;
    temp->destination->inDegree--;
    free(temp);
  }
  vertex->OutDegree=0;
  return true;
}

bool delete_vertex(pGragh head,pVertex remove_vertex) {//실제 삭제할 vertex가 있는지 판단 유무없음. 유의할것.
  for (pVertex root=head->first;root!=NULL;root=root->pnextvertex) {
    delete_arc(head,root,remove_vertex);//모든 root -> remove_vertex 관계 제거
  }
  delete_all_arc(head,remove_vertex);//모든 remove_vetex에서의 outdegree를 제거함.

 pVertex temp=NULL;//temp->pnextvertex 가 remove_vertex임.

  if (head->first==remove_vertex) {//만약 head->first가 삭제 대상인 경우 이를 처리함.
    temp=head->first;
    head->first=head->first->pnextvertex;
    head->count--;
    free(temp);
    return true;
  }

  for (temp=head->first;temp!=NULL&&temp->pnextvertex!=remove_vertex;temp=temp->pnextvertex);
  temp->pnextvertex=temp->pnextvertex->pnextvertex;//한칸 건너띄기

  //free(remove_vertex->data); <-필요한 경우.
  free(remove_vertex);
  head->count--;
  return true;
}

bool delete_gragh(pGragh head) {
  if (head->first==NULL) {
    free(head);
    return true;
  }
  while (head->count!=0) {
    delete_vertex(head, head->first);
  }
  free(head);
  return true;
}

void clear_processed(pGragh root) {
  for (pVertex rp = root->first; rp!=NULL; rp=rp->pnextvertex) {
    rp->processed=0;
  }
}


bool DepthFirstTraversal (pGragh head,pVertex root,void (*process)(void *dataptr)) {
  if (check_list(head,root)==NULL) {
    return false;
  }
  pArc ac=NULL;
  if (root->processed) {
    return false;
  }
  (*process)(root->data);
  root->processed=1;

  for (ac=root->fpArk;ac!=NULL;ac=ac->next) {
    if (!ac->destination->processed) {
      DepthFirstTraversal(head,ac->destination,process);
    }
  }
  return true;
}


bool BreathFirstTraversal(pGragh head,pVertex root,void (*process)(void *dataptr),pQueue que) {
  if (check_list(head,root)==NULL) {
    return false;
  }
  if (root!=NULL&&root->processed==0) {
    (*process)(root->data);
    root->processed=1;
  }
  for (pArc arcs=root->fpArk;arcs!=NULL;arcs=arcs->next) {
    if (arcs->destination->processed==0) {
      Enqueue(que,arcs->destination);
    }
  }

  if (!IsEmptyQueue(que)) {
    BreathFirstTraversal(head,(pVertex)Dequeue(que),process,que);
  }
  
  return true;
}