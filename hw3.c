#include <stdio.h>
// double d[3],*e; 
//  int i,*j; 
//  char a,*b,c[3];
//   i=3; j=&i; 
//   d[0]=4.2; 
//   e=&(d[1]); 
//   *(e-1)=1.5;
//    e[1]=2.3;
//     	printf("Label   address   value\n");
//     for (i=0; i<5; i++) 
//     	c[i%3]=(char)(*j+i); b=&a; *b=c[2]; 
    
// 	 		printf("*e  %ld  %lf\n ", e, *e);
// 	 		printf("i   %ld  %d\n ", &i, i);
// 	 		printf("*j  %ld  %d\n ", j, *j);
// 	 		printf("a  %ld  %d\n ", &a, a);
// 	 		printf("*b   %ld  %d\n ", b, *b);
// 			 // memory map
// 	 		for (int r = 0; r < 3; ++r)
// 	 		{
// 	 			printf("d[%d]  %ld  %lf\n",r,&d[r],d[r] );
// 	 			printf("c[%d]  %ld  %d\n",r,&c[r],c[r] );
// 	 		}


int main(int argc, char const *argv[])
{

  int array[5], what[5];
int *ptr;
int offset, j;
for (j=0; j<5; j++)
array[j] = 2 * j + 10;
ptr = &(array[0]);
offset = 4;
what[0] = *(ptr + offset);
what[1] = ptr[offset - 3];
what[2] = *(array + offset);
what[3] = *ptr+offset;
what[4] = *ptr++;
printf("Label    address   value\n");
for (int i = 0; i < 5; ++i)
{
printf("what[%d]  %ld \n", );
}
	return 0;
}