#include<iostream>
#include<cstring>
using namespace std;
/* 
 * DLX解经典数独问题 
 * 考虑到每行都要有1~9 
 * 用第1~81列表示第i行是否有数字j(第(i - 1)*9 + j列的状态） 
 * 由于每列都要有1~9 
 * 用第82~162列表示第i列是否有数字j (第(i - 1)*9 + j + 81列的状态) 
 * 考虑到每个九宫格都要有1~9 
 * 用第163~243列表示第i个九宫格是否有数字j (第(i - 1)*9 + j + 162列的状态) 
 * 但是仅仅依靠这些是不够的 
 * 还有一个限制条件每个格子只能有1个数字 
 * 所以用第244~324列表示格子中是否填了数 
 * 那么对于给定的数字, 就在对应的列上写4个1 
 * 如果是.那么就添加9行, 分别对应哪个位子填1~9的情况 
 * 那么最坏情况下有9*9*9行可选 
 */  
const int maxnode = 730*325;
const int maxn = 730;
const int maxm = 325;
struct state{
		int x,y,val;
		state(int _x,int _y,int _val):x(_x),y(_y),val(_val){} 
		state(){}
	};
	state s[maxn];
struct dlx
{
	int n,m,size;
	int U[maxnode],D[maxnode],L[maxnode],R[maxnode],Row[maxnode],Col[maxnode];
	int H[maxn],S[maxm];
	int ansd,ans[maxn];
	
	void init(int _n,int _m)
	{
		n = _n;
		m = _m;
		for(int i = 0; i <= m;i++) // initialize the head
		{
			S[i] = 0;
			U[i] = D[i] = i;
			L[i] = i-1;
			R[i] = i+1;
		}
		R[m] = 0;
		L[0] = m; 
		size = m;
		for(int i = 1; i <= n ;i++)
			H[i] = -1;
	}
	void link(int r,int c)
	{
		++S[Col[++size] = c]; // we add nodes one by one
		Row[size] = r;
		D[size] = D[c]; // new -> list head
		U[D[c]] = size; // list head -> new
		U[size] = c;
		D[c] = size;
		if(H[r] < 0) H[r] = L[size] = R[size] = size; // if this is the first element in the row
		else
		{
			R[size] = R[H[r]]; // ok
			L[R[H[r]]] = size; // ok
			L[size] = H[r]; //???
			R[H[r]] = size;//???
		}
	}
	void remove(int c)
	{
		L[R[c]] = L[c];
		R[L[c]] = R[c];
		for(int i = D[c]; i != c; i = D[i])
		{
			for(int j = R[i]; j != i; j = R[j])
			{
				U[D[j]] = U[j];
				D[U[j]] = D[j];
				--S[Col[j]];
			}
		}
	}
	void resume(int c)
	{
		for(int i = U[c]; i != c;i = U[i])
			for(int j = L[i]; j != i; j = L[j])
			{
				U[D[j]] = D[U[j]] = j;
				++S[Col[j]];
			}
		L[R[c]] = R[L[c]] = c;
	}
	bool dance(int d)
	{
		if (R[0] == 0)
		{
			ansd = d;
			return true;
		}
		int c = R[0];
		for(int i = R[0] ; i != 0; i = R[i]) // optimization
			if(S[i] < S[c])
				c = i;
		remove(c);
		for(int i = D[c]; i != c; i = D[i])
		{
			ans[d] = Row[i];
			for(int j = R[i] ; j != i; j = R[j])
				remove(Col[j]);
			if(dance(d+1)) return true;
			for(int j = L[i]; j != i; j = L[j]) resume(Col[j]);
		}
		resume(c);
		return false;
	}
};

dlx g;
int main()
{
	char buffer[100];
	while(gets(buffer))
	{
		if(strcmp(buffer,"end") == 0)
			break;
		int tn = 0;
		int tm = 324;
		for(int i = 0; i< strlen(buffer); i++)
			if(buffer[i] == '.')tn+=9;
			else tn++;
		g.init(tn,tm);
		tn = 0;
		for(int i = 0; i < 9; i++)
			for(int j = 0; j< 9;j++)
			{
				char c = buffer[i*9+j];
				if(c == '.')
				{
					for(int k = 1; k <= 9; k++)
					{
						s[++tn] = state(i,j,k);
						g.link(tn,i*9+k);
						g.link(tn,j*9+k+81);
						g.link(tn,(i/3*3+j/3)*9+k+162);
						g.link(tn,i*9+j+1+243);
					}
				}
				else
				{
					s[++tn] = state(i,j,c-'0');
					g.link(tn,i*9+c-'0');
					g.link(tn,j*9+c-'0'+81);
					g.link(tn,(i/3*3+j/3)*9+c-'0'+162);
					g.link(tn,i*9+j+1+243);
				}
			}
	
		if(!g.dance(0)) printf("No answer\n");
		else {
			for(int i = g.ansd-1; i>= 0;i--)
			{
				int sel = g.ans[i];
				buffer[s[sel].x*9+s[sel].y] = s[sel].val+'0';
			}
			puts(buffer);
		}

	}

return 0;
}







