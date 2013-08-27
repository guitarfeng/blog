#include <stdio.h>


int getMax(int a, int b) {  
    int c = a - b;  
    int k = (c >> 31) & 0x1;  
    return a -  k * (a - b);  
}


int main()
{
    int a, b;
    while (1) {
        scanf("%x %x", &a, &b);
        printf("%d, %d\n", a, b);
        int r1 = getMax(a, b);
        printf("F1: %x == %d\n", r1, r1);
        int r2 = a-((a-b)&((a-b)>>31));
        printf("F2: %x == %d\n", r2, r2);
    }
    return 0;
}

