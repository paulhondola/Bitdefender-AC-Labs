// stack_frame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <stdio.h>

int aduna(int* array, int len)
{
    int i, result = 0;

    if (array == NULL)
    {
        printf("array null\n");
        return 0;
    }
    for (i = 0; i < len; i++)
    {
        result += array[i];
    }
    return result;
}


int test(int a, int b, int c)
{
    int local1, status;

    status = scanf_s("%d", &local1);
    if (status != 1)
    {
        printf("eroare scanf\n");
        return 0;
    }

    local1 = local1 * (a + b + c);

    return local1;
}


int main()
{
    int result;
    int array[] = { 1,2,3,4,5,6,7,8,9,10 };

    result = test(1, 2, 3);
    printf("test  -> %d\n", result);
    result = aduna(array, sizeof(array) / sizeof(int));
    printf("aduna -> %d\n", result);
}
