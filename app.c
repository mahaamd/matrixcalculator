#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define Max_size 20
struct Matrix
{
    float array[Max_size][Max_size];
    int m,n;
};
void menu();
void printMatrix(struct Matrix m);
void filereadmatrix1(struct Matrix *m1);
void filereadmatrix2(struct Matrix *m2);
void filewritematrix(struct Matrix *m1);

struct Matrix readMatrix()
{
    struct Matrix mat;
    printf("enter matrix row then column: ");
    scanf("%d",&mat.m);
    scanf("%d",&mat.n);
    printf("enter matrix:\n");
    for (int i = 0; i < mat.m; i++)
    {
        for(int j=0;j<mat.n;j++ )
        {
            scanf("%f",&mat.array[i][j]);
        }
    }
    return mat;
    
}

int addMatrix(struct Matrix *one,struct Matrix *two,struct Matrix *three)
{
    if (one->m!=two->m||one->n!=two->n)
    {
        return 0;
    }
    three->m=one->m;
    three->n=one->n;
    for (int i = 0; i < one->m; i++)
    {
        for(int j=0;j<one->n;j++)
        {
            three->array[i][j]=one->array[i][j]+two->array[i][j];
        }
    }
    
    return 1;
}
int subMatrix(struct Matrix *one,struct Matrix *two,struct Matrix *three)
{
        if (one->m!=two->m||one->n!=two->n)
    {
        return 0;
    }
    three->m=one->m;
    three->n=one->n;
    for (int i = 0; i < one->m; i++)
    {
        for(int j=0;j<one->n;j++)
        {
            three->array[i][j]=one->array[i][j]-two->array[i][j];
        }
    }
return 1;
}
int mulMatrix(struct Matrix *one,struct Matrix *two,struct Matrix *mull)
{
    if (one->n!=two->m)
    {
        return 0;
    }
    mull->m=one->m;
    mull->n=two->n;    
    int sum=0;
    for (int i = 0; i < one->m; i++)
    {
       for (int k = 0; k < two->n; k++)
       {
          sum=0;
          for (int j = 0; j < one->n; j++)
          {
            sum+=one->array[i][j]*two->array[j][k];
          }
          mull->array[i][k]=sum;
       }
   }
   return 1;
}
void transposematrix(struct Matrix *transpose)
{
    struct Matrix mytransepose;
    mytransepose.m=transpose->m;
    mytransepose.n=transpose->n;
    for (int i = 0; i < transpose->m; i++)
    {
        for (int j = 0; j < transpose->n; j++)
        {
            mytransepose.array[i][j]=transpose->array[i][j];
        }
    }
    int temp=transpose->m;
    transpose->m=transpose->n;
    transpose->n=temp;

    for (int i = 0; i < mytransepose.m; i++)
    {
        for(int j=0;j<mytransepose.n;j++)
        {
            transpose->array[j][i]=mytransepose.array[i][j];
        }
    }
    
}
float det(struct Matrix *mat)
{
    if (mat->m!=mat->n)
    {
        fprintf(stderr,"dementional error try again\n");
        menu();
    }
    
    float determinant;
    if (mat->m==1)
    {
        return mat->array[0][0];
    }
    if(mat->m==2)
    {
        return determinant=mat->array[0][0] * mat->array[1][1]-mat->array[0][1]*mat->array[1][0];
    }
    else
    {
        int sighn=1;
        struct Matrix minor,matr;
        float sum=0;
        minor.m=mat->m-1;
        minor.n=mat->n-1;
        int minor_col;
        int minor_row;
        for(int jcur=0;jcur< mat->m; jcur++)
        {
            minor_row=0;
            for (int i = 1; i < mat->m; i++)
            {
                minor_col=0;
                for(int j=0;j<mat->n;j++)
                {
                    if(jcur==j)
                        continue;
                    else    
                        minor.array[minor_row][minor_col]=mat->array[i][j];

                        minor_col++;  
                }
               minor_row++;
            }
                sum=sum+sighn*(mat->array[0][jcur] * det(&minor));
           
            sighn=-1*sighn;
           
        }

        return sum;
    }
}
struct Matrix inverse(struct Matrix mat)
{
    struct Matrix minor,co_matrix;
     minor.m=mat.m-1;
     minor.n=mat.n-1;
    //int array[mat.m-1][mat.n-1];
    int l=0,k=0;
    float d=det(&mat);
    if (d==0)
    {
        fprintf(stderr,"det is 0 so no inverse");
        menu();
    }
    float arr[mat.m][mat.n];
    co_matrix.m=mat.m;
    co_matrix.n=mat.n;
    int minor_row;
    int minor_col;
    int sum=0;
    for (int icur = 0; icur < mat.m; icur++)
    {
        for(int jcur=0;jcur< mat.n; jcur++)
        {
               minor_row=0; 
               
            for (int i = 0; i < mat.m; i++)
            {
                //minor_row=i;
               minor_col=0;
                for(int j=0;j<mat.n;j++)
                {

                    if(jcur==j||icur==i)
                        //minor_row--;
                        continue;
                              
                    else
                    {
                        
                        minor.array[minor_row][minor_col] = mat.array[i][j];
             
                    }
                   
                        minor_col++;
                        
                }

                if (icur!=i)
                {
                     minor_row++;
                }
              
            }
            co_matrix.array[l][k]=pow(-1,(l+k))*det(&minor);
            k++;
            if (k==mat.m)
            {
                k=0;
                l++;
            }
            
        }
        
    }
              
