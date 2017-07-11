#include <iostream>
#include <vector>
using namespace std;
#define maxn 31
#define maxalphabet 26

struct points{
	int r,c;
}ll[maxalphabet],rh[maxalphabet];

struct Letter{
	vector<int> covered;
	int indegree;
	int exist;
}letter[maxalphabet];
int col,row;

char maps[maxn][maxn];
char ans[maxn];
int cnt_alpha;


void dfs(int current)
{
	if(current == cnt_alpha)
	{
		ans[current] = '\0';
		printf("%s\n",ans);
		return;
	}
	for(int i = 0; i< maxalphabet;i++)
	{
		if(!letter[i].exist)
			continue;
		if(letter[i].indegree == 0)
		{
			ans[current] = i+'A';
			letter[i].indegree--;//means it is no longer here
			for(int j = 0; j < letter[i].covered.size();j++)
			{
				letter[letter[i].covered[j]].indegree--;
			}
			dfs(current+1);
			for(int j = 0; j < letter[i].covered.size();j++)
			{
				letter[letter[i].covered[j]].indegree++;
			}
			letter[i].indegree++;//means it is no longer here
			
		}


	}


}




int main()
{
	while(scanf("%d%d",&row,&col)!=EOF)
	{
		memset(letter,0,sizeof(letter));
		memset(ll,0x3f,sizeof(ll));
		memset(rh,-1,sizeof(rh));
		cnt_alpha = 0;
		for(int i = 1; i <= row;i++)
		{
			scanf("%s",maps[i]+1);
		}
		for(int i = 1;i <= row;i++)
			for(int j = 1;j <= col;j++)
			{
				if(maps[i][j] == '.')
					continue;
				int tt = maps[i][j] - 'A';
				if(!letter[tt].exist)
				{
					letter[tt].exist = ++cnt_alpha;
				}
				ll[tt].r = min(ll[tt].r,i);
				ll[tt].c = min(ll[tt].c,j);
				rh[tt].r = max(rh[tt].r,i);
				rh[tt].c = max(rh[tt].c,j);
			}
		for(int k = 0; k < maxalphabet ;k++)
		{
			if(letter[k].exist == 0)
				continue;
			for(int i = ll[k].r;i <= rh[k].r;i++)
				for(int j = ll[k].c;j <= rh[k].c;j++)
				{
					if(i != ll[k].r && i != rh[k].r && j != ll[k].c)
						j = rh[k].c;
					int tmp = maps[i][j] -'A';
					if(tmp != k)
					{
						letter[k].covered.push_back(tmp);// deliberately inversse for answer
						letter[tmp].indegree++;
					}


				}
		}
		dfs(0);
	}

	return 0;
}