#include <iostream>
#include <vector>
#include <iomanip>
#define Ep 0.00001
#define INF 10000
#define vvd vector<vector<double> >
#include <cmath>
using namespace std;


void print(vector<double> A)
{
  int n=A.size();
  cout<<"(";
  for(int i=0;i<n;i++)
    cout<<A[i]<<",";
  cout<<")\n";
}
vvd multiply(vvd A, vvd B)
{
  int n = A.size();
  vvd C(n,A[0]);
  for(int i=0;i<n;i++)
    {
      for(int j=0;j<B[0].size();j++)
      {
	C[i][j]=0;
	for(int k=0;k<B.size();k++)
	  {
	    C[i][j]+=A[i][k]*B[k][j];
	   
	  }

      }
      print(C[i]);
    }
  return C;
}

vector<double> multiply(vector<double> C,vvd A)
{
  cout<<"vd X vvd\n";
  int n=C.size();
  vector<double> R(n);
  for(int i=0;i<n;i++)
    {
      R[i]=0;
      for(int j=0;j<n;j++)
	R[i]+=A[j][i]*C[j];
      if(abs(R[i])<Ep)
	R[i]=0;
 	 
    }
  return R;
}


vector<double> multiply(vvd A,vector<double> C)
{
  int n=C.size();
  vector<double> R(n);
  for(int i=0;i<n;i++)
    {
      R[i]=0;
      for(int j=0;j<n;j++)
	R[i]+=A[i][j]*C[j];
      if(abs(R[i])<Ep)
	R[i]=0;
 	 
    }
  return R;
}
vector<double> getN(vector<double> e,int toC)
{
  double r = e[toC];
  e[toC]=1/r;
  for(int i=0;i<e.size();i++)
    if(i!=toC)
      e[i]=-e[i]/r;
  return e;
}
void print(vvd A)
{
 
  for(int i=0;i<A.size();i++)
    {
      cout<<"\t";
      for(int j=0;j<A[0].size();j++)
	cout<<setw(16)<<A[i][j];
      cout<<endl;
    }
  cout<<"\n\n";
}

vvd getI(int n)
{
  vector<double> A(n);
  vvd B(n,A);
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      {
	B[i][j]=0;
	if(i==j)
	  B[i][j]=1;
      }
  return B;
}


double multiply(vector<double> A,vector<double> B)
{
  double S=0;
  int n=A.size();
  for(int i=0;i<n;i++)
    S+=A[i]*B[i];
  return S;
}

double Tmultiplier(vector<double> A)
{
  vector<double> temp(A.size());
  vvd M(A.size(),temp);

  for(int i=0;i<A.size();i++)
    {
      for(int j=0;j<B[0].size();j++)
	{
	  M[i][j]=A[i]*A[j];
	}
    }
  return M;
} 
      
void print(vector<int> A)
{
  int n=A.size();
  cout<<"(";
  for(int i=0;i<n;i++)
    cout<<A[i]<<",";
  cout<<")\n";
}
vvd exchange(vvd A,vector<double> c,int x)
{
  int n=c.size();
  for(int i=0;i<n;i++)
    A[i][x] = c[i];
  return A;
}


vvd getInverse(vvd M,vvd B,vvd prevB,vector<int> diff)
{
 
  int n = diff.size(),toC,nC=0;
  for(int i=0;i<n;i++)
    if(diff[i]==1)
      {
	toC = i;
	nC++;
      }

  if(nC > 1)
    {
      vvd nM=M;
      for(int i=0;i<n;i++)
	if(i==toC)
	  nM[i][toC]=1;
	else
	  nM[i][toC]=0;
      diff[toC]=0;
      vvd I=getInverse(nM,B,prevB,diff);
	 
      prevB=multiply(I,prevB);
      cout<<endl;
 	 
    }

  vvd A = B;
  vector<double> e,N,C;
  for(int i=0;i<n;i++)
    C.push_back(M[i][toC]);
  e = multiply(prevB,C);
  //cout<<"e"<<toC+1<<endl;
  // print(e);
  N = getN(e,toC);
  //cout<<"N"<<toC+1<<endl;
  // print(N);
 
  for(int i=0;i<n;i++)
    A[i][toC]=N[i];
  //cout<<"E"<<toC+1<<endl;
  //print(A);
  A=multiply(A,prevB);
  //cout<<"Inverse "<<toC+1<<endl;
  //print(A);
  return A;
}

