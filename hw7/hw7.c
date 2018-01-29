#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// int main(int argc, char *argv[])
// {
//     FILE *fpt;
//     int Terminal;
//     char c;
//     char strDev[100];

//     if (argc != 2) {
//         printf("Usage: devterm n, where n is the terminal number.\n");
//         return -1;
//     } else Terminal = atoi(argv[1]);

//     sprintf(strDev, "/dev/pts/%d", Terminal);

//     if ((fpt = fopen(strDev,"w")) == NULL) {
//         printf("Unable to open %s\n", strDev);
//         exit(0);
//     }
//     // write text to terminal
//     while(1)
//     {
//         // print text each 1s
//         fprintf(fpt,"Hello!  Scientia Est Potentia!!!\n");
//         sleep(1);
//     }
//     fclose(fpt);
 
//     exit(1);
// }
   



//  int x;
// int Magic(int z) { z=x*3; return(z);
// }
// int main() { int y;
// x=4; y=6; x=Magic(y);
//  printf("%d %d\n",x,y);
//  printf("%ld  %ld \n",(long int)(&x), (long int )(&y)  ); 
// }



// #include <stdio.h> 
// #include <unistd.h>
// main() 
// { int    i,j,k;
// k=0; 
// for (j=0; j<4; j++)
// k=k+j; 
// i=fork();
//     if (i == 0) 
//     for (i=3; i<k; i++)
//     j=j-i;
//     else i=k%3;
// printf("%d %d %d\n",i,j,k); 
// }




// #include <stdio.h> 
// #include <unistd.h>
// main() { 
//     int    i,j;
//     i=fork(); 
//     for (j=0; j<3; j++)
//     {
//      if(i==0 && j==0)
//     { sleep(3); printf("Cats\n"); }
//     else if (i == 0) {
//     sleep(2); printf("Dogs\n"); }
//     else {
//     sleep(2); printf("Raining\n"); }
// }
// }

// #include <stdio.h> 
// #include <signal.h>
// main() 
// { 
//     void   f(int);
//     int i; double *t,x[5];
//     signal(SIGSEGV,f); 
//     x[0]=0.0; 
//     t=0; 
//     for (i=1; i<5; i++)
//     { 
//         x[i]=(double)i+11.0; 
//         if (x[i-1] > 12.0)
//             *t=42.3;
//         printf("Ok\n"); 
//     }
// }
// void f(int signum) { printf("Bad!\n"); exit(SIGSEGV);
// }

#include <string.h>
#define MAXLETTERS 8
void usr_strfold(char *dest, const char *src);
int main(int argc, char const *argv[])
{
    char str[MAXLETTERS*2];
    int i=0, letter=0;
    int len=0;
    if (argc !=2)
        printf("usage: ./hw7 string\n");
    else
    {
        if(strlen(argv[1])>MAXLETTERS || strlen(argv[1])<7 )
        {
            printf("Lenght of string should be between %d and %d \n",7, MAXLETTERS);
            return 0;
        }
        else{
            usr_strfold(str, argv[1]);
            len=strlen(str);
            // print line
            for ( i = 0; i <len ; ++i)
            {
                if(i== (len/2))
                    printf("%s\n", str);
                else
                {
                    for (letter = 0; letter < len; ++letter)
                    {//print each letter
                        if (letter == (len/2))
                            printf("%c",str[i] );
                        else if(letter == i || letter == (len-i-1)) 
                            printf("%c",str[i] );
                        else
                            printf(" ");
                    }
                    printf("\n");
                }
            }
        }
    }
    return 0;
}

/*
*  @brief: usr_strfold:
*       This function is to generate the symmetrical string
*       for the output
*  @char *dest:
*       return the generated string
*  @char *src:
*       input the original string
*/
void usr_strfold(char *dest, const char *src)
{
    int len=strlen(src), i;
    for ( i = 0; i <len ; ++i)
    {
        dest[i]= dest[(2*len-2)-i]=src[i];
    }
    dest[2*len-1]='\0';
}