        for (int i = 0; i < mat.m; i++)
        {
            for (int j = 0; j < mat.n; j++)
            {
                 co_matrix.array[i][j]=(1/d)*co_matrix.array[i][j];
            }
        }
        
        transposematrix(&co_matrix);

         return co_matrix; 
}    
int main()
{
    //struct Matrix matrix1,matrix2,add,minus,mull,transe,inve;
    menu();

return 0;
}
void printMatrix(struct Matrix m)
{
    for (int i = 0; i < m.m; i++)
    {
        for (int j = 0; j < m.n; j++)
        {
            printf("%.2f ",m.array[i][j]);
        }
        putchar(10);
    }
    printf("%d ",m.m);
    printf("%d",m.n);
    putchar(10);    
}
void filereadmatrix1(struct Matrix *m1)
{
   //int rand();
   FILE *read;
   //struct Matrix m1;
   int scan;
   printf("enter 1st matrix row and column: ");
   scanf("%d%d",&m1->m,&m1->n);
   read=fopen("matrix.txt","r");
  for (int i = 0; i < m1->m; i++)
   {
       for(int j=0;j<m1->n;j++)
       {
           scan=fscanf(read,"%f",&m1->array[i][j]);
           if (scan==EOF)
           {
               break; 
           }
           
       }
   } 
fclose(read);
}
void filereadmatrix2(struct Matrix *m2)
{ 
   printf("enter 2nd matrix row and column: ");
   int scan1;
   FILE *read1;
   scanf("%d%d",&m2->m,&m2->n);
   read1=fopen("input2.txt","r");
  for (int i = 0; i < m2->m; i++)
   {
       for(int j=0;j<m2->n;j++)
       {
           scan1=fscanf(read1,"%f",&m2->array[i][j]);
           if (scan1==EOF)
           {
               break; 
           }
           
       }
   }
   fclose(read1);
}
void filewritematrix(struct Matrix *m1)
{
    FILE *write;
   write=fopen("mat","a");
   fwrite(m1->array,sizeof(struct Matrix),1,write);
   fclose(write);
}

