#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <map>
#include <set>

using namespace std;

int g[1105][1105];
int pre[1105];
int used[1105];
bool hungary(int k)
{
	for(int i = 1;i <= g[k][g[k][0]];i++)
	{
		int j = g[k][i];
		if(!used[j])
		{
			used[j] = 1;
			if(pre[j] == 0 || hungary(pre[j]))
			{
				pre[j] = k;
				return true;
			}
		}
	}
	return false;
}


int main()
{
	int M,N,K;
	scanf("%d%d%d",&M,&N,&K);
	int m,n;
	memset(pre,0,sizeof(pre));
	for(int i = 0;i <= M+1;i++)
		g[i][0] = 0;
	for(int i = 1; i <= K;i++)
	{
		scanf("%d%d",&m,&n);
		g[m][++g[m][0]] = n;
	}
	int match = 0;
	for(int i = 1; i<= M;i++)
	{
		memset(used,0,sizeof(used));
		if(hungary(i))
		{	
			match++;
		}
	}
	printf("%d\n",M+N-match);
return 0;


}