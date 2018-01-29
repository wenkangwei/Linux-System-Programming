 #include <stdio.h>
 #include <string.h>
// main() 
// {
//  int i,j,k,swap;
//  char c[8]; 
//  c[0]='f';
//  c[1]='r'; 
//  c[2]='o';
//  c[3]='g'; 
//  c[4]=0;
//  for (i=0; i<4; i++)
//  	{
//  	 k=i; 
//  	 for (j=i+1; j<4; j++) 
//  	 	if (c[j]-c[k] < 10) 
//  	 		k=j; 
// 	 	swap=c[i]; 
// 	 	c[i]=c[k]; 
// 	 	c[k]=swap; 
//  	 }
// printf("   Address         label value \n");
// for ( i = 0; i <=4; ++i)
//  	 {
//  	 	printf("  %ld  c[%d]  %c \n", (long int)&c[i], i, c[i]);
//  	 } 	 

// } 

void matrix_Multiply(char *a, char *b, char *c)
{

	int sum=0;
	for (int c = 0; c < 2; ++c) 	//scan b column
	{
		for(int r1=0; r1<2;r1++) 	//scan a row
		{

			for (int n= 0; n < 3; ++n) //scan b row
			{
				sum+=a[n][c]*b[r1][c];
			}
			c[r1][c]=sum;
		}
	}
}

int main(int argc, char const *argv[])
{
	float a[2][3]={1.1,0,1.1,0,1.1,0}, b[3][2]={1.1,0,1.1,0,1.1,0},c[2][2];
	float sum=0;
	matrix_Multiply(a,b,c);
	printf("a:\n");
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			printf(" %f",a[i][j] );
		}
		printf("\n");
	}
	printf("b: \n");
for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			printf(" %f",b[i][j] );
		}
		printf("\n");
	}
	printf("c:\n");
for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			printf(" %f",c[i][j] );
		}
		printf("\n");
	}

	return 0;
}


// main()
// {
// 	int x[2][3][2];
// 	int i,j,k;
// 	for (i=0; i<3; i++) 
// 		for (j=0; j<2; j++) 
// 			x[0][i][j]=i*3+j; 
// 	for (k=0; k<2; k++) 
// 		for (j=0; j<2; j++) 
// 			x[1][k][j]=x[0][j][k]-1;

// 	printf("Address         Label       value\n");
// 	for ( i = 0; i < 2; ++i)
// 		for(j=0;j<3;j++)
// 			for (k = 0; k < 2; ++k)
// 			{
// 				printf("%ld   x[%d][%d][%d]   %d \n",(long int )&x[i][j][k],i,j,k, x[i][j][k] );
// 			}

// }


// main()
// {
//  int i,j,t; 
//  char name[50];
//   printf("What is your name? "); 
//   scanf("%s",name); t=0; 
//    for (i=0; i<strlen(name);i++)
//    for (j='a'; j<=name[i]; j++) 
//    	t++; 
//    printf("%d\n",t); 

// }

// main()
// {

// 	char s[10], t[10];
// 	int i,j;
// 	strcpy(s,"frog");
// 	for ( i = 0; i < strlen(s); i++)
// 	{
// 		t[i]=s[i];
// 		printf("%d\n",t[i] );
// 	}
	
// 	j=0;
// 	for ( i = 0; i < strlen(t); i++)
// 		j=j+(int)t[i];	

// 	printf("%d\n",j );

// }

// main()
// {
// 	int name_type=0,sub_index=0;
// 	char name[50], first[25], last[25];
// 	char *name_pt;
// 	printf("What is your name? \n");
// 	scanf("%s", name);
// 	// clean buffers
// 	for (int i = 0; i < 25; ++i)
// 	{
// 		first[i]=0;
// 		last[i]=0;
// 	}
// 	name_pt =name;
// 	while(*name_pt!='\0')
// 	{

// 		if (*name_pt<='Z'&&*name_pt>='A')
// 		{
// 			name_type++;
// 			sub_index =0;
// 		}
// 		if (name_type==1)
// 		{
// 			first[sub_index]=*name_pt;
// 			sub_index++;
// 		}
// 		else
// 		{
// 			last[sub_index]=*name_pt;
// 			sub_index++;
// 		}
// 		name_pt++;
// 	}

// 	printf("\n first name: \n");
// 	for (int i = 0; first[i]; ++i)
// 	{
// 		printf("%c", first[i] );
// 	}
// 	printf("\n last name: \n");
// 	for (int i = 0; last[i]; ++i)
// 	{
// 		/* code */
// 		printf("%c", last[i] );
// 	}
// 	printf("\n");
// }

// int *funcs(int *i, int *j)
// {
// 	*j=*i+*j;
// 	printf("%d\n",*j );
// 	return j;
// }

// int main(int argc, char const *argv[])
// {
// 	int *(*pt)(int*, int*);
// 	int i=9,j=8;
// 	pt=&funcs;
// 	*(*pt)(&j,&i);
// 	return 0;
// }


// int is_Vowel(char c)
// {
// 	return c=='a'||c=='e'||c=='i'||c=='o'||c=='u';
// }

// int main(int argc, char const *argv[])
// {
// 	char input[80]={}, output[80]={};
// 	char *string_pt;
// 	int index=0;
// 	printf("Enter a string: ");
// 	scanf("%s", input);
// 	string_pt=input;
// 	while(*string_pt!='\0')
// 	{
// 		if (!is_Vowel(*string_pt))
// 		{
// 			output[index]=*string_pt;
// 			index++;
// 		}
// 		string_pt++;
// 	}
// 	printf("output:\n");
// 	for (int i = 0; output[i]; ++i)
// 	{
// 		printf("%c", output[i]);
// 	}
// 	printf("\n");	
// 	return 0;
// }