void menu()
{
    struct Matrix matrix1,matrix2,add,minus,mull,transe,inv;
    //FILE *wf;
    int input;
    //puts("hi there");
    printf("enter '1' for adding two matrix : \nenter '2' for subtracting matrix :\nenter '3' for calculate transeport matrix :\nenter '4' for calculating determinant :\nenter '5' for calculating inverted matrix :\nenter '6' for matrix multiplation :\n");
    scanf("%d",&input);
    if (input==1)
    {
        int choose;
        printf("which one do you prefer? import your 'own' matrix(1) or use 'file' (2)'??\n");
        scanf("%d",&choose);
        if (choose==1)
        {
            matrix1=readMatrix();
            matrix2=readMatrix();  
        }
        else if(choose==2)
        {
            filereadmatrix1(&matrix1);
            filereadmatrix2(&matrix2);
            printMatrix(matrix1);
            printMatrix(matrix2);
        }
        int not=addMatrix(&matrix1,&matrix2,&add);
        if (not==1)
        {
            int c;
            printMatrix(add);
            printf("do you want to store resault in a file?? yes(1) no(2)");
            scanf("%d",&c);
            if (c==1)
            {
                filewritematrix(&add);
            }
                if(c==2)
                     exit(0);
            }
            else
                fprintf(stderr,"dimention error");
   
    }
    if (input==2)
    {
        int choose2;
        printf("which one do you prefer? import your 'own' matrix(1) or use 'file' (2)'??\n");
        scanf("%d",&choose2);
        if (choose2==1)
        {
            matrix1=readMatrix();
            matrix2=readMatrix();
        }
        else if(choose2==2)
        {
            filereadmatrix1(&matrix1);
            filereadmatrix2(&matrix2);
            printMatrix(matrix1);
            printMatrix(matrix2);
        }
        int not=subMatrix(&matrix1,&matrix2,&minus);
        if (not==1)
        {
            int c;
            printMatrix(minus);
            printf("do you want to store resault in a file?? yes(1) no(2)");
            scanf("%d",&c);
            if (c==1)
            {
                filewritematrix(&minus);
            }
                if(c==2)
                    exit(0);
            }
            else
                fprintf(stderr,"dimention error");
   
    }
    if (input==3)
    {
        int choose;
        printf("which one do you prefer? import your 'own' matrix(1) or use 'file' (2)'??\n");
        scanf("%d",&choose);
        if(choose==1)
            matrix1=readMatrix();

        else if(choose==2)
        {
            filereadmatrix1(&matrix1);
            printMatrix(matrix1);
        }
        transposematrix(&matrix1);
        printMatrix(matrix1);
        printf("do you want to store resault in a file?? yes(1) no(2)");
        int c;
        scanf("%d",&c);
        if (c==1)
            {
                filewritematrix(&minus);
            }
            if(c==2)
                exit(0);
            
    }
    if (input==4)
    {
        int choose;
        printf("which one do you prefer? import your 'own' matrix(1) or use 'file' (2)??\n");
        scanf("%d",&choose);
        if (choose==1)
            matrix1=readMatrix();
       
        else if (choose==2)
        {
            filereadmatrix1(&matrix1);
            printMatrix(matrix1);
        }    
        float deter=det(&matrix1);
        printf("\n%.2f\n",deter);
    }
    if (input==5)
    {
        int choose;
        int c;
        printf("which one do you prefer? import your 'own' matrix(1) or use 'file' (2)??\n");
        scanf("%d",&choose);
        if (choose==1)
            matrix1=readMatrix();
       
        else if (choose==2)
        {
            filereadmatrix1(&matrix1);
            printMatrix(matrix1);
        }
        if (matrix1.m==1&&matrix1.n==1)
        {
            printf("%.2f\n",1/matrix1.array[0][0]);
        }
        if (matrix1.m!=1&&matrix1.n!=1)
        {
            matrix1=inverse(matrix1);
            printMatrix(matrix1);
        }   
        printf("do you want to store resault in a file yes(1) no(2)??");
        scanf("%d",&c);
        if (c==1)
        {
            filewritematrix(&matrix1);
        }
            else
                exit(0);           

    }
    
    if (input==6)
    {
        int choose;
        printf("which one do you prefer? import your 'own' matrix(1) or use 'file' (2)'??\n");
        scanf("%d",&choose);
        if (choose==1)
        {
            matrix1=readMatrix();
            matrix2=readMatrix();
        }
        else if(choose==2)
        {
            filereadmatrix1(&matrix1);
            filereadmatrix2(&matrix2);
            printMatrix(matrix1);
            printMatrix(matrix2);
        }
        int not=mulMatrix(&matrix1,&matrix2,&mull);
        if (not==1)
        {
            printMatrix(mull);
            int c;
            printf("do you want to store resault in a file?? yes(1) no(2)");
            scanf("%d",&c);
            if (c==1)
            {
                filewritematrix(&mull);
            }
            else if(c==2)
                exit(0);
        }
        else
            fprintf(stderr,"dimention error");
    }
    
        
    
    

}