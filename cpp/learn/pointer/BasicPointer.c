#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a = 10;
    int *b = &a; // Pointer to integer
    printf("Size of int: %lu\n", sizeof(int));
    printf("Size of &a: %lu\n", sizeof(&a));
    printf("Size of b: %lu\n", sizeof(b));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));
    *c = 20;
    *d = 30;
    printf("%p\n", c);
    printf("%p\n", d);
    printf("%u\n", (unsigned int)c);
    printf("%u\n", (unsigned int)d);
    free(c);
    free(d);

    return 0;
}