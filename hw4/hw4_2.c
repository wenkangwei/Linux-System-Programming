#include <stdio.h>
#include <malloc.h>

double sum(double** mr, int mr_rows, int mr_cols)
{
 double result=0;
 int i=0,j=0;
 for(i=0; i< mr_rows;i++)
  {
	for(j=0;j<mr_cols;j++)
		result+=mr[i][j];
  }

return result;
}

double** transpose(double **mr, int mr_rows, int mr_cols)
{
   double **transp;
   int i=0,j=0;
   // create transpose matrix
   transp= (double**)calloc(mr_cols, sizeof(double*));
   for(i=0; i< mr_cols;i++)
     {
	transp[i]=(double*) calloc(mr_rows, sizeof(double));
     }
   //transpose result matrix
   for(i=0; i< mr_rows;i++)
    {
	for(j=0;j<mr_cols;j++)
	   transp[j][i]= mr[i][j];

    }
   
   return transp;
}


int distribution(double **mr,int mr_rows, int mr_cols,
		 int *pos_cnt, int *neg_cnt)
{
  int zero_cnt=0;
  int i=0,j=0;
  for(i=0; i<mr_rows;i++)
   {
	for(j=0;j<mr_cols;j++)
	{
	  zero_cnt= mr[i][j]==0? zero_cnt+1: zero_cnt;
	  *pos_cnt= mr[i][j]>0?  *pos_cnt+1: *pos_cnt;
	  *neg_cnt= mr[i][j]<0?  *neg_cnt+1: *neg_cnt;

	}

   }


return zero_cnt;
}

double** multiply( double** m1,int m1_rows, int m1_cols, double** m2, int m2_rows, int m2_cols)
{
    int i=0, j=0,k=0 , sum=0;
    double **mr;
    mr= (double**) calloc(m1_rows, sizeof(double*));
    for(i=0;i< m1_rows;i++)
    	mr[i]= (double*) calloc(m2_cols,sizeof(double));
    for(i=0; i<m1_rows;i++) //scan mr matrix's rows
    	{
	  for(j=0;j<m2_cols;j++)//scan mr's cols
	  {
	    sum=0;
	    for(k=0;k<m2_rows;k++)
		    sum+=m1[i][k]*m2[k][j];
	    mr[i][j]=sum;
	  }
	}

  return mr;
}

void print_matrix(double** m, int m_rows, int m_cols)
{
   int i=0, j=0;
   for(i=0; i< m_rows;i++)
   {
   	for(j=0;j<m_cols;j++)
		printf("%1.0f ",m[i][j]);
	printf("\n");
   }
}

void free_matrix(double** m, int m_rows, int m_cols)
{
    int i=0, j=0;
    for(i=0; i<m_rows;i++)
	 free(m[i]);
}


int main(int argc, char *argv[])
{
    double **m1, **m2, **mr, **transp;
    int i=0, j=0, neg_cnt=0, pos_cnt=0,zero_cnt=0;
    int m1_rows=1, m1_cols=3, m2_rows=3,m2_cols=2, mr_rows=1, mr_cols=2;

    m1= (double**) calloc(m1_rows, sizeof(double*));
    for(i=0;i<m1_rows;i++)
    	m1[i]=(double*) calloc(m1_cols, sizeof(double));

    m2= (double**) calloc(m2_rows, sizeof(double*));
    for(i=0;i<m2_rows;i++)
    	m2[i]=(double*) calloc(m2_cols, sizeof(double));

    mr= (double**) calloc(mr_rows, sizeof(double*));
    for(i=0;i<mr_rows;i++)
    	mr[i]=(double*) calloc(mr_cols, sizeof(double));

    for(i=0; i< m1_rows;i++)
    {
       printf("m1 row1,");
       for(j=0;j<m1_cols;j++)
	  {
	     printf("cols %d: ",j);
	     scanf("%lf",&m1[i][j]);
	  }
    }
    for(i=0; i< m2_rows;i++)
    {
       printf("m2 row1,");
       for(j=0;j<m2_cols;j++)
	  {
	     printf("cols %d: ",j);
	     scanf("%lf",&m2[i][j]);
	  }
    }

  mr= multiply(m1,m1_rows,m1_cols,m2, m2_rows,m2_cols);
  transp=transpose(mr, mr_rows,mr_cols);
  printf("\nm1:\n");
  print_matrix(m1,m1_rows,m1_cols);
  printf("\nm2:\n");
  print_matrix(m2,m2_rows,m2_cols);
  printf("\nmr:\n");
  print_matrix(mr,mr_rows,mr_cols);
  printf("\ntranspose:\n");
  print_matrix(transp,mr_cols,mr_rows);

 printf("sum: %1.0f \n",sum(mr,mr_rows,mr_cols));
 print_matrix(transpose(mr, mr_rows,mr_cols),mr_cols,mr_rows );
 zero_cnt=distribution(mr,mr_rows,mr_cols,&pos_cnt,&neg_cnt );
 printf("zero cnt: %d, positvie cnt: %d. negative cnt: %d\n", zero_cnt, pos_cnt,neg_cnt );


//free space
free_matrix(m1, m1_rows,m1_cols);
free_matrix(m2, m2_rows,m2_cols);
free_matrix(mr, mr_rows,mr_cols);

return 0;
}
