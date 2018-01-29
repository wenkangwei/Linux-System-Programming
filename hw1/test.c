#include <stdio.h>
#include <stdlib.h>


 // bitcount: count 1 bits in x
// int bitcount(unsigned x)
// {
// int bits;

// for (bits = 0; x != 0; x >>= 1)
// if (x & 01)
// bits++;
// return bits;
// }

// int bitcount_V2(unsigned x)
// {
// int bits=0;
// while(x!=0)
// {
// 	x&=(x-1);
// 	bits++;	
// }

// return bits;
// } 
 // int main(int argc, char const *argv[])
 // {


 // 	// uchar x,y,z;
 // 	// x=15;
 // 	// y=35;
 // 	// z=133;
 // 	// x=x|64;
 // 	// y=y&3;
 // 	// z=~z;
 // 	// printf("%d, %d, %d\n",x,y,z );


 // 	// int x=7;
 // 	// x=(x|16)<<1;
 // 	// printf("%d\n", x);

	// // char i;
	// // double d;
	// // int t;
	// // t=0;
	// // for ( i = 'z'; i >= 'w'; i--)
	// // 	for (d = 1.0; d <=1.5; d+=0.1)
	// // 		if(d-1.3>0)
	// // 			t++;

	// // printf("%d\n", t);

 // 	// int i,j;
 // 	// j=0;
 // 	// for ( i = 1; i < 100; i<<=1)
 // 	// {
 // 	// 	if(i%5>1)
 // 	// 		j=j|i;
 // 	// 	printf("%d, %d \n",i,j );

 // 	// }


 // 	int i,j,k;
 // 	j=0;
 // 	k=32;
 // 	for ( i = 100; i >0; i-=10)
 // 	{
 // 		if(k/4>0)
 // 			j=j|k;
 // 		if(i<=70 && i>=40)
 // 			k<<=1;
 // 		else
 // 			k=k>>1;
 // 		printf("%d %d %d \n",i,j,k );
 // 	}

 // // 	char c[80];
	// // int n=0,i;

	// // printf("Enter a three-digit nonnegative number: ");
	// // fgets(c, sizeof(c), stdin);
 // // 	for (i = 0; i<=2; ++i)
 // // 	{
 // // 		n*=10;
 // // 		n+=c[i]-48;
 		
 // // 	}
 
 // // 	printf("The number is %d \n", n);
 // 	return 0;
 // }


int main(int argc, char const *argv[])
{
	void *a;
	char *b;
	b= (char *) malloc(sizeof(char));
	a=malloc(sizeof(int));
	// printf("address: a %x   b: %x\n", a ,b);
	a++;
	b++;
	printf("address: a %x   b: %x\n", a ,b);

	return 0;
}