#include<iostream>
using namespace std;
#include<algorithm>
int elem[100];

int partition(int lo,int hi)
{
  swap(elem[lo],elem[lo + rand()% (hi-lo +1)]);
  int pivot = elem[lo];
  while(lo < hi)
  {
    while((lo < hi)&& pivot <= elem[hi]) hi--;
    elem[lo] = elem[hi];
    while((lo < hi) && elem[lo] <= pivot) lo++;
    elem[hi] = elem[lo];
  }
  elem[lo] = pivot;
  return lo;
}
void quick_sort(int lo,int hi)
{
  if(hi - lo < 2)return;
  int mid = partition(lo,hi-1);
  quick_sort(lo,mid);
  quick_sort(mid+1,hi);
}

int main()
{
  int n;
  scanf("%d",&n);
  for(int i = 0;i < n ;i++)
  scanf("%d",&elem[i]);
  quick_sort(0,n);
  for(int i = 0;i< n ;i++)
    printf("%d ",elem[i]);
  printf("go\n");
  int x;
  for(int i = 1;i <= 5;i++)
  {
    scanf("%d",&x);
  printf("lower bound : %d\n",lower_bound(elem,elem+n,x)-elem);
}
  return 0;
}
