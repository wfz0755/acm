#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn = 1000005;
const int maxm = 2005;

char ch[maxn];
int sum[maxn];

int num;
int n,m;

struct ListBlock
{
	int size;
	char data[maxm];
	void push_back(char c)
	{
		size++;
		data[size] = c;
	}
	void insert(int pos,char c)
	{
		for(int i = size+1;i > pos;i--)
		{
			data[i] = data[i-1];
		}
		data[pos] = c;
		size++;
	}
	char getData(int pos)
	{
		return data[pos];
	}
};
ListBlock blocks[maxm];

void maintain()
{
	for(int i = 1; i<= num;i++)
	{
		sum[i] = sum[i-1] + blocks[i].size;
	}
}
void init()
{
	num = sqrt((n+m)*1.0)+1;
	for(int i = 0;i < n;i++)
	{
			blocks[i/num+1].push_back(ch[i]);
	}
	maintain();
}
char query(int pos,int number)
{
	return blocks[number].getData(pos);
}
void insert(int pos,int number,char c)
{
	blocks[number].insert(pos,c);
}
char myQuery(int pos)
{
	int p = lower_bound(sum+1,sum+1+num,pos)-sum;
	return query(pos-sum[p-1],p);
}
void myInsert(char c,int pos)
{
	int p = lower_bound(sum+1,sum+1+num,pos)-sum;
	insert(pos-sum[p-1],p,c);
	maintain();
}
int main()
{
	scanf("%s",ch);
	n = strlen(ch);
	scanf("%d",&m);
	init();
	char s[3];
	char c[3];
	int pos;
	for(int i = 1; i<= m;i++)
	{
		scanf("%s",s);
		if(s[0] == 'Q')
		{
			scanf("%d",&pos);
			printf("%c\n",myQuery(pos));
		}
		else{
			scanf("%s%d",c,&pos);
			myInsert(c[0],pos);
		}


	}

	return 0;

}