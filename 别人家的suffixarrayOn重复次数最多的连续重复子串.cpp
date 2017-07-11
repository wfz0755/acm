#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 222222 
int t1[maxn],t2[maxn],c[maxn],r[maxn],sa[maxn],rank[maxn],height[maxn];
bool cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int str[],int sa[],int rank[],int height[],int n,int m)
{
    n++;
    int i,j,p,*x=t1,*y=t2;
    for(i=0;i<m;i++)c[i]=0;
    for(i=0;i<n;i++)c[x[i]=str[i]]++;
    for(i=1;i<m;i++)c[i]+=c[i-1];
    for(i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
    for(j=1;j<=n;j<<=1)
    {
        p=0;
        for(i=n-j;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(i=0;i<m;i++)c[i]=0;
        for(i=0;i<n;i++)c[x[y[i]]]++;
        for(i=1;i<m;i++)c[i]+=c[i-1];
        for(i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(i=1;i<n;i++)
        x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p>=n)break;
        m=p;
    }
    int k=0;
    n--;
    for(i=0;i<=n;i++)rank[sa[i]]=i;
        for(i=0;i<n;i++)
        {
            if(k)k--;
            j=sa[rank[i]-1];
            while(str[i+k]==str[j+k])k++;
            height[rank[i]]=k;
        }
}
char a[maxn],b[maxn];
int main()
{
    while(~scanf("%s%s",a,b))
    {
        int la=strlen(a),lb=strlen(b);
        for(int i=0;i<la;i++)r[i]=a[i];
        r[la]='#';
        for(int i=0;i<lb;i++)r[i+la+1]=b[i];
        r[la+lb+1]=0;//important 
        int n=la+lb+1; // total length
        da(r,sa,rank,height,n,128);  // m is the largest number possible in r
        int ans=0;
        for(int i=2;i<=n;i++)
            if(sa[i-1]+height[i]<la&&sa[i]>la||sa[i-1]>la&&sa[i]+height[i]<la)
                ans=max(ans,height[i]);
        printf("%d\n",ans);
    }
    return 0;
}