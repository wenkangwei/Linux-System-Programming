   

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE *fpt;
    int Terminal;
    char strDev[100];

   char c;

    if (argc != 2) {
        printf("Args = %d.  Usage: devterm n, where n is the terminal number.\n", argc-1);
        return -1;
    } else Terminal = atoi(argv[1]);

    sprintf(strDev, "/dev/pts/%d", Terminal);

    if ((fpt = fopen(strDev,"r")) == NULL) {
        printf("Unable to open %s\n", strDev);
        return(1);
    }

    do {
        fscanf(fpt, "%c", &c);
        printf("%c\n", c);
    } while (c != 'q');

    fclose(fpt);
    return 0;
}
