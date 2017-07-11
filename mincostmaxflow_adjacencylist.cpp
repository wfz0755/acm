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
#include <cmath>
#define ll long long 
using namespace std;
const int maxn = 155;
int mat[maxn][maxn];
int s,t;
int n;
struct edge{
int u,v,nxt,cap,cost;
}E[(maxn*maxn) << 1];
int total_edge;
int vis[maxn];
int head[maxn];
int pre[maxn];
int dis[maxn];
int path[maxn];
//int max_flow;
int ans; // mincost
void add_edge(int u,int v,int cap,int cost)
{
	E[total_edge].u = u;
	E[total_edge].v = v;
	E[total_edge].cost = cost;
	E[total_edge].cap = cap;
	E[total_edge].nxt = head[u];
	head[u] = total_edge++;
	E[total_edge].u = v;
	E[total_edge].v = u;
	E[total_edge].cost = -cost;
	E[total_edge].cap = 0;
	E[total_edge].nxt = head[v];
	head[v] = total_edge++;
}

int spfa()
{
	memset(vis,0,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	queue<int> q;
	q.push(s);
	vis[s] = 1;
	dis[s] = 0;
	while(!q.empty())
	{
		int u= q.front();
		q.pop();
		for(int i = head[u]; i != -1; i = E[i].nxt)
		{
			int v = E[i].v;
			if(E[i].cap >0 && dis[v] > dis[u]+E[i].cost)
			{
				dis[v] = dis[u] + E[i].cost;
				pre[v] = u;
				path[v] = i;
				if(!vis[v])
				{
					vis[v] = 1;
					q.push(v);
				}
			}
		}
		vis[u] = 0;
	}
	if(pre[t] == -1)
		return 0;
	return 1;
}

void augment()
{
	int u,sum = 0x3f3f3f3f;
	for(u = t; u != s;u = pre[u])
	{
		sum = min(sum,E[path[u]].cap);
	}
	//max_flow += sum;
	for(u = t; u != s; u = pre[u])
	{
		E[path[u]].cap -= sum;
		E[path[u]^1].cap += sum;
		ans += E[path[u]].cost;
	}
}

void mincostmaxflow(){
	while(spfa())
	{
		augment();
	}
	printf("%d\n",ans);
}


int main()
{
	int N;
	scanf("%d",&N);
	for(int i = 1;i<=N;i++)
		for(int j = 1; j <= N;j++)
		{
			scanf("%d",&mat[i][j]);
		}
	
	int sum_rubish[maxn];
	memset(sum_rubish,0,sizeof(sum_rubish));
	memset(head,-1,sizeof(head));
	total_edge = 0;
	s = (N <<1)+1;
	t = s+1;
	n = t;
	//max_flow = 0;
	ans = 0;


	for(int i = 1; i<= N;i++)
	{
		for(int j = 1; j<= N;j++)
			sum_rubish[j] += mat[i][j];
	}
	for(int i = 1;i <= N;i++)
	{
		add_edge(s,i,1,0);
	}
	for(int i = 1;i <= N;i++)
	{
		add_edge(i+N,t,1,0);
	}
	
	for(int i = 1; i <= N;i++)
		for(int j = 1; j<= N;j++)
		{
			add_edge(i,j+N,1,sum_rubish[i]-mat[i][j]);
		}
		mincostmaxflow();
		return 0;

}