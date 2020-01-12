#include <stdio.h>
 
#define ARR_LEN 255 /*数组长度上限*/
#define elemType int /*元素类型*/
 
/* 冒泡排序 */
/* 1. 从当前元素起，向后依次比较每一对相邻元素，若逆序则交换 */
/* 2. 对所有元素均重复以上步骤，直至最后一个元素 */
/* elemType arr[]: 排序目标数组; int len: 元素个数 */
void bubbleSort (elemType arr[], int len) {
    elemType temp;
    int i, j;
    for (i=0; i<len-1; i++) /* 外循环为排序趟数，len个数进行len-1趟 */
        for (j=0; j<len-1-i; j++) { /* 内循环为每趟比较的次数，第i趟比较len-i次 */
            if (arr[j] > arr[j+1]) { /* 相邻元素比较，若逆序则交换（升序为左大于右，降序反之） */
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
}
 
int main (void) {
    elemType arr[ARR_LEN] = {3,5,1,-7,4,9,-6,8,10,4};
    int len = 10;
    int i;
     
    bubbleSort (arr, len);
    for (i=0; i<len; i++)
        printf ("%d\t", arr[i]);
    putchar ('\n');
     
    return 0;
}