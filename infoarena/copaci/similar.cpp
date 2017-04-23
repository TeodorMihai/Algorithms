#include <fstream>
#include <stdlib.h>
using namespace std;

struct punct
{
    long long x, y;
};
punct v[100001];

long long n,i,a,b;

long long cmmdc( long long a, long long b )
{
	long long r;
	while( b )
	{
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}


int main()
{
    ifstream f("copaci.in");
    ofstream g("copaci.out");

    f>>n;
    for(i=1;i<=n;i++)
    f>>v[i].x>>v[i].y;

    b=0;
    for(i=1;i<n;i++)
    b+=cmmdc(llabs(v[i].x-v[i+1].x),llabs(v[i].y-v[i+1].y));

     long long x1,x2,y1,y2;
     v[n + 1] = v[1];
    for(i=1;i<=n;i++)
    {
        x1=v[i].x-v[0].x;
        y1=v[i].y-v[0].y;
        x2=v[i+1].x-v[0].x;
        y2=v[i+1].y-v[0].y;
        a+=x1*y2-x2*y1;
    }
    a=llabs(a*0.5);

    long long p=a-(b/2)+1;
    g<<p;
    f.close();
    g.close();
    return 0;
}