#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//ascend type link_list
typedef int element;


typedef struct int_tListNode {
  element data;
  struct int_tListNode *next;
} int_ListNode, *pint_ListNode;

typedef struct {
  element count;
  pint_ListNode head;
  pint_ListNode pos;
}int_List, *pint_List;

pint_List int_creatlist(int inp) {
  pint_List p = (pint_List) malloc(sizeof(int_List));
  if (p==NULL) {
    return NULL;
  }
  p->count=0;
  p->head=NULL;
  p->pos=NULL;

  return p;
}

//private function : _insert; 즉 끼어들기.
void int_insert(pint_List p,pint_ListNode pre, element item) {
  pint_ListNode temp=(pint_ListNode) malloc (sizeof(int_ListNode));
  temp->data=item;

  if (pre==NULL) {
    temp->next=p->head;
    p->head=temp;
  }
  else {
    temp->next=pre->next;
    pre->next=temp;
  }
  p->count++;
}

bool int_searchList(pint_List p, int_ListNode **pre, int_ListNode **loc, element item) {
  for (*pre=NULL, *loc=p->head;*loc!=NULL;*pre=*loc,*loc=(*loc)->next) {
    if ((*loc)->data==item) {
      return true;
    }
    else if ((*loc)->data>item) {
      break;//오름차순 비교용.
    }
  }
  return false;

}


void int_addNodeList(pint_List p,element item) {
    pint_ListNode pre=NULL, loc=NULL;
    bool result=int_searchList(p,&pre,&loc,item);
    if (!result) {
      int_insert(p,pre,item);
    }
}

void int_deleteListNode(pint_List p, pint_ListNode pre, pint_ListNode Loc) {
  if (pre==NULL) {
    p->head=Loc->next;
  }
  else {
    pre->next=Loc->next;
  }
  free(Loc);
  p->count--;
}

bool int_traverseList(pint_List p, int fromwhere, element *dt) {
  if (fromwhere==0 || p->pos==NULL) {
    p->pos=p->head;
  }
  else {
    p->pos=p->pos->next;
  }

  if (p->pos!=NULL) {
    *dt=p->pos->data;
    return true;
  }
  else {
    *dt=0;
    return false;
  }
}

void int_destroyList(pint_List p) {
  pint_ListNode dltptr=NULL,next=NULL; 
  for (dltptr=p->head;dltptr!=NULL;dltptr=next) {
    free(dltptr);
  }
  free(p);
}

bool int_removeList(pint_List p, element item)  {
  pint_ListNode pre=NULL, loc=NULL;
  bool find=int_searchList(p,&pre,&loc,item);
  if (find) {
    int_deleteListNode(p,pre,loc);
    return true;
  }
  return false;
}

bool int_isEmptyList(pint_List p) {
  if (p->count==0) {
    return true;
  }
  return false;
}

bool int_searchdata(pint_List p,element item) {
  pint_ListNode a,b;
  bool n = int_searchList(p,&a,&b,item);
  return n;
}


//bool int_isFullList() 생략.
