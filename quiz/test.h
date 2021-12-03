#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Tree_Queue.h"

typedef struct {
    int count;//vertex개수.
    int (*compare)(void *a1, void *a2);
    struct vertex* first;
    int** pArc;//동적할당으로 행렬 구현. 행 -> 열 
} Gragh, *pGragh;

typedef struct vertex {
  struct vertex* pnextvertex;
  void* data;
  int inDegree;
  int OutDegree;
  short processed;
} Vertex, *pVertex;
//vertex 입력받은 순서가 곧 행의 위치

pGragh CreateGragh(int (*comp)(void *a1,void *a2)) {
    pGragh temp = (pGragh)malloc(sizeof(Gragh));
    if (temp==NULL) {
        return NULL;
    }
    temp->count=0;
    temp->first=NULL;
    temp->compare=comp;
    return temp;
}

int sequence_vertex(pGragh head,pVertex temp) {//맨처음에 바로 발견 = 0번째
    int re=0;
    for (pVertex tp = head->first;tp!=NULL;tp=tp->pnextvertex) {
        if (tp==temp) {
            break;
        }
        re++;
    }
    return (re<head->count)?re:-1;//만약 없는 vertex인 경우 -1을 리턴함.
}

pVertex check_data(pGragh head,void *item) {
    pVertex temp=head->first;
    for (;temp!=NULL;temp=temp->pnextvertex) {
        if (head->compare(item,temp->data)==0) {
            break;
        }
    }
    return temp;
}


pVertex addVertex(pGragh head,void* item) {
    pVertex temp = (pVertex) malloc(sizeof(Vertex));
    if (temp==NULL) {
        return NULL;
    }

    int size=head->count;
    int** newarc=(int**)malloc(sizeof(int*)*(size+1));
    for (int i=0;i<size;i++) {
        newarc[i]=(int*)malloc(sizeof(int)*(size+1));
        if (newarc[i]==NULL) {
            for (int k=0;k<i;k++) {
                free(newarc[k]);
            }
            free(newarc);
            return NULL;
        }
    }

    temp->inDegree=0;
    temp->OutDegree=0;
    temp->processed=0;
    temp->pnextvertex=NULL;
    temp->data=item;
    head->count++;

    if (head->count==0) {
        head->first=temp;
        head->pArc=(int**)malloc(sizeof(int*));//0에서 시작시 이중동적할당
        (head->pArc)[0]=(int*)malloc(sizeof(int));
        return temp;
    }
    else {
        pVertex locPtr=head->first;
        pVertex predPtr=NULL;
        while (locPtr!=NULL && (head->compare(item,locPtr->data)>=0)) {
            if (head->compare(item,locPtr->data)==0) {
                free(temp);
                head->count--;
                return NULL;
            }
            predPtr=locPtr;
            locPtr=locPtr->pnextvertex;
        }
        if (predPtr==NULL) {
            head->first=temp;
        }
        else {
            predPtr->pnextvertex=temp;
        }
            temp->pnextvertex=locPtr;
    }

    int location = sequence_vertex(head,temp);
    size=head->count;


    for (int i=0;i<size;i++) {
        for (int k=0;k<size;k++) {
            if (i<size-1&&k<size-1) {
            newarc[i][k]=head->pArc[i][k]; }
            else {
                newarc[i][k]=0;
            }
        }
    }


    int **delPtr=head->pArc;
    head->pArc=newarc;

    for (int i=0;i<size-1;i++) {
        free(delPtr[i]);
    }
    free(delPtr);

    if (location != 0 && location != (head->count) - 1) {
        for (int i = 0; i < location; i++) {
            for (int k = size - 2; k >= location; k--)
                head->pArc[i][k + 1] = head->pArc[i][k];
        }

        for (int i = size - 2; i >= location; i--) {
            for (int k = size - 2; k >= location; k--) {
                head->pArc[i + 1][k + 1] = head->pArc[i][k];
            }
        }
        for (int i = size - 2; i >= location; i--) {
            for (int k = 0; k < location; k++) {
                head->pArc[i + 1][k] = head->pArc[i][k];
            }
        }
    }

    if (location == 0) {
        for (int i = size - 2; i >= 0; i--) {
            for (int k = size - 1; k >= 0; k--) {
                head->pArc[i + 1][k + 1] = head->pArc[i][k];
            }
        }
    }

    for (int i = 0; i < size; i++) {
        head->pArc[i][location] = 0;
    }
    memset((head->pArc)[location], 0, size * sizeof(int));
    

    return temp;
}

bool add_arc(pGragh head,pVertex superior, pVertex inferior) {//superior -> inferior, 
    int super=sequence_vertex(head,superior),infer=sequence_vertex(head,inferior);
    if (super==-1||infer==-1) {
        return false;//없는 경우가 잇을 경우 바로 종료.
    }
    head->pArc[super][infer]=1;//super -> infer 
    return true;
}

bool delete_arc(pGragh head,pVertex superior, pVertex inferior) {
    int super=sequence_vertex(head,superior),infer=sequence_vertex(head,inferior);
    if (super==-1||infer==-1) {
        return false;//없는 경우가 잇을 경우 바로 종료.
    }
    head->pArc[super][infer]=0;//super -> infer 관계 바로 삭제
    return true;
}

