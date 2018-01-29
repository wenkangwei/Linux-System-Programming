#include <stdio.h>
#include <math.h>

int main(void)
{
    int i, found = -1;;
    char s[100];
    float f;

    while (!feof(stdin)) {
        fgets(s, sizeof(s), stdin);
        found = sscanf(s, "%d", &i);
        if (found == 1) {
            f = (float)i * M_PI / 180;
            fprintf(stdout, "%f\n", sin(f));
            found = -1;
        }
    }
    return 0;
}

