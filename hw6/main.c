#include <stdio.h>
#include <stdlib.h>


// struct inventory { char name[30];
// int count; float price; } log[75];

//  main(int argc, char const *argv[])
// {
// 	FILE *fpt;
	
// 	fpt=fopen("out.txt","w");
// 	// initiakize log[75]
// 	fwrite(log, 75*sizeof(struct inventory),1,fpt );
// 	fclose(fpt);
	
// }

// int main(int argc, char const *argv[])
// {


// 	FILE *fpt;
// 	int word_count=0, total_count=0;
// 	unsigned char flag=0;
// 	char letter;
// 	int length=0;
// 	fpt=fopen(argv[1] ,"r");
// 	while(!feof(fpt))
// 	{
// 		fread( &letter,sizeof(char), 1 ,fpt);
// 		// printf("%c\n",letter );
// 		if(letter>=33 && letter <=126 )
// 		{
// 			if(!flag) flag=1;//found new length
// 			word_count++;	//word amount of a length
// 		}
// 	else		//check lengths 
// 		{		if(word_count>=3 && word_count<=15) {
// 					length++;
// 				total_count+=word_count;
// 				}//found end of length and clean data
// 			printf("length: %d word_count: %d\n",length, word_count );
// 			flag=0;
// 			word_count=0;
// 		}
// 	}
// 	printf("total words: %d\n", total_count);
// 	fclose(fpt);
// 	return 0;
// }



main() { 
double testd;
int testi; 
FILE *fpt; 
struct frog {
double *x,y;
}; 
struct frog turtle,*apple,tv[3];
testi=21; 
apple=&turtle; 
turtle.y=5.2; 
fpt=fopen("out3","w"); 
fwrite(apple,sizeof(struct frog),1,fpt); 
fclose(fpt);
apple->x=&testd;
fpt=fopen("out3","r");
fread(&(tv[1]),sizeof(struct frog),1,fpt);
fclose(fpt);
 *(turtle.x)=7.3;
  (*apple).y=3.6;
   turtle.y=1.5; 
   *(tv[1].x)=6.4; 
   printf("%lf \n",tv[1].y);
    }
