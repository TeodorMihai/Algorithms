#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define maxn 1000
#define filein "1-tri.in"

double x[maxn],y[maxn],a,b,c,r,eps=1e-6;
long i,j,k,m,n,p,ok;

int main()
{
n=30;
x[0]=y[0]=0;
srand(0x1001);

for (i=1;i<n;i++)
  {
  ok=0;
  while (!ok)
    {
    ok=1;

    x[i]=x[i-1]+1;
    y[i]=y[i-1]+i;

    for (j=0;j<i;j++)
      if (fabs(x[i]-x[j])<eps || fabs(y[i]-y[j])<eps)
        {
        ok=0; break;
        }

    if (ok)
      {
      for (j=0;j<i-1;j++)
        {
        for (k=j+1;k<i;k++)
          {
          a=y[j]-y[k];
          b=x[k]-x[j];
          c=x[j]*y[k]-x[k]*y[j];

          r=a*x[i]+b*y[i]+c;

          if (fabs(r)<eps)
            {
            ok=0; break;
            }
          }

        if (!ok) break;
        }
      }
    }
  }

freopen(filein,"w",stdout);
printf("%ld\n",n);
for (i=0;i<n;i++)
  {
  printf("%.0lf %.0lf\n",x[i],y[i]);
  }

m=100;
printf("%ld\n",m);

for (p=0;p<m;p++)
  {
  i=rand()%n;

  do
    {
    j=rand()%n;
    }
  while (j==i);

  do
    {
    k=rand()%n;
    }
  while (k==i || k==j);

  printf("%ld %ld %ld\n",i+1,j+1,k+1);
  }
  
return 0;
}
