#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// array + linklist 형태
#define MAX_SIZE 50// array 크기. 

// 힙은 기본적으로 Array형으로 띄운뒤, 만약 충돌값이 날 경우 그 즉시 LinkedList형식으로 연결함.
// heap_function은 MAX_SIZE를 기준으로 하며, 데이터에서 MAX_SIZE를 나눈 나머지를 사용함.

void swap(int *a,int *b) {
    int temp=*a;
    *a=*b;
    *b=temp;
}


typedef struct tHeap {
    int data;
    bool inputed;
    struct tHeap *next;
} Heap, *pHeap;

bool findkey(pHeap array, int key) {
    int location=key%MAX_SIZE;

		if (array[location].inputed==false) {
			return false;
		}
    
    if (array[location].data==key) {
        return true;
    }
    else {
        pHeap loc;
        for (loc=array[location].next;loc!=NULL;loc=loc->next) {
            if ((loc->data)==key) {
                return true;
            }
        }
    }
		return false;
}


void insert_data(pHeap array, int data) {
    int location= data%MAX_SIZE;
		

    if (array[location].inputed==false) {//빈 데이터인 경우 바로 대입.
        array[location].data=data;
        array[location].inputed=true;
        array[location].next=NULL;
    }
    else {
        pHeap temp=(pHeap)malloc(sizeof(Heap));//아닌 경우 linkedlist형식
        if (temp==NULL) {
            return;
        }
        temp->data=data;
        temp->next=NULL;
        temp->inputed=true;

        pHeap loc,pre=NULL;
        for (loc=array[location].next;loc!=NULL;) {
            pre=loc;
						loc=loc->next;
        }
        if (pre==NULL) {
					array[location].next=temp;
				}
				else {
					pre->next=temp;
				}
    }
}

void remove_data(pHeap array) { 
    for (int i=0;i<MAX_SIZE;i++) {
        if (array[i].next!=NULL) {
            pHeap del;
            while (array[i].next!=NULL) {
                del=array[i].next;
                array[i].next=(array[i].next)->next;
                del->next=NULL;
                free(del);
            }
        }
    }
}

pHeap create_arrayheap() {
    pHeap temp = (pHeap)malloc(sizeof(Heap)*MAX_SIZE);
    if (temp==NULL) {
        return NULL;
    }
    else {
        for (int i=0;i<MAX_SIZE;i++) {
            temp[i].inputed=false;
        }
        return temp;
    }
}

//Binary Search: 퀵정렬 사용.

void quick_sort(int *data,int left, int right) {//확인
    int pivot=0,i=0,j=0;

    if (left<right) {
        i=left; j=right+1;
        pivot=data[left];
        do {
            do {
                i++;
            } while (data[i]<pivot);
            do {
                j--;
            } while(data[j]>pivot);
            if (i<j) {
                swap(&data[i],&data[j]);
            }
        } while (i<j);
        swap(&data[left],&data[j]);
        quick_sort(data,left,j-1);
        quick_sort(data,j+1,right);
    }
}

bool binary_search(int *array,int size,int data) {
    int left, right, mid;

		left=0;right=size-1;

		while (left<=right) {
			mid=(left+right)/2;
			if (array[mid]>data) {
				right=mid-1;
			}
			else if (array[mid]<data) {
				left=mid+1;
			}
			else {
				return true;
			}
		}
		return false;
}


int check_file_line(char *np) {//파일 줄 확인. 파일명이 존재하지 않으면 -1 리턴
  int line=0;
  char c[60];//임시저장소

  FILE *fep=fopen(np,"r");

  if (fep==NULL) {
    return -1;
  }

  while(!feof(fep)) {
    line++;
    fgets(c,60,fep);
  }
  fseek(fep, -1, SEEK_CUR);

  if (fgetc(fep)=='\n') {
    line--;
  }
  fclose(fep);
  return line;
}




int main(void) {
	char file_name[30];
    printf("Input file name : ");
    scanf("%s",file_name);
    rewind(stdin);

    FILE *fp = fopen(file_name,"r");

    if (fp==NULL) {
        return 1;
    }
    int line = check_file_line(file_name);
    int target;
    printf("Target number : ");
    scanf("%d",&target);
    rewind(stdin);
    int select;
    printf("Choose a searching method (Binary : 1 , Heap : 2 ) : ");
    scanf("%d",&select);
    rewind(stdin);

    if (select==1) {
        int datas[line];
        for (int i=0;i<line;i++) {
        fscanf(fp,"%d",&datas[i]);

        if (fgetc(fp)!='\n') {
            fseek(fp,-1,SEEK_CUR);
            }
        }
        quick_sort(datas,0,line-1);
        bool find=binary_search(datas,line,target);

        if (find==true) {
            printf("\n%d is found.\n",target);
        }
        else {
            printf("\n%d is not found.\n",target);
        }
        fclose(fp);

    }
    else if (select==2) {
        pHeap heap_data=create_arrayheap();
        int temp;
         for (int i=0;i<line;i++) {
            fscanf(fp,"%d",&temp);
            insert_data(heap_data,temp);

        if (fgetc(fp)!='\n') {
            fseek(fp,-1,SEEK_CUR);
            }
        }

        bool found=findkey(heap_data,target);

         if (found==true) {
            printf("\n%d is found.\n",target);
        }
        else {
            printf("\n%d is not found.\n",target);
        }
    }
    return 0;
}

