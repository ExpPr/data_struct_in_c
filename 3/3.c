#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char name[50];
    int age;
    int score[3];//수학 영어 역사
} std, *stdp;//그냥 + 포인터.

int comp1(const void *a, const void *b) {
    return strcmp(((stdp)a)->name,((stdp)b)->name);
}//이름순.

int comp2(const void *a, const void *b) {
    return ((stdp)a)->age-((stdp)b)->age;
}//나이

int comp3(const void *a, const void *b) {
    return ((stdp)a)->score[0]-((stdp)b)->score[0];
}//수학

int comp4(const void *a, const void *b) {
  return ((stdp)a)->score[1]-((stdp)b)->score[1];
}//영어

int comp5(const void *a, const void *b) {
    return ((stdp)a)->score[2]-((stdp)b)->score[2];
}//국사

int (*comp[5]) (const void *a,const void *b)={comp1,comp2,comp3,comp4,comp5};//함수  포인터 배열. 정렬옵션 선택용.

int check_line(char *np) {
    int line=0;//라인수
    char c[200];

    FILE *fep=fopen(np,"r");
    while (!feof(fep)) {
        line++;
        fgets(c,200,fep);
    }
    fseek(fep,-1,SEEK_CUR);

    if(fgetc(fep)=='\n') {
        line--;//마지막 줄 감안
    }
    fclose(fep);
    return line;
}

int data_check(std a,int line) {
    int err=0;
    if (a.age<0) {
        printf("Result : The age cannot be a negative number. Program terminates.");
        return 1;
    }
    if (a.score[0]<0 || a.score[0]>100) {
        printf("Result : The range of math scores must be 0 to 100. Program terminates.\n");
        return 2;
    }
    if (a.score[1]<0 || a.score[1]>100) {
        printf("Result : The range of English scores must be 0 to 100. Program terminates.\n");
        return 3;
    }
     if (a.score[2]<0 || a.score[2]>100) {
        printf("Result : The range of History scores must be 0 to 100. Program terminates.\n");
        return 4;
    }
    return 0;
}

void dataprint(stdp a,int size,int p) {//p : 맨 첫줄 출력용도.
    //기본 :  이름 나이 수학 영어 역사
    // 정렬 기준을 이름위치와 변경
    //노가다 방식.
    switch (p) {
    case 0:
    printf("============== DATA =================\n");
    puts("No\tName\tAge\tMath\tEnglish\tHistory");
    for (int i=0;i<size;i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\n",i+1,a[i].name,a[i].age,a[i].score[0],a[i].score[1],a[i].score[2]);
    }
    printf("===========================================\n");
    break;
    case 1:
    printf("============== DATA =================\n");
    puts("No\tAge\tName\tMath\tEnglish\tHistory");
    for (int i=0;i<size;i++) {
        printf("%d\t%d\t%s\t%d\t%d\t%d\n",i+1,a[i].age,a[i].name,a[i].score[0],a[i].score[1],a[i].score[2]);
    }
    printf("===========================================\n");
    break;
    case 2:
    printf("============== DATA =================\n");
    puts("No\tMath\tName\tAge\tEnglish\tHistory");
    for (int i=0;i<size;i++) {
        printf("%d\t%d\t%s\t%d\t%d\t%d\n",i+1,a[i].score[0],a[i].name,a[i].age,a[i].score[1],a[i].score[2]);
    }
    printf("===========================================\n");
    break;
    case 3:
    printf("============== DATA =================\n");
    puts("No\tEnglish\tName\tAge\tMath\tHistory");
    for (int i=0;i<size;i++) {
        printf("%d\t%d\t%s\t%d\t%d\t%d\n",i+1,a[i].score[1],a[i].name,a[i].age,a[i].score[0],a[i].score[2]);
    }
    printf("===========================================\n");
    break;
    case 4:
    printf("============== DATA =================\n");
    puts("No\tHistory\tName\tAge\tMath\tEnglish");
    for (int i=0;i<size;i++) {
        printf("%d\t%d\t%s\t%d\t%d\t%d\n",i+1,a[i].score[2],a[i].name,a[i].age,a[i].score[0],a[i].score[1]);
    }
    printf("===========================================\n");
    break;
    }

}

int main_p() {
    puts("========================================");
    puts("1) Insert");
    puts("2) Sort");
    puts("3) Quit");
    printf("Select a menu : ");

    int p;
    scanf("%d",&p);
    return p;
}

int main(void) {
    int max_data=0;//데이터 양
    int temp_data_count=0;//임시 버퍼 크기.
    int select=0;//메뉴 선택

    stdp dt = (stdp) malloc (sizeof(std));

    while (1) {//반복문
        if (select==0) {//메인 인터페이스.
            select=main_p();
        }
        else if (select==1) {//인풋
            char fname[100];
            printf("File Name : ");
            scanf("%s",fname);
            rewind(stdin);//버퍼 초기화

            FILE *fp = fopen(fname,"r");

            if (fp==NULL) {//파일 존재 여부 판단.
                printf("Result : The file does noot exist. Program terminated");
                break;
            }
            else {
                stdp tempsp=(stdp) malloc (sizeof(std));
                int temp_c=0;//실질적 데이터 입력 개수 카운트용.
                temp_data_count=check_line(fname);//.txt파일 입력.
                tempsp=(stdp)realloc(tempsp,sizeof(std)*temp_data_count);

                for (int i=0;i<temp_data_count;i++) {
                    if (fscanf(fp,"%s %d %d %d %d",tempsp[i].name,&tempsp[i].age,&tempsp[i].score[0],&tempsp[i].score[1],&tempsp[i].score[2])!=5) {//데이터 입력. 5개입력이 안되면 강제종료.
                        printf("Result : Line %d is not a complete input.Program terminated",i+1);//에러1 출력
                        fclose(fp);
                        free(tempsp);
                        break;
                    }
                    else if (data_check(tempsp[i],i+1)!=0) {//5개 입력 완전히 받은 상태면. 숫자 데이터가 올바른 데이터인지 판단. 아니면 강제종료.
                        fclose(fp);
                        free(tempsp);
                        break;
                    }
                    else {
                        temp_c++;
                    }   
                }

                if (temp_c!=temp_data_count) {
                    break;
                }
                else {
                    dt=realloc(dt,sizeof(std)*(max_data+temp_data_count));//본 메모리 재할당.
                    memcpy(dt+max_data,tempsp,sizeof(std)*temp_data_count);//메모리 데이터 복사.
                   max_data+=temp_data_count;
                    dataprint(dt,max_data,0);
                    select=0;
                    fclose(fp);
                    free(tempsp);
                }

            }
        }
        else if (select==2) {
            if (max_data==0) {
                printf("\nResult : There is no data to be sorted. Program terminates.");
                select=3;
                break;
            }
            else {
                int sort_menu=0;
                puts("-------------------");
                puts("1) Name");
                puts("2) Age");
                puts("3) Math");
                puts("4) English");
                puts("5) History");
                printf("Choose the field to sort by : ");
                scanf("%d",&sort_menu);
                rewind(stdin);//버퍼 비우기


                if (sort_menu<1 || sort_menu>5) {
                    printf("Reuslt : Please input it again.\n\n");
                    select=2;
                }
                else {
                    qsort(dt,max_data,sizeof(std),comp[sort_menu-1]);
                    dataprint(dt,max_data,sort_menu-1);
                    select=0;
                }

            }
        }
        else if (select==3) {
            break;
        }
        else {
            puts("-------");
            puts("Wrong Number. Please Input again.");
            puts("-------");
            select=0;
        }
    }

    free(dt);//할당 해제
    return 0;
}