bool delete_all_arc(pGragh head,pVertex target) {// target의 모든 outdegree 제거
    int target_number=sequence_vertex(head,target);
    if (target_number==-1) {
        return false;
    }
    memset((head->pArc)[target_number],0,(head->count)*sizeof(int));
    return true;
}

bool delete_vertex(pGragh head,pVertex remove_vertex) {
    int target_number=sequence_vertex(head,remove_vertex);
    if (target_number==-1) {
        return false;//해당 vertex가 그래프에 없을 경우 자동 종료.
    }
    delete_all_arc(head,remove_vertex);

    int size=head->count;
    for (int i=0;i<size;i++) {
        if (i==target_number) {
            continue;
        }
        head->pArc[i][target_number]=0;
    }

    if (size==1) {//1개밖에 안남았고 이제 0개로 바뀔떄
        free(head->pArc[0]);
        free(head->pArc);
    }
    else {//2개 이상 있었었을때. 잘릴 열의 오른쪽 데이터들 전부 왼쪽 한칸씩 옮기기, 아래쪽은 위로 한칸씩 옮기는 것도 중요함.

    if (target_number!=0 && target_number!=size-1) {//이때 해당 부분 index값이 0 혹은 size-1를 제외한, 즉 중간에 있는 vertex 제거하는 경우

        for (int i=0;i<target_number;i++) {//오른쪽 상단 영역
            for (int k=target_number+1;k<size;k++) {
                head->pArc[i][k-1]=head->pArc[i][k];
            }
        }

        for (int i=target_number+1;i<size;i++) {//오른쪽 하단 영역
            for (int k=target_number+1;k<size;k++) {
                head->pArc[i-1][k-1]=head->pArc[i][k];
            }
        }

        for (int i=target_number+1;i<size;i++) {//왼쪽 하단 영역
            for (int j=0;j<target_number;j++) {
                head->pArc[i-1][j]=head->pArc[i][j];
            }
        }
        }

    else if (target_number==0) {//만약 맨 처음 vertex를 제거해야 할 경우.
        for (int i=1;i<size;i++) {
            for (int k=1;k<size;k++) {
                head->pArc[i-1][k-1]=head->pArc[i][k];
             }
            }
        }
    }
    //여기서부터 vertex _link 영역
     pVertex temp=NULL;//temp->pnextvertex 가 remove_vertex임.

    if (head->first==remove_vertex) {//만약 head->first가 삭제 대상인 경우 이를 처리함.
        temp=head->first;
        head->first=head->first->pnextvertex;
        head->count--;
        free(temp);
        return true;
    }

  for (temp=head->first;temp!=NULL&&temp->pnextvertex!=remove_vertex;temp=temp->pnextvertex) {}
    temp->pnextvertex=temp->pnextvertex->pnextvertex;//한칸 건너띄기

  //free(remove_vertex->data); <-필요한 경우.
  free(remove_vertex);
  head->count--;
  return true;
}

bool delete_gragh(pGragh head) {
    if (head->count!=0) {
       pVertex temp;
        for (;head->first!=NULL;) {
            temp=head->first;
            head->first=head->first->pnextvertex;
            //free(temp->data);
            free(temp);
        }
        for (int i=0;i<head->count;i++) {
            free(head->pArc[i]);
        }
        free(head->pArc);
    }
    free(head);
    return true;
}

void clear_processed(pGragh root) {
  for (pVertex rp = root->first; rp!=NULL; rp=rp->pnextvertex) {
    rp->processed=0;
  }
}

pVertex return_vertex(pGragh root, int sequence) {
    if (sequence>=root->count) {
        return NULL;
    }
    pVertex temp=root->first;
    for (int i=0;i<sequence;i++) {
        temp=temp->pnextvertex;
    }
    return temp;
}


bool DepthFirstTraversal (pGragh head,pVertex root,void (*process)(void *dataptr)) {
    if (sequence_vertex(head, root)==-1) {
      return false;
    }
    if (root->processed) {
        return false;
    }
    (*process)(root->data);
    root->processed=1;

    int i=sequence_vertex(head,root);
    for (int k=0;k<head->count;k++) {
        if (head->pArc[i][k]>=1&&return_vertex(head,return_vertex(head,k)->processed==0)) {
            DepthFirstTraversal(head,return_vertex(head,k),process);
        }
    }
    return true;
}

bool BreathFirstTraversal(pGragh head,pVertex root,void (*process)(void *dataptr),pQueue que) {

    if (sequence_vertex(head, root)==-1) {
      return false;
    }
    int k=sequence_vertex(head,root);
    if (root!=NULL && root->processed==0) {
      (*process)(root->data);
      root->processed=1;
    }

    for (int i=0;i<head->count;i++) {
      if (head->pArc[k][i]==1) {
        if (return_vertex(head, i)->processed==0) {
          Enqueue(que, return_vertex(head,i));
        }
      }
    }

  if (!IsEmptyQueue(que)) {
    BreathFirstTraversal(head, (pVertex)Dequeue(que), process, que);
  }
  return true;
}

void print_all_arc_data(pGragh head,pVertex check,void (*process)(void *dataptr)) {
    int k=sequence_vertex(head,check);
    if (k!=-1) {
        for (int i=0;i<head->count;i++) {
            if (head->pArc[k][i]==1) {
                (process)(return_vertex(head,i)->data);
            }
        }
    
    }
  }

