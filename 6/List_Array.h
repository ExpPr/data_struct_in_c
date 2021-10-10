#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int element;


typedef struct {
  element *data;
  int count, pos, size;
} int_List, *pint_List;

pint_List int_creatlist(int size) {
  pint_List temp=(pint_List)malloc(sizeof(int_List));
  if (temp==NULL) {
    printf("Memory allocation is not made\n");
    return NULL;
  }
  temp->data=(element*)malloc(sizeof(element)*size);
  temp->count=0;
  temp->pos=-1;
  temp->size=size;

  return temp;
}

bool int_isFullLink(pint_List test) {
  if (test->size>test->count) {
    return false;
  }
  return true;
}

bool int_isEmptyLink(pint_List t) {
  return (t->count==0)?true:false;
}

bool int_searchList(pint_List p,int* pre,int * loc,element item) {
  for (*pre=-1,*loc=0;*loc<p->count;++(*pre),++(*loc)) {
      if (p->data[*loc]==item) {
        return true;
      }
      else if (p->data[*loc]>item) {
        break;
      }
  }
  return false;
}

bool int_movefrom(pint_List p,int index,int how) {
  if (how==1) {
    if (int_isFullLink(p)) {
      return false;
    }
    for (int i=p->count-1;i>=index;i--) {
      p->data[i+1]=p->data[i];
    }
    p->count++;
  }//인덱스부터 왼쪾으로 옮기기 [즉 count+1칸에 빈칸이 있음 가정]
  else if (how==2) {
    for (int i=index;i<p->count;i++) {
      p->data[i-1]=p->data[i];
    }
    p->count--;
  }//인덱스부터 오른쪽으로 옮기기 [즉 인덱스-1칸에 빈칸이 있음을 가정]
  return true;
}

void int_insert(pint_List p,int *pre, element item) {
    int_movefrom(p,++(*pre),1);
    p->data[*pre]=item;
}

void int_addNodeList(pint_List p,element item) {
    int pre, loc;
    bool result=int_searchList(p,&pre,&loc,item);
    if (!result) {
      int_insert(p,&pre,item);
    }
}

void int_deleteListNode(pint_List p, int*pre, int *loc) {
  int_movefrom(p,(*loc)+1,2);
}

bool int_removeList(pint_List p, element item)   {
  int pre,loc;
  bool find=int_searchList(p,&pre,&loc,item);
  if (find) {
    int_deleteListNode(p,&pre,&loc);
    return true;
  }
  return false;
}

void int_destroyList(pint_List p) {
  free(p->data);
  free(p);
}

bool int_traverseList(pint_List p, int fromwhere, element *dt) {
  if (fromwhere==0 || p->pos==-1) {
    p->pos=0;
  }
  else {
    p->pos++;
  }

  if (p->pos<(p->count)) {
    *dt=p->data[(p->pos)];
    return true;
  }
  else {
    *dt=0;
    return false;
  }
}

bool int_searchdata(pint_List p,element item) {
  int a,b;
  bool n = int_searchList(p,&a,&b,item);
  return n;
}

  