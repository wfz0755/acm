
#include <iostream>
#include <cmath>
const int maxn = 1005;
const int logmaxn = 10;
int N;
int A[maxn];
int M[maxn][logmaxn];
void process2()
{
	for(int i = 0;i < N;i++)
	{
		M[i][0] = i;
	}
	for(int j = 1; (1<< j) - 1 <= N;j++)
		for(int i = 0; i+ (1<< j) -1 < N;i++)
		{
			if(A[M[i][j-1]] < A[M[i+(1<<(j-1))][j-1]])
				M[i][j] = M[i][j-1];
			else M[i][j] = M[i+(1 << (j-1))][j-1];
		}
}

int query(int i,int j)
{
	int k = (int)log2(1.0*(j-i+1));
	if(A[M[i][k]] <= A[M[j-(1<<k)+1][k]])
	{
		return M[i][k];
	}
	else return M[j-(1<<k)+1][k];
}

int main()
{
	N = 10;
	for(int i = 0; i< N;i++)
	{
		A[i] = i;
	}
	process2();
	int l,r;
	while(1)
	{
	scanf("%d%d",&l,&r);
	printf("%d\n",query(l,r));
	}
return 0;
}