#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1005;
char buffer[maxn];
struct entry{
	int nr[2],p;
}L[maxn];

int sa[maxn],ranks[maxn],height[maxn];

//rank[i] = j -> suffix from i ranks j
// sa[i] = j , the ith suffix start from j
//height[i] -> longest common prefix between suffix(sa[i-1]),suffix(sa[i])
//LCP(i, j) = min{height[k] | min{i, j} < k <= max{i, j}}
int n;
int cmp(const entry &a,const entry &b)
{
	return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1]?1:0) : (a.nr[0] < b.nr[0] ? 1: 0);
}
void construct()
{
	int cnt;
	for(int i = 0 ;i <n;i++)
		ranks[i] = (int)buffer[i];
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

int calc_substr()
{
	int ret = n-sa[0];
	for(int i = 1; i< n;i++)
	{
		ret += (n-sa[i]-height[i]);
	}
return ret;
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{		
		scanf("%s",buffer);
		n = strlen(buffer);
		construct();	
		calheight();
		printf("%d\n",calc_substr());
	}
return 0;


}