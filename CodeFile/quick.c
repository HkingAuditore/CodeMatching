#include<stdio.h>

void sort(int * a, int len) {
    if( len <= 1 ) return;

    int i=0, j=len-1, t, temp = a[0];
    while( i<j ) {
        while( a[j]>temp && j>i ) j--; a[i] = a[j];
        while( a[i]<=temp && i<j ) i++; a[j] = a[i];
    }
    a[i] = temp;
    sort(a, i);
    sort(a+i+1, len-i-1);

    return;
}

int main(void) {
    int i, a[13] = {-100, 4, 6, -10, 9, 46, -4, 3, 6, 5, 8, 44, 20};
    sort(a, 13);
    for(i=0; i<13; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}