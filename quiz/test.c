#include <stdio.h>

int max_return(int *min_index, int *max_index, int c[],int length) {
    int sum=0;
    int max=0;
    for (int i=0;i<length;i++) {
        sum=0;
        for (int j=i;j<length;j++) {
            sum=sum+c[j];
            if (max<sum) {
                max=sum;
                *min_index=i;
                *max_index=j;
            }
        }
    }
    return max;
}


int main(void) {

    int a[]={27,6,-50,21,-3,14,16,-8,42,33,-21,9};

    int min_index, max_index, max=max_return(&min_index,&max_index,a,sizeof(a)/sizeof(int));
    printf("출력 결과 : %d ~ %d 까지의 합이 max = %d \n",a[min_index],a[max_index],max);
   


    return 0;
}