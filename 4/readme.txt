필수 stack 명령어 (초기화 , push ,pop , top , 해제) 

    해제 명령어는 동적할당 해제용. 가능하면 사용완료시 이 명령어로 해제 할 것.

    Stack_Array ://int형 전용 stack
        초기화 방식 : p_intStack p = init_Stack(int size)
        push : push(p_intStack p, int item)
        top : top(p_intStack p)
        pop : pop(p_intStack p)
        해제 : int_destroyyStack(p_intStack p)
    
    Stack_Link : //int형 전용 stack
        초기화방식 : int_pStack p=init_Stack() -> link형이므로 크기제한 없음.
        push : int_push(int_pStack p , int item)
        top : top (int_pStack p)
        pop : pop (int_pStack p)
        해제 : int_delete_stack(int_pStack p)

    Stack_Link2 : char 전용 stack
        초기화방식 : pStack p = createStack()
        push : push(pStack p, char c)
        top : top(pStack p)
        pop : pop(pStack p)
        해제 : delete_stack(pStack p)

        ==============================
        주의점 : 

        함수 오버로드가 안되어서 Array은 Array형끼리
        Link형은 Link형끼리만 사용해야 합니다.
        안그럼 치명적인 버그가 걸립니다. (즉 Stack_Array.h 와 Stack_Link.h 이런식으로  include 금지)
        (Stack.Link.h Stack.Link2.h 이런식으로 include하는 것은 가능)
        ==============================

구현 방식 : 
        Array 형 : 

typedef int Element
typedef struct {
    Element *stack;
    int size;
    int top;
} int_Stack, *p_intStack;

사이즈가 결정되면 *stack에 동적할당을 함. 이때 top값은 자동 -1으로 됨.
push되면 top 크기값이 1 늘어나면서 stack[top]에 실제 데이터를 넣는 방식.
pop되면 가장 맨위 데이터를 뽑은 다음. top-- 처리

Link형 : 

typedef struct tStackNode { <- push나 pop이 관리
    Element data;
    struct tStackNode *next;
} StackNode, *pStackNode;

typedef struct { <- 스택 생성시 사용되는 포인터. 헤더 스택 이라 지칭함.
    int count;
    StackNode *top;
} Stack, *pStack;

초기화 할 때 , 자동으로 헤더 스택 부분의 node 담당하는 부분값 null으로 하고
push될 때 tStackNode 를 하나 동적할당을 한 뒤, 헤더 스택에 담긴 노드 포인터 값을 전달 받음.
그리고 헤더 파일의 node 값은 방금 할당 받은 tStackNode의 주소값으로 넣음.
마지막으로 count++

pop은 미리 데이터와 마지막 tSTackNode 주소를 복사한 뒤, 헤더 파일의 노드 값은 바로 없어질 tStackNode에 담긴
다음 주소를 받으면서 자기자신은 삭제되는 형식.

=============

Calculator.c 파일 :
    작동방식 :
        1. 식을 입력 받음
        2. 먼저 문법이 맞는지 판단을 함 
         -> infix 방식으로 수 사이에 연산자 없이 공백으로 수를 띄우는지 판별. (숫자 다음 공백칸일때 감지모드 들어가며, 숫자를 발견하면 바로 에러처리)
            -> (감지모드에서 연산자나 괄호 발견시 그 즉각 감지모드 해제)
         -> 괄호 문법 확인. 열린괄호 개수와 닫힌 괄호 개수 판별. ) (  같은 오류도 판별함. stack방식보단 단순 count를 이용함.
         -> 공백 제거
         -> 연산자 문법 확인. + - * % 를 찾으면 연산자 앞에는 숫자나 ')'이 있는지, 연산자 뒤에는 숫자나 '('이 있는지 확인.
            ->맨 처음에 연산자 있거나 맨 마지막에 연산자 있으면 에러처리. (단 div/0) 은 추후처리.
         ->infix 를 postfix로 변환. 규칙이 있음.
            1. 숫자는 전부 출력. 단 숫자 출력 이후 다른 숫자 이외 문자발견시 공백으로 구분.
            2. 열린 괄호는 일단 stack함
            3. 닫힌 괄호가 나오면. 열린 괄호가 나올때까지 혹은 stack이 빌때까지 stack에 담긴 연산자 pop한뒤 출력. 열린 괄호는 제거함.
            4. 연산자가 나오면 stack에 담겨진 연산자가 자기자신보다 상위거나 동급이면 계속 pop한 뒤 이 pop을 출력함, 하위 연산자 만날경우, 자기자신을 stack
             -> ( ) : 최하위 // + - : 중위 // * % 최상위 
             5. 끝에 다다랄을때 stack에 남은 것이 있으면 전부 pop하고 출력.
        -> postfix방식으로 계산 
            숫자를 받을때 자리수 구분위해 숫자가 들어오면 기존 담겨진 수*10 한 뒤 그 숫자를 더함. (공백이 발견될때까지 한 뒤 그 수를 stack한다)
            연산자 발견시 두번 pop 함.  먼저것이 후피연산자 나중것이 선피연산자. 그리고 그 연산자 맞게 계산한후 그 값을 다시 push함.
             -> 이때 div/0 발견시 그 즉시 에러처리
        
------
식 입력시 출력이 음수가 되는 것은 구현 되지 않음 : ex - > -(10+21);
나눗셈 할때 나머지는 버려짐. 9%4 = 2
입력시 띄어쓰기는 자동으로 제거됨 : ex -> (23     +4)*3 같은 것도 가능. 단 그렇다고 너무 과도한 공백은 자제하는 것이..

나누기를 실행 할 때 / 이 아닌 %를 사용해야함. 그러지 않을 경우 에러가 발생.

가끔씩 작동이(?) 안할 때 도 잇습니다. 그럴땐 여러번 작동을 부탁드립니다.

---------------------
(9/25)

이전 파일을 올려놓아 명령어가 없어진 것이 문제인 것이 발견했습니다.
수정하였습니다.

