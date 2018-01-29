#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[])
{
   double **matrix;
   int i,j, m_rows=2, m_cols=3;
   
   //create matrix
   matrix= (double**) calloc(m_rows, sizeof(double*));
   for(i=0; i<m_rows; i++)
   	matrix[i]= (double*) calloc(m_cols, sizeof(double));
   //set last element's value to 5
    matrix[1][2]=5;
   //print matrix
   for(i=0; i< m_rows;i++)
   {
   	for(j=0;j<m_cols;j++)
	     printf("%2.0lf ",matrix[i][j]);
	printf("\n");
   }
   //free space
   for(i=0;i<m_rows;i++)
   	free(matrix[i]);

    return 0;
}
