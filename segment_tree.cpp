#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
#define lson l,m,rt << 1
#define rson m+1,r,rt << 1|1
const int maxn = 205;
int cnt[maxn << 2];
double sum[maxn << 2];
int n;

double X[maxn << 1]; // discretization
struct seg{
	double h,l,r;
	int s;
	seg(){}
	seg(double a,double b,double c,int d):l(a),r(b),h(c),s(d){}
	bool operator< (const seg& cmp) const{
		return h < cmp.h;
	}
}ss[maxn];

void PushUp(int rt,int l,int r)
{
	if(cnt[rt]) sum[rt] = X[r+1] - X[l];
	else if(l == r) sum[rt] = 0;
	else sum[rt] = sum[rt << 1] + sum[rt << 1|1];
}
void update(int L,int R,int c,int l,int r,int rt)
{
	if(L <= l && r <= R)
	{
		cnt[rt] += c;
		PushUp(rt,l,r);
		return;
	}
	int m  = (l + r) >> 1;
	if(L <= m) update(L,R,c,lson);
	if(m < R) update(L,R,c,rson);
	PushUp(rt,l,r);
}
int Bin(double key,int nn,double x[])
{
	int l = 0,r = nn-1;
	while(l <= r)
	{
		int m = (l+r) >> 1;
		if(x[m] == key) return m;
		if(x[m] < key) l = m+1;
		else r = m-1;
	}
return -1;
}

int main()
{
//freopen("in","r",stdin);
//freopen("out.txt","w",stdout);
int t = 0;
	while(scanf("%d",&n)&& n)
	{
		t++;
		double x,y,r;
		int m = 0;
		for(int i = 1; i<= n;i++)
		{
			scanf("%lf%lf%lf",&x,&y,&r);
			X[m] = x-r;
			ss[m++] = seg(x-r,x+r,y-r,1);
			X[m] = x+r;
			ss[m++] = seg(x-r,x+r,y+r,-1);
		}
		sort(X,X+m);
		sort(ss,ss+m);
		int k = 1;
		for(int i = 1; i< m;i++)
		{
			if(X[i] != X[i-1]) X[k++] = X[i];
		}
		memset(cnt,0,sizeof(cnt));
		memset(sum,0,sizeof(sum));
		double ans = 0;
		for(int i = 0; i< m-1;i++)
		{
			int l = Bin(ss[i].l,k,X);
			int r = Bin(ss[i].r,k,X) - 1;
			if(l <= r)update(l,r,ss[i].s,0,k-1,1);
			ans += sum[1] * (ss[i+1].h - ss[i].h);
		}
		printf("%d %.2lf\n",t,ans);

	}

	return 0;
}