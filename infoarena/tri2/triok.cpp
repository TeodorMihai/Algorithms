/* Mugurel Ionut Andreica - Bucuresti, ROMANIA */

/*
  Preprocessing: O(N*N*logN) - time complexity
                 O(N*N) - memory
  Queries: O(1) for every query
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#define filein "6-tri.in"
#define fileout "tri.out"
#define maxn 1000

long x[maxn],y[maxn],o[maxn],oaux[maxn],under[maxn][maxn];
long v,i,j,k,m,n;
long double u[maxn],pi=2*acos(0);

void read();
void precompute();
void compute();

int main()
{
read();
precompute();
compute();
return 0;
}

void read()
{
long i;

freopen(filein,"r",stdin);
scanf("%ld",&n);

for (i=0;i<n;i++)
  scanf("%ld %ld",&x[i],&y[i]);
}

void sortx(long li,long ls)
{
if (ls-li==1)
  {
  if (x[o[ls]]<x[o[li]])
    {
    v=o[li]; o[li]=o[ls]; o[ls]=v;
    }
  }
else
if (ls-li>1)
  {
  sortx(li,(li+ls)>>1);
  sortx(((li+ls)>>1)+1,ls);

  k=li-1;
  i=li;
  m=(li+ls)>>1;
  j=m+1;

  while (i<=m && j<=ls)
    {
    k++;

    if (x[o[i]]<x[o[j]])
      {
      oaux[k]=o[i];
      i++;
      }
    else
      {
      oaux[k]=o[j];
      j++;
      }
    }

  if (i<=m)
    {
    for (j=i;j<=m;j++)
      {
      k++;
      oaux[k]=o[j];
      }
    }
  else
    {
    for (i=j;i<=ls;i++)
      {
      k++;
      oaux[k]=o[i];
      }
    }

  for (k=li;k<=ls;k++)
    o[k]=oaux[k];
  }
}

void sortu(long li,long ls)
{
if (ls-li==1)
  {
  if (u[o[ls]]>u[o[li]])
    {
    v=o[li]; o[li]=o[ls]; o[ls]=v;
    }
  }
else
if (ls-li>1)
  {
  sortu(li,(li+ls)>>1);
  sortu(((li+ls)>>1)+1,ls);

  k=li-1;
  i=li;
  m=(li+ls)>>1;
  j=m+1;

  while (i<=m && j<=ls)
    {
    k++;

    if (u[o[i]]>u[o[j]])
      {
      oaux[k]=o[i];
      i++;
      }
    else
      {
      oaux[k]=o[j];
      j++;
      }
    }

  if (i<=m)
    {
    for (j=i;j<=m;j++)
      {
      k++;
      oaux[k]=o[j];
      }
    }
  else
    {
    for (i=j;i<=ls;i++)
      {
      k++;
      oaux[k]=o[i];
      }
    }

  for (k=li;k<=ls;k++)
    o[k]=oaux[k];
  }
}

void precompute()
{
long i,j;

for (i=0;i<n;i++)
  o[i]=i;

sortx(0,n-1);

memset(under,0,sizeof(under));

for (i=2;i<n;i++)
  {
  for (j=0;j<i;j++)
    {
    u[o[j]]=atan2(y[o[j]]-y[o[i]],x[o[j]]-x[o[i]]);
    if (u[o[j]]<0)
      u[o[j]]+=2*pi;
    }

  sortu(0,i-1);

  for (j=1;j<i;j++)
    if (x[o[j]]<x[o[j-1]])
      {
      under[o[j]][o[i]]=under[o[j-1]][o[i]]+under[o[j]][o[j-1]]+1;
      }
    else
      {
      under[o[j]][o[i]]=under[o[j-1]][o[i]]-under[o[j-1]][o[j]];
      }
  }
}

void compute()
{
long p,i,j,k,m;
long double a,b,c,r;

freopen(fileout,"w",stdout);
scanf("%ld",&m);
for (p=0;p<m;p++)
  {
  scanf("%ld %ld %ld",&i,&j,&k);
  i--; j--; k--;

  if (x[i]>x[j])
    {
    v=i; i=j; j=v;
    }

  if (x[i]>x[k])
    {
    v=i; i=k; k=v;
    }

  if (x[j]>x[k])
    {
    v=j; j=k; k=v;
    }

  a=y[i]-y[k];
  b=x[k]-x[i];
  c=(long double)(x[i])*(long double)(y[k])-
    (long double)(x[k])*(long double)(y[i]);

  r=a*x[j]+b*y[j]+c;

  if (r>0)
    {
    printf("%ld\n",under[i][j]+under[j][k]-under[i][k]);
    }
  else
    {
    printf("%ld\n",under[i][k]-under[i][j]-under[j][k]-1);
    }
  }
}