// int main(int argc, char const *argv[])
// {
// 	char input[80]={}, filename[20]={}, suffix[20]={};
// 	char *string_pt;
// 	int index=0;
// 	printf("Enter a filename: ");
// 	scanf("%s", input);	
// 	string_pt=input;
// 	while(*string_pt!='.')
// 	{
// 		filename[index]=*string_pt;
// 		string_pt++;
// 		index++;
// 	}
// 	filename[index]='\0';
// 	index=0;
// 	if (*string_pt=='.')
// 	{
// 		string_pt++;
// 		do
// 		{
// 		 suffix[index]= *string_pt;
// 		 index++;
// 		 string_pt++;
// 		}
// 		while(*string_pt!='\0');
// 	}


// 	printf("\nfilename:\n");
// 	for (int i = 0; filename[i]!='\0'; ++i)
// 	{
// 		printf("%c", filename[i]);
// 	}

// 	printf("\nsuffix:\n");
// 	for (int i = 0; suffix[i]!='\0'; ++i)
// 	{
// 		printf("%c", suffix[i]);
// 	}
// 	printf("\n");
// 	return 0;
// }

// void operate(int *a, int *b)
// {
// 	int mask=0x1FE0; //mask 0b0001 1111 1110 0000
// 	*b&=~(mask<<4); //clean 9~16bits
// 	mask&=*a;		//get5~9 bits of a 
// 	mask<<=4;
// 	*b|=mask;		//set 9~16 bits
// 	printf("%d, mask: %x\n", *b, mask);
// }

// int main(int argc, char const *argv[])
// {
// 	int mask=0x1FE0; //mask 0b0001 1111 1110 0000
// 	int a=10, b=1;
// 	operate(&a,&b);

// 	return 0;
// }


// int is_Set(int b)
// {
// 	int mask=0xF8; //0b1111 1000 3~7 bits are 1
// 	return ((b&mask)==mask && (b&((mask)<<5))==0) ? 1:0;
// }

// int main(int argc, char const *argv[])
// {
// 	int a=0,b=(0xFFF8);
// 	if (is_Set(b))
// 	{
// 		a=12;
// 	}
// 	printf("a: %d\n", a);
// 	return 0;
// }


// int main(void)
// {
// int i;
// char c[80];
// char *pt;
// int n=0;
// int mask=0x0F;
// int bits_order=0;
// printf("Input> ");
// fgets(c, sizeof(c), stdin);
// pt=c;
// while(*pt!='\0')
// {

// 	if (*pt<='9'&& *pt>='0')
// 	{
// 		mask=(*pt-48);
// 		n|=mask<<(4*bits_order);
// 	}
// 	if (*pt>='A'&& *pt<='F')
// 	{
// 		mask=(*pt-55);
// 		n|=mask<<(4*bits_order);
// 	}
// 	bits_order++;
// 	pt++;
// }
// printf("You enter: %s\n", c);
// printf("Result:\n");
// printf("0x%X\n",n );


// }

// #define uchar unsigned char
// int usr_strcp(char *dst, char *sub, int dst_len)
// {
// 	int index=0;
// 	// check whether the dst array is a correct string
// 	while(dst[index]!='\0' && index< dst_len-1)
// 		index++;
// 	//if it is string
// 	if (dst[index]=='\0')
// 	{
// 		dst=&dst[index];					//move pointer to position of '\0' character
// 		while(*sub!='\0'&& index< dst_len-1)	//check boundary
// 		{
// 			*dst=*sub;
// 			dst++;
// 			sub++;
// 			index++;
// 		}
// 		*dst='\0';
// 		return 0;
// 	}


// 	return 1;
// }


// int extract_subStr(char esc_char,const char *str_pt, char *subStr, int len)
// {
// 	char str_temp[80];
// 	uchar esc_cnt=0; //used to check how many same escape characters are detected.
// 	int index=0;
// 	//stop extracting substring if substring is longer than destination array or 
// 	// detected 2 escape characters, or the str_pt is at the end of source string

// 	//copy substring to buffer
// 	while(esc_cnt!=2&& index<80-1 &&*str_pt!='\0')
// 	{
// 		if(*str_pt==esc_char) 
// 		{
// 			esc_cnt++;
// 			str_pt++;
// 		}
// 		//start extracting substring when the first escape character is detected
// 		if(esc_cnt==1)
// 		{
// 			str_temp[index] =*str_pt;	//extract character and substring index ++
// 			index++;
// 		}
// 		str_pt++;						//check next character in source string

// 	}
// 	if( esc_cnt==2)
// 	{
// 		printf("Copying string \n");
// 		str_temp[index] ='\0';
// 		usr_strcp(subStr,str_temp,len);	//copy substring to the array.
// 		return 0;
// 	}
// 	else 
// 	{
// 		printf("esc_cnt: %d\n",esc_cnt );
// 		return 1;
// 	}
// }


// int main(int argc, char const *argv[])
// {
// 	char c[20]="" , a[80]="ab%cd%e*k*l$asd$mnc$", b[10]="jh*kl*l";

// 	// c[1]='\0';
// 	if(!extract_subStr('%',a,c,80))
// 	{
// 	printf("result: %s\n",c );
// 			printf("a: %s\n",a );
		
// 	}else{
// 		printf("Invalid string\n");
// 	}

// 	if(!extract_subStr('*',a,c,80))
// 		{
// 		printf("result: %s\n",c );
			
// 		}else{
// 			printf("a: %s\n",a );
// 			printf("Invalid string\n");
// 		}
// if(!extract_subStr('$',a,c,80))
// 		{
// 		printf("result: %s\n",c );
			
// 		}else{
// 			printf("a: %s\n",a );
// 			printf("Invalid string\n");
// 		}
// 	return 0;
// }