#include <stdio.h>

int main(void)
{
    int i = 0;
    char s[100];
    int p, n = -1;

    printf("prog_i input: 2 ^ p = n\n");
    while (!feof(stdin))
    {
        fgets(s, sizeof(s), stdin);
        sscanf(s, "2 ^ %d = %d", &p, &n);
        printf("s[%d] = %d\n", i++, n);
    }
    return 0;
}

