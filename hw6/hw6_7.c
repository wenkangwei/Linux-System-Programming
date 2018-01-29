/* An example program to test shell redirection.  Run as 
 *
 *      depunt < test.txt > output.txt
 *
 *  to redirect stdin and stdout.
 * 
 *  Use the "diff" command to compare output.txt to expected.txt.  
 *
 * The program reads words from standard in, removes punctuation,
 * and prints the result to standard out.  It handles the following
 * punctuation symbols:
 *
 *      " ! ; : . ? , ( )
 *
 * The program ends when it sees an isolated period symbol:
 *
 *      .
 */

#include <stdio.h>

int main (int argc, char *argv[])
{
    char textin[80],wordout[80];
    int i,j;

    if (argc > 1)
    {
        printf("Usage:  depunct\n");
        exit(0);
    }
    while (1)
    {
        scanf("%s",textin);
        if (strcmp(textin,".") == 0)
            break;
        strcpy(wordout,textin);
        for (i=0; i<strlen(wordout); i++)
            if (wordout[i] == '.'  ||  wordout[i] == ','  ||
                    wordout[i] == '"'  ||  wordout[i] == ';'  ||
                    wordout[i] == '!'  ||  wordout[i] == '?'  ||
                    wordout[i] == '('  ||  wordout[i] == ')'  ||
                    wordout[i] == ':')
            {
                for (j=i; j<strlen(wordout)-1; j++)
                    wordout[j]=wordout[j+1];
                // fixed bug after subtracting i;
                i--;
                wordout[j]='\0';
            }
        printf("%s\n",wordout);
    }
    return 0;
}

