#include<iostream>
#define ll long long

using namespace std;

struct cube
{
    int met[2][2];
};
cube ccc;
ccc.met ={{1,1},{1,0}};
cube unit_c({{1,0},{0,1}});

cube multi(cube a,int power)
{
    if(power == 0)
      return unit_c;
    if(power == 1)
    {
      return init;
    }
    cube c1 = unit_c;
    if(power & 1)
    {
        c1 = init;
    }
    cube tmp1 = multi(init, power >>1);
    cube res;
    for(int i = 0;i <= 1;i++)
      for(int j = 0; j<= 1;j++)
      {
          int tmp = 0;
          for(int col = 0; col <= 1;col++)
            tmp += tmp1.met[i][col]*tmp1.met[col][j];
          res.met[i][j] = tmp;
      }
    cube c2 = res;
      for(int i = 0;i <= 1;i++)
        for(int j = 0; j<= 1;j++)
        {
            int tmp = 0;
            for(int col = 0; col <= 1;col++)
              tmp += c1.met[i][col]*c2.met[col][j];
            res.met[i][j] = tmp;
        }
      return res;

}
int fib[2] = {1,1}; // fib 0,fib 1

int main()
{
  int n;
  scanf("%d",&n);
  if(n < 2)
    {
      printf("%d\n",fib[n]);
    }
  cube res = multi(init,n-2);
  int fibn = fib[0]* res.met[0][0]+ fib[1]*res.met[0][1];
  printf("%d\n",fibn);
  return 0;
}
