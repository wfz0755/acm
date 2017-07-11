#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 20005;
int buffer[maxn];
struct entry{
	int nr[2],p;
}L[maxn];

int sa[maxn],ranks[maxn],height[maxn];

//rank[i] = j -> suffix from i ranks j
// sa[i] = j , the ith suffix start from j
//height[i] -> longest common prefix between suffix(sa[i-1]),suffix(sa[i])
//LCP(i, j) = min{height[k] | min{i, j} < k <= max{i, j}}
int n;

int k;
int cmp(const entry &a,const entry &b)
{
	return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1]?1:0) : (a.nr[0] < b.nr[0] ? 1: 0);
}
void construct()
{
	int cnt;
	for(int i = 0 ;i <n;i++)
		ranks[i] = buffer[i];
	for(cnt = 1;cnt >> 1 < n;cnt <<=1)
	{
		for(int i = 0; i< n;i++)
		{
			L[i].nr[0] = ranks[i];
			L[i].nr[1] = i+cnt < n ? ranks[i+cnt]:-1;
			L[i].p= i;
		}
		sort(L,L+n,cmp);
		for(int i  =0; i < n;i++)
		{
			ranks[L[i].p] = (i > 0 && L[i].nr[0] == L[i-1].nr[0] && L[i].nr[1] == L[i-1].nr[1])? ranks[L[i-1].p] :i;
		}
	}
	for(int i = 0; i< n;i++)
	{
		sa[ranks[i]]= i;
	}
}
void calheight()
{
	 for (int i = 0, h0 = 0; i < n; h0 = max(0, height[ranks[i]]-1), ++i) {
		if (!ranks[i])
			continue;
		int j = sa[ranks[i]-1], & k = height[ranks[i]] = h0;
		while (buffer[i+k] == buffer[j+k])
			++k;
	}
}
int test_mi(int len)
{
	int res = -1;
	int g_s,g_e;
	for(int i = 1;i < n && res == -1;i++)
	{
		if(height[i] >= len)
		{
			g_s = i-1;
			while(i < n&& height[i] >= len)
			{
				i++;
			}
			i--;
			g_e = i;
			if(g_e - g_s+1 >= k)
				res= 1;
		}
	}
	return res;
}

int main()
{
		scanf("%d%d",&n,&k);
		for(int i = 0;i < n;i++)
			scanf("%d",&buffer[i]);
		construct();
		calheight();
		int lo = 0;
		int hi = n;
		int mi ;
		while(1)
		{
			mi= (lo+hi) >>1;
			int res = test_mi(mi);
			if(res<0) // doesn't exist
			{
				hi = mi;
			}
			else // exists
			{
				lo = mi;
			}
			if(hi -lo <= 1)
			{
				break;
			}
		}
		printf("%d\n",lo);

return 0;


}