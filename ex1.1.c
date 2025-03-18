#include <time.h>
#include <stdio.h>
int main()
{
    int N,i,k;
    long double btime,etime;
    scanf("%d",&N);
    long double rtime[N];
    for(i=0;i<N;i++)
    {
        btime=clock();
        k=i/2;
        etime=clock();
        rtime[i]=etime-btime;
    }
    for(i=0;i<N;i++)
    {
        printf("%d ",i);
        printf("%.19Lf\n",rtime[i]);
    }
}