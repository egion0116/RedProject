#include <stdio.h>
#include <stdlib.h>

void Test(int* restrict a, int* restrict b, int* restrict c)
{
    *a += *c;
    *b += *c;

    printf("%d\n", *a);
}

int main(void)
{
    int val = 10;

    Test(&val, &val, &val);

    return 0;   
}