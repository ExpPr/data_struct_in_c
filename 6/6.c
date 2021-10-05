#include <stdio.h>
#include <stdlib.h>
#include "List_Link.h"
//include 파일명만 바꾸면 됩니다.

void list_print(pint_List p) {
  printf("The current status of List : ");
  bool n;
  int k=0;
  int out;
  do {
    n=int_traverseList(p, k++, &out);
    if(n&&k<p->count) {
      printf("%d, ",out);
    }
    else if (n&&k==(p->count)) {
      printf("%d\n",out);
    }
  } while(n);
  printf("\n");
  int_traverseList(p, 0, &out);

}

int main_page() {
  printf("In(0), Search(1), Out(2), Exit(3) : ");
  int p;
  scanf("%d",&p);
  rewind(stdin);
  return p;
}

void select_zero(pint_List p){
  printf("In : ");
  int input;
  scanf("%d",&input);
  rewind(stdin);
  int_addNodeList(p, input);
  list_print(p);
}
void select_one(pint_List p) {
  printf("Search : ");
  int input;
  scanf("%d",&input);
  rewind(stdin);
  bool result=int_searchdata(p, input);

  if (result==false) {
    printf("My list does not have %d.\n",input);
    list_print(p);
  }
  else {
    printf("My list has %d.\n",input);
    list_print(p);
  }
}
void select_sec(pint_List p) {
  printf("Out : ");
  int input;
  scanf("%d",&input);
  rewind(stdin);

  bool n = int_removeList(p, input);
  if (n==true) {
    printf("%d was removed.\n",input);
  }
  else {
    printf("%d doesn't exist.\n",input); 
  }
  list_print(p);
}

void select_th(pint_List p) {
  int_destroyList(p);
  exit(0);
}

int main(void) {
  pint_List p = int_creatlist(100);
  while (1) {
    int select=main_page();
    switch(select) {
      case 0:
        select_zero(p);
        break;
      case 1:
        select_one(p);
        break;
      case 2:
        select_sec(p);
        break;
      case 3:
        select_th(p);
        break;
    }
  }
  return 0;
}