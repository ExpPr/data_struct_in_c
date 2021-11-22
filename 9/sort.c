#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int sorted[1000];

void swap(int *a,int *b) {
    int temp=*a;
    *a=*b;
    *b=temp;
}

void select_sort(int *data, int size) {//확인
    int temp;
    for (int i=0;i<size-1;i++) {
        for (int j=i+1;j<size;j++) {
            if (data[i]>data[j]) {
                temp=data[i];
                data[i]=data[j];
                data[j]=temp;
            }
        }
    }
}

void bubble_sort(int *data, int size) {//확인
    int temp;
    for (int i=0;i<size-1;i++) {
        for (int j=0;j<size-1-i;j++) {
            if (data[j]>data[j+1]) {
                temp=data[j];
                data[j]=data[j+1];
                data[j+1]=temp;
            }
        }
    }
}

void insert_sort(int *data, int size) {//확인
    int i=0,j=0;
    int hold=0;

    for (i=1;i<size;i++) {
        hold=data[i];
        for (j=i;j>0&&hold<data[j-1];j--) {
            data[j]=data[j-1];
        }
        data[j]=hold;
    }
}

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

void merge(int *list,int i,int m,int n) {
   int l=i,j=m+1,k=i;

	 while (l<=m && j<=n) {
		 if (list[l]<=list[j]) {
			 sorted[k++]=list[l++];
		 }
		 else {
			 sorted[k++]=list[j++];
		 }
	 }

	 while (l<=m) {
		 sorted[k++]=list[l++];
	 }
	 while (j<=n) {
		 sorted[k++]=list[j++];
	 }

	 for (int a=i;a<=n;a++) {
		 list[a]=sorted[a];
	 }
   
}



void merge_sort(int *list, int low, int high) {//다시
    if (low<high) {
        int mid=(low+high)/2;
        merge_sort(list,low,mid);
        merge_sort(list,mid+1,high);
        merge(list,low,mid,high);
    }
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
    puts("");
    puts("");
    printf("Choose a sorting method to use (Selection : 0 , Insertion : 1, Bubble 2, Quick : 3, Merge : 4) : ");
    int select;
    scanf("%d",&select);
    rewind(stdin);

    int unsorted[line];
    for (int i=0;i<line;i++) {
        fscanf(fp,"%d",&unsorted[i]);

        if (fgetc(fp)!='\n') {
            fseek(fp,-1,SEEK_CUR);
        }
    }


    switch(select) {
        case 0:
            select_sort(unsorted,line);
            break;
        case 1:
            insert_sort(unsorted,line);
            break;
        case 2:
            bubble_sort(unsorted,line);
            break;
        case 3:
            quick_sort(unsorted,0,line-1);
            break;
        case 4:
            merge_sort(unsorted,0,line-1);
            break;
        default :
            printf("wrong input\n");
            fclose(fp);
            return 1;
    }

    puts("The numbers sorted : ");

    int q=line/10;
    int p=line%10;

    for (int i=0;i<q-1 && i>=0;i++) {
        for (int j=0;j<9;j++) {
            printf("%d,\t",unsorted[i*10+j]);
        }
        printf("%d\n",unsorted[i*10+9]);
    }

    for (int i=0;i<p-1;i++) {
        printf("%d,\t",unsorted[q*10+i]);
    }
    printf("%d\n\n",unsorted[line-1]);

    fclose(fp);
    return 0;

}
