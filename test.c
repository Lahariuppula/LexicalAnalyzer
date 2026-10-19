
#include <stdio.h>
#define MAX 10

int main()
{
    // Variable declaration
    int a = 10;
    float b = 3.14;
    char grade = 'A';
    char name[] = "Lahari";

    /* Array declaration */
    int arr[5] = {1, 2, 3, 4, 5};

    // Arithmetic operators
    a = a + 5;
    a++;
    a--;

    // Relational and logical operators
    if (a >= 15 && b != 0)
    {
        printf("Hello World\n");
    }
    else
    {
        printf("Invalid value\n");
    }

    // Array access
    arr[0] = 10;

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}