vvd Inverse(vvd M,int n)
{
  vector<double> temp(n);
  vector<int> diff(n);
  vvd B(n,temp);
  
  for(int i=0;i<n;i++)
    {
 	 
      for(int j=0;j<n;j++)
	{
      
	  B[i][j]=0;
	  if(i==j)
	    B[i][j]=1;
	  if(j==i && M[i][j]!=1)
	    diff[j]=1;
	  if(j!=i && M[i][j]!=0)
	    diff[j]=1;
	}
    }
 
  vvd I =getInverse(M,B,B,diff);
  return I;
}

void IPM(vector<double> X,vvd A,vector<double> C)
{
  int n = X.size();
  vector<double> nX(n);
  vvd D(n,nX);
  cout<<"X = \n"; print(X);
  for(int i=0;i<n;i++)
    D[i][i]=X[i];
   cout<<"D =\n";
   print(D);
  vvd Din = Inverse(D,n);
 cout<<"Din =\n";
 print(Din);
  vvd nA = multiply(A,D);
cout<<"A = \n"; print(A);
 cout<<"D =\n";
   print(D);
cout<<"nA =\n";
 print(nA);
  vector<double> nC = multiply(D,C);
cout<<"nC = \n"; print(nC);
 vector<double> t(A.size());
 vvd nAT(A[0].size(),t);
  for(int i=0;i<nA.size();i++)
    for(int j=0;j<nA[0].size();j++)
      nAT[j][i]=nA[i][j];
cout<<"nAT= \n"; print(nAT);
  vvd I = getI(n);
  vvd temp = multiply(nA,nAT);
cout<<"temp1= \n"; print(temp);
  temp = Inverse(temp,n);
cout<<"temp2= \n"; print(temp);
  temp = multiply(nAT,temp);
cout<<"temp3= \n"; print(temp);
  temp = multiply(temp,nA);
cout<<"temp= \n"; print(temp);

  vvd P = I;
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      P[i][j] = I[i][j] - temp[i][j];
cout<<"P = \n"; print(P);
  vector<double> Cp = multiply(P,nC);
 cout<<"Cp = \n"; print(Cp);
}

int main()
{
  int n,m,v;
  
  cout<<"Enter number of variables\n";
  cin>>n;
  cout<<"Enter number of equations\n";
  cin>>m;
  cout<<"Enter number of equations with > constraint\n";
  cin>>v;
  cout<<"Enter the equations with sign\n";
  vector<double> Z(n+1+m+v),cB(n),b(m),cV(n+m+v);
  vector<int> diff(n),Bv,Nbv;
  vector<char> sign(m);
  vvd A(m,cV);

  v = n;
  for(int i=0;i<m;i++)
    {
      for(int j=0;j<n+2;j++)
	{
	  if(j<n)
	    cin>>A[i][j];
	  if(j==n)
	    cin>>b[i];
	}
      cin>>sign[i];
      if(sign[i]=='<' || sign[i]=='=')
	A[i][v++]=1;
      else if(sign[i]=='>')
	{
	  A[i][v++]=-1;
	  A[i][v++]=1;
	}
    }

 
  cout<<"Enter Z\n";
  for(int i=0;i<n+1;i++)
    {
      cin>>Z[i];
      if(i<n)
	{
	  cV[i]=Z[i];
	  
	}
    }
  cout<<"b = "; print(b);
  print(A);
  print(Z);
  cout<<"Enter guess\n";
  vector<double> X(A[0].size());
  for(int i=0;i<A[0].size();i++)
    cin>>X[i];
  IPM(X,A,cV);
}

//2 1 0 1 1 8 < 1 2 0 2 2 4
