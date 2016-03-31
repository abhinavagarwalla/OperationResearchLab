#include<stdio.h>

float determinant(float f[200][200],int x)
{
    int pr,c[20],j,p,q,t;
    float d=0,b[200][200];
    if(x==2)
    {
     d=0;
     d=(f[0][0]*f[1][1])-(f[0][1]*f[1][0]);
     return(d);
    }
    else
    {
     for(j=0;j<x;j++)
     {
       int r=0,s=0;
       for(p=0;p<x;p++)
       {
         for(q=0;q<x;q++)
         {
           if(p!=0&&q!=j)
           {
             b[r][s]=f[p][q];
             s++;
             if(s>x-2)
             {
               r++;
               s=0;
             }
           }
         }
       }
       for(t=0,pr=1;t<=(1+j);t++)
         pr=(-1)*pr;
       c[j]=pr*determinant(b,x-1);
     }
     for(j=0,d=0;j<x;j++)
     {
       d=d+(f[0][j]*c[j]);
     }
     return(d);
    }
}

int fact(int n)
{
    if(n==0)return (1);
    else return(n*fact(n-1));
}
int combo[20][20];
int k=0;
void combinationUtil(int arr[], int data[], int start, int end, int index, int);
void printCombination(int arr[], int n, int r)
{
    int data[r];
    combinationUtil(arr, data, 0, n-1, 0, r);
}
void combinationUtil(int arr[], int data[], int start, int end, int index, int r)
{
    int j;
    if (index == r)
    {
     for(j=0;j<r;j++)
       combo[k][j]=data[j];
     k++;
     return;
    }
    int i;
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
     data[index] = arr[i];
     combinationUtil(arr, data, i+1, end, index+1, r);
    }
}
int main()
{
    int nota=0;
    int flag=0;
    int M,N,i,j,q=0;
    float det;
    printf("Number of equations : ");
    scanf("%d",&N);
    printf("Number of variables : ");
    scanf("%d",&M);
    int val=fact(M)/(fact(N)*fact(M-N));
    printf("Total combinations possible = %d\n",val);
    float a[N][M+1];
    float tempt[N][M+1];
    float b[200][200];
    for(i=0;i<N;i++)
    {
     printf("Enter eqn. %d: \n",i+1);
     printf("Enter coefficient of equations no %d:\n",i+1);
     for(j=0;j<=M;j++)
     {
	printf("\nFor Cofficient %d: ", j+1);
       scanf("%f",&a[i][j]);
       tempt[i][j]=a[i][j];
	printf("Input Taken");
     }
printf(",");
    }
    
    printf("Input of equations is done");
    int R = N;
    int C = M;
    int rank = C;
  for (int row = 0; row < rank; row++)
  {
    if (tempt[row][row])
    {
    for (int col = 0; col < R; col++)
    {
      if (col != row)
      {
        double mult = (double)tempt[col][row] /
                  tempt[row][row];
        for (int i = 0; i < rank; i++)
        tempt[col][i] -= mult * tempt[row][i];
      }
    }
    }
    else
    {
      int reduce = 1;
      for (int i = row + 1; i < R; i++)
      {
        if (tempt[i][row])
        {
          //swapIt(row, i, rank);
          for (int i = 0; i < rank; i++)
          {
            float temp1 = tempt[row][i];
            tempt[row][i] = tempt[i][i];
            tempt[i][i] = temp1;
          }
          reduce = 0;
          break ;
        }
      }
      if (reduce)
      {
        rank--;
        for (int i = 0; i < R; i ++)
          tempt[i][row] = tempt[i][rank];
      }
      row--;
    }
  }
  
  printf("rank of matrix = %d\n", rank);
  if(rank<M){N=rank;}
    int ismax=0;
    float maxm[M];
    printf("Enter 0 for minimisation and 1 for maximisation : ");
    scanf("%d", &ismax);
    printf("Enter the coefficient for optimisation:\n");
    for(i=0;i<M;i++)
    {
     scanf("%f",&maxm[i]);
    }
    for(i=0;i<N;i++)
    {
     for(j=0;j<=M;j++)
     {
       printf("%f ",a[i][j]);
     }
     printf("\n");
    }
    int arr[M];
    for(i=0;i<M;i++)
     arr[i]=i;
    int s=sizeof(arr)/sizeof(arr[0]);
    printCombination(arr,s,N);
    float solution[val][M];
    for(i=0;i<val;i++)
    {
     for(j=0;j<M;j++)
       solution[i][j]=0;
    }
    int p;
    for(p=0;p<val;p++)
    {
     for(j=0;j<N;j++)
     {
       for(i=0;i<N;i++)
       {
         b[i][j]=a[i][combo[p][j]];
       }
     }
     for(i=0;i<N;i++)
       b[i][N]=a[i][M];
     det=determinant(b,N);
     float sol[N];
     int p,q,v;
     int k=0;
     float c[200][200];
     for(i=0;i<N;i++)
     {
       for(v=0;v<N;v++)
       {
         for(j=0;j<N;j++)
         {
           c[v][j]=b[v][j];
         }
       }
       for(j=0;j<N;j++)
       {
         c[j][k]=b[j][N];
       }
       k++;
       sol[i]=determinant(c,N)/det;
     }
     for(i=0;i<N;i++)
       for(j=0;j<N;j++)
       {
         solution[q][combo[q][j]]=sol[j];
       }
       q++;
     }
     int total=0;
     int temp=0;
     int tb=0;
     int h;
     for(i=0;i<val;i++)
     {
       for(j=0;j<M;j++)
       {
         if ((solution[i][j]>1000)||(solution[i][j]<-1000)) flag=1;
         printf("%5.2f ",solution[i][j]);
         if (solution[i][j]>=0) temp++;
       }
       if (temp==M) {total++; printf("BFS");}
       else if (flag==1) {tb++; printf("Not Basic Solution");}
       else printf("Basic Solution");
       temp=0;
       flag=0;
       printf("\n");
     }
     float max=0;
     float min = 100000;
     int f=0;
     int non_bfs=0;
     int opx = 0;
     float max2 = 89;
     for(i=0;i<val;i++)
     {
       f=0;
       for(j=0;j<M;j++)
       {
         if(solution[i][j]>=0)
         {
           f++;
         }
       }
       if(f==M)
       {
         float value=0;
         for(h=0;h<M;h++)
         {
           value=value+solution[i][h]*maxm[h];
         }
         if(ismax)
         {
           if(max<=(value))
           {
             max2=max;
             max=value;
             opx=i;
           }
         }
         else
         {
           if(min>=value)
           {
	     max2=min;
             min=value;
             opx=i;
           }
         }
       }
     }
     printf("Total Number of Basic Solutions = %d \n", val-tb);
     printf("Total Number of Basic Feasible Solution=%d\n",total);
     if(ismax)printf("The Maximum Value of Z is: %f\n", max);
     else printf("The Minimum Value of Z is: %f\n", min);
     printf("when: ");
     if(max2==max||max2==min)printf("Multiple Solutions exist, hence it has infinitely many solutionss one of which is: ");
     for(j=0;j<M;j++)
     {
       printf("x%d = %f ,",j+1, solution[opx][j]);
     }
     printf("\n");
     return 0;
}
