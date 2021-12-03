#include <stdio.h>

int** ret() {
    static int test[3][3]={{1,2,3},{4,5,6},{7,8,9}};
    return test;
}

int main(void) {
    int **test=ret();

    for (int i=0;i<3;i++) {
        for (int k=0;k<3;k++) {
            printf("%d ",test[i][k]);
        }
        puts("");
    }
    return 0;
}