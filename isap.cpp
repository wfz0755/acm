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
using namespace std;
const int max_nodes = 105;
int n,np,nc,m;
int source;         // 源点
int sink;           // 汇点
//int p[max_nodes];   // 可增广路上的上一条弧的编号
int gap[max_nodes]; // 和 t 的最短距离等于 i 的节点数量
int cur[max_nodes]; // 当前弧下标
int dis[max_nodes];   // 残量网络中节点 i 到汇点 t 的最短距离
int head[max_nodes];
int pre[max_nodes];
int total_edge ;
struct edge{
	int v,w,nxt;
}E[max_nodes*max_nodes*2];
void add_edge(int u,int v,int w)
{
	E[total_edge].v = v;
	E[total_edge].w = w;
	E[total_edge].nxt = head[u];
	head[u] = total_edge++;
	E[total_edge].v = u;
	E[total_edge].w = 0;
	E[total_edge].nxt = head[v];
	head[v] = total_edge++;
}

int maxflow()
{
	int mxflow = 0;
	memset(gap,0,sizeof(gap));
	memset(dis,0,sizeof(dis));
	memset(cur,-1,sizeof(cur));
	int u = pre[source] = source;
	int aug = -1;
	while(dis[source] < n+2)
	{
	loop:
		for(int &i = cur[u]; i != -1;i = E[i].nxt)
		{
			int v= E[i].v;
			if(E[i].w && dis[u] == dis[v] +1)
			{
				aug = min(aug,E[i].w);
				pre[v] = u;
				u = v;
				if(v == sink)
				{
					mxflow += aug;
					for(u = pre[u]; v != source;v = u,u = pre[u])
					{
						E[cur[u]].w -= aug;
						E[cur[u]^1].w += aug;
					}
					aug = 0x3f3f3f3f; // max
				}	
				goto loop; // may change
			}

		}
	int mdis = n+2;
	for(int i = head[u]; i!= -1; i = E[i].nxt)
	{
		int v= E[i].v;
		if(E[i].w && mdis > dis[v])
		{
			cur[u] = i;
			mdis = dis[v];
		}
	}
	if( --gap[dis[u]] == 0)
		break;
	gap[dis[u] = mdis+1]++;
	u = pre[u];
}
return mxflow;
}



int main()
{
	int u,v,cc;
	//char temp[100];
	while(scanf("%d%d%d%d",&n,&np,&nc,&m)!=EOF)
	{
		memset(head,-1,sizeof(head));
		total_edge = 0;
	//	memset(f,0,sizeof(f));
		source = n;
		sink = n+1;
//		memset(c,0,sizeof(c));
		for(int i = 1;i <= m;i++)
		{
			 scanf(" (%d,%d)%d", &u, &v, &cc);
		//	 printf("\nu:v:c:%d %d %d\n",u,v,cc);
	//		c[u+1][v+1] = cc;
			add_edge(u,v,cc);
	//		cap[v][u] = cc;
		//	tab[v+1][u+1] = 0;
		}
		for(int i =  1;i <= np;i++)
		{
		scanf(" (%d)%d", &u, &cc);

//			c[s][u+1] = cc;

			//tab[u+1][s] = 0;
		add_edge(source,u,cc);
	//		cap[u][s] = cc;
				
		}
		for(int i =  1;i <= nc;i++)
		{
			 scanf(" (%d)%d", &u, &cc);
			add_edge(u,sink,cc);
		//	cap[t][u] = cc;
		}
			printf("%d\n",maxflow());
	}

return 0;
}