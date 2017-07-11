#include <iostream>
#include <cstring>
using namespace std;
const int maxn = 100005;
struct edge{
	int v,nxt;
}E[maxn << 1];
struct node{
	int l,r;
}app[maxn];
int m,n;
int head[maxn];
int cnt_edge = 0;
int a[maxn],c[maxn];
int cnt;
int status[maxn];
inline int lowbit(int x)
{
	return x&(-x);
}

void dfs(int u)
{
	app[u].l = cnt;
	status[u] = 1;
	for(int i = head[u]; i != -1; i = E[i].nxt)
	{
		if(!status[E[i].v])
			dfs(E[i].v);
	}
	app[u].r = cnt++;
}
void change(int x)
{
	//printf("This X is :%d\n",x);
	if(a[x])
	{
		for(int i = x; i < cnt;i += lowbit(i))
			{
				c[i]++;
		}
	}
	else{
		for(int i = x; i < cnt;i += lowbit(i))
				{
					c[i]--;
		}
	}
//	printf("\nout\n");
}
int sum(int x)
{
	int i,res=0;
	for(i = x; i> 0;i-=lowbit(i)) res += c[i];

		return res;
}



int main()
{	
	scanf("%d",&n);
	int u,v;
	memset(c,0,sizeof(c));
	memset(head,-1,sizeof(head));
	memset(app,0,sizeof(app));
	memset(status,0,sizeof(status)); // 0 unvisited, 1 visited
	for(int i = 1; i<= n-1;i++)
	{
		scanf("%d%d",&u,&v);
		E[cnt_edge].v = v;
		E[cnt_edge].nxt = head[u];
		head[u] = cnt_edge++;
		E[cnt_edge].v = u;
		E[cnt_edge].nxt = head[v];
		head[v] = cnt_edge++;
	}
	cnt= 1;
	//printf("rua");
	dfs(1);
	memset(a,0,sizeof(a));
	for(int i = 1; i <= n;i++)
	{
		a[i] = 1;
		change(i);
	}
	char s[3];
	int pos;
	
	scanf("%d",&m);

	while(m--)
	{
		scanf("%s%d",s,&pos);//printf("this is s %s\n and m is ",s);
		if(s[0] == 'Q')
		{
			printf("%d\n",sum(app[pos].r)-sum(app[pos].l-1));
		}
		else
		{
			a[app[pos].r] = a[app[pos].r]^1;
			change(app[pos].r);
		}
	}
return 0;

}