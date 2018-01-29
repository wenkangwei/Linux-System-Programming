#include <stdio.h>
#include <math.h>

int main(void)
{
    float f;
    int found = -1;

    while (!feof(stdin)) {
        found = fscanf(stdin, "%f", &f);
        if (found == 1) {
            f = asin(f);
            f = f*180/M_PI;
            fprintf(stdout, "f = %f\n", f);
            found = -1;
        }
    }
    return 0;
}

