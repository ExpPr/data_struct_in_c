#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Stack_Link.h"
#include "Stack_Link2.h"

void check_operand_error(char *exp) {//325 23 *10-3 같은 입력 오류 판별. 가장 먼저 실행요구
    int p=strlen(exp),n=0;
    int care=0;

    while (n<p) {
        if (isdigit(exp[n])&&exp[n+1]==' ') {
            n+=2;
            care=1;
            continue;
        }
        else if (care==1) {
            if (exp[n]=='+'||exp[n]=='-'||exp[n]=='%'||exp[n]=='*') {
                n++;
                care=0;
                continue;
            }
            else if (exp[n]==' '){
                n++;
                continue;
            }
            else if (isdigit(exp[n])) {
                printf("Error : Check the binary explression!");
                exit(1);
            }
        }
        n++;
    }
}

void check_parse_error(char *exp) {//괄호 확인. stack 사용안함. operand 에러 확인 먼저 할 것. 이 함수 실행후 문제 없을 시 operator 에러체크
    int inspector=0;

    for (int i=0;i<strlen(exp);i++) {
        if (exp[i]=='(') {
            inspector++;
        }
        else if (exp[i]==')') {
            if (inspector==0) {
                printf("Error : Check the pairs of Parenthesis!\n");
                exit(1);//종료.
            }
            inspector--;
        }
    }

    if (inspector!=0) {
        printf("Error : Check the pairs of Parenthesis!\n");
        exit(1);//종료.
    }
}

void check_operator_error(char *exp) {//23*10 -3 + 같이 연산자에 양쪽 피연산자가 없는 식인 경우 에러처리. 공백제거 작업을 우선 한 후 이 함수 이용.
    int p=strlen(exp),n=0;
    char c;
    if (exp[n]=='+'||exp[n]=='*'||exp[n]=='%'||exp[n]=='-') {//맨 처임 부분 입력이 바로 연산자가 들어가는 경우. 단 음수입력 고려.
        printf("Error : It is not an appropriate operator input.");
        exit(1);
    }
    while (n<p-1) {//중간에 연산자 들어갔을때 감지
        if (exp[n]=='+'||exp[n]=='-'||exp[n]=='*'||exp[n]=='%') {
            if (((exp[n-1]==')')||isdigit(exp[n-1]))  && ((exp[n+1]=='(')||isdigit(exp[n+1]))) {
                n++;
                continue;
            }
            else if (n==p-2&& ((exp[n-1]==')')||isdigit(exp[n-1])) && isdigit(exp[n+1])) {
                n++;
                continue;
            }
            else {
                printf("Error : It is not an appropriate operator input. ");
                exit(1);
            }
        }
        n++;

    }
    if (exp[n]=='+'||exp[n]=='-'||exp[n]=='*'||exp[n]=='%') {//맨 끝 연산자 감지
        printf("Error : It is not an appropriate operator input.");
        exit(1);
    }
}

void removespace(char *inp) {//공백 제거함수. 모든 스페이스 제거.
    char* str=(char*)malloc(sizeof(inp));
    int i=strlen(inp);
    int count=0;

    for (int p=0;p<i;p++) {
        if (inp[p]!=' ') {
            str[count++]=inp[p];
        }
    }
    str[count]='\0';
    strcpy(inp,str);
    free(str);
}



void check(char *p) {
    check_operand_error(p);
    check_parse_error(p);
    removespace(p);
    check_operator_error(p);
}

int priority (char a) {//우선순위
    switch (a) {
        case '+':
        case '-':
            return 2;
        case '(':
        case ')':
            return 1;
        case '*':
        case '%':
            return 3;
    }
}
//규칙 1 : 숫자는 전부 출력한다
//규칙 2 : '(' 는 stack 한다
//규칙 3 : ')' 이 나오면, stack 데이터를 pop한다. 단 ')'이 나오기 전까지 혹은 완전이 비워질때까지
//규칙 4 : 연산자가 나오면 stack에 담겨진 연산자가 자기자신보다 상위거나 동급이면 계속 pop한 뒤 이 pop을 출력함, 하위 연산자 만날경우, 자기자신을 stack한다
//규칙 5 : 입력이 끝이 날 때 stack에 남은 데이터가 있으면 전부 pop한다.
char *infix_to_postfix(char *exp) {
    int len=strlen(exp);
    int count=0;
    char *temp=(char*)malloc(sizeof(char)*2*len+1);
    pStack p=createStack(200);

    for (int i=0;i<len;i++) {
        if (exp[i]>='0'&&exp[i]<='9') {
            do {
                temp[count++]=exp[i];
                i++;
            } while (exp[i]>='0'&&exp[i]<='9');
            temp[count++]=' ';
            //한칸 건너띄는거 방지.
            i--;
        }
        else if (exp[i]=='(') {
            push(p,exp[i]);
        }
        else if (exp[i]=='*'||exp[i]=='%'||exp[i]=='+'||exp[i]=='-') {
            while (!isEmptyStack(p)&&(priority(exp[i])<=priority(top(p)))) {
                temp[count++]=pop(p);
                temp[count++]=' ';
            }
            push(p,exp[i]);
        }
        else if (exp[i]==')') {
            while (top(p)!='(') {
                temp[count++]=pop(p);
                temp[count++]=' ';
            }
            pop(p);
        }
    }

    while (!isEmptyStack(p)) {
        temp[count++]=pop(p);
        temp[count++]=' ';
    }

    temp[count-1]='\0';
    delete_stack(p);
    return temp;
}

int calc_postfix (char *post) {
    int len=strlen(post);
    int temp=0;
    int re;
    int op1,op2;

    int_pStack p=init_Stack(100);

    for (int i=0;i<len;i++) {
        if (post[i]>='0'&&post[i]<='9') {
            do {
                temp=(temp*10)+(post[i]-'0');
                i++;
            } while (post[i]!=' ');
            int_push(p,temp);
            temp=0;
        }
        else if (post[i]=='+'||post[i]=='-'||post[i]=='*'||post[i]=='%') {
            op2=int_pop(p);
            op1=int_pop(p);

            if (op2==0 && post[i]=='%') {
                printf("Error : It cannot be divided by zero.");
                int_delete_stack(p);
                exit(1);//강종 div/0에러처리
            }

            if (post[i]=='+') {
                int_push(p,op1+op2);
            }
            else if (post[i]=='-') {
                int_push(p,op1-op2);
            }
            else if (post[i]=='*') {
                int_push(p,op1*op2);
            }
            else if (post[i]=='%') {
                int_push(p,op1/op2);
            }
        }
    }
    re=int_pop(p); 
    int_delete_stack(p);
    return re;
}

int main(void) {
    printf("Arithmetic Expression : ");
    char p[200];
    scanf("%[^\n]",p);
    rewind(stdin);
    check(p);
    printf("Input : %s\n",p);
    char *q=infix_to_postfix(p);
    printf("Post : %s\n",q);
    printf("Result : %d",calc_postfix(q));
    free(q);


    return 0;
}