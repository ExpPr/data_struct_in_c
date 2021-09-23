#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>//strtok
#include <stdlib.h>//qsort

int comp(const void* a, const void* b) {//qsort용
	int a1 = *(int*)a;
	int a2 = *(int*)b;

	if (a1 < a2) {
		return -1;
	}
	if (a1 > a2) {
		return 1;
	}
	return 0;
}


int checkasc(int p[10]) {//정렬확인용

	for (int i = 1; i < 10; i++) {
		int key = p[i];
		for (int j = i - 1; j >= 0; j--) {
			if (p[j] > key) {
				return 1;
				
			}
			
		}
	}
	return 0;
}

int input_asc_int(int tp[]) {
	char input[2][250];
	int count=0;
	int temp[2][10];

	printf("Input : \n");

	for (int i=0;i<2;i++) {
		scanf("%[^\n]",input[i]);
		getchar();
	}//일단 두줄 받기
	rewind(stdin);//더블로 출력되는 현상 막기.


	for (int i=0;i<2;i++) {
		int *temp=malloc(sizeof(int));//임시버퍼
		char *ptr=strtok(input[i],", ");//", "기준으로 포인터 옮기기(?)
		while (ptr!=NULL) {
			temp[count]=atoi(ptr);
			ptr=strtok(NULL,", ");
			count++;
			temp=(int*)realloc(temp,sizeof(int)*(count+1));
		}

		if (count>10 || count<10) {
			printf("\nYou should input 20 numbers in total.");//각 줄당 숫자 개수 비교해서 하나라도 발견시. 그 즉시 종료.
			free(temp);
			return 1;
		}
		temp=(int*)realloc(temp,sizeof(int)*(10));//11배를 한걸 10배로 다시 조정.

		if (checkasc(temp)!=0) {//오름차순인지 판별.
			printf("\nThe input numbers are not in ascending order.");
			free(temp);
			return 2;
		}

		else {//각 줄당 모든 조건 충족시 실제 데이터 입력.
			for (int k=i*10;k<((i+1)*10);k++) {
				tp[k]=temp[k>=10?k-10:k];
			}
			free(temp);
			count=0;
		}
	}
	return 0;//성공적 입력 확인.
}

int main(void) {
	
	int result[20];//데이터 입력.
	int count=1;
	int deduplicated_result[20];

	if (input_asc_int(result)==0) {
		qsort(result,20,sizeof(int),comp);//퀵정렬

		deduplicated_result[0] = result[0];//중복제거
		for (int k = 1; k < 20; k++) {
			if (result[k] == result[k - 1]) {
				continue;
			}
			else {
				deduplicated_result[count] = result[k];
				count++;
			}
		}


		printf("Output : \n");//실질적 출력.
		for (int k = 0; k < count - 1; k++) {
			printf("%d, ", deduplicated_result[k]);
		}
		printf("%d", deduplicated_result[count - 1]);//마지막 콤마 출력 배제

	}

	return 0;
}
	
