// Using fflush on stdin does not work for Linux
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char s[100];

    printf("\nEnter a String -> ");
    fscanf(stdin, "%s", s);
    printf("%s\n", s);

    printf("\nEnter a String -> ");
    fscanf(stdin, "%s", s);
    printf("%s\n", s);

    getchar();

    fflush(stdin);
    printf("\nEnter a String -> ");
    fscanf(stdin, "%s", s);
    fflush(stdin);
    printf("%s\n", s);

    printf("\nEnter a String -> ");
    fscanf(stdin, "%s", s);
    fflush(stdin);
    printf("%s\n", s);

    return 0;
}

