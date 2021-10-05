#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Stack_Link2.h"

int total_count=0;

void change10_to_nfix(int n, int ep, char *temp) {
    if (ep>=37) {
    printf("%d base can't use\n",ep);
    }
    int k=n;
    int count=0;
    pStack p = createStack(100);
    int tp=0;
    do {
        tp=k%ep;
        if (tp>=0 && tp <= 9) {
            push(p,'0'+tp);
        }
        else {
            push (p,'A'+(tp-10));
        }
        k=k/ep;
    } while (k!=0);

    while (!isEmptyStack(p)) {
        temp[count++]=pop(p);
    }
    temp[count]='\0';
    delete_stack(p);
}

int changeN_to_10(char *temp,int n) {
    int result=0;
    int index=strlen(temp)-1;
    for (int i=0;i<=index;i++) {
        if (temp[i]>='0' && temp[i]<='9') {
            result+=(temp[i]-'0')*pow(n,index-i);
        }
        else {
            result+=(temp[i]-'A'+10)*pow(n,index-i);
        }
    }
    return result;
}

int option() {
  printf("Push(0) , Pop(1), Exit(2) : ");
  int select;
  scanf("%d",&select);
  rewind(stdin);
  return select;
}

void option_push(pStack p) {
  int input=0;
  char temp[20];
  printf("push : ");
  scanf("%d",&input);
  rewind(stdin);

  change10_to_nfix(input, 12, temp);
  for (int i=strlen(temp)-1;i>=0;i--) {
    push(p,temp[i]);
  }
  push(p,' ');
  total_count++;
  printAll(p);
  printf(" ( %d )\n",total_count);
}

void option_pop(pStack p) {
  if (isEmptyStack(p)) {
    printAll(p);
    printf("\n");
  }

else {
  if (p->top->data==' ') {
    pop(p);
  }
  printf("Pop : ");
  char temp[30];
  int co=0;
  while (1) {
    temp[co++]=pop(p);
    if (isEmptyStack(p)) {
      break;
    }
    else if (top(p)==' ') {
      break;
    }
  }
  printf("%d ( %s )\n",changeN_to_10(temp, 12),temp);
  total_count--;
  printAll(p);
  printf(" ( %d )\n",total_count);
  }
}

void option_exit(pStack p) {
  delete_stack(p);
  exit(0);
}


int main(void) {
    int select_option=0;
    pStack st=createStack(100);
    while(1) {
      select_option=option();
      switch(select_option) {
        case 0:
          option_push(st);
          break;
        case 1:
          option_pop(st);
          break;
        case 2:
          option_exit(st);
          break;
        default:
          printf("wrong input\n\n");
      }
    }
  return 0;
}
