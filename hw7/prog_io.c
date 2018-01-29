#include <stdio.h>
#include <math.h>

int main(void)
{
    float f;
    int found = -1;
    char s[100];

    while (!feof(stdin)) {
        fgets(s, sizeof(s), stdin);
        found = sscanf(s, "%g", &f);
        if (found == 1) {
            fprintf(stdout, "sin[%g] = %f\n", f, sin(f));
            found = -1;
        }
    }
    return 0;
}

