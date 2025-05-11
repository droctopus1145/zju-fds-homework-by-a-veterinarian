#include <stdio.h>

int main()
{
    FILE* fp=fopen("D:/c learning/data structures and algorithm analysis in c/zju-fds-homework-by-a-veterinarian/input.txt","w");
    fprintf(fp,"1000 999\n");
    for(int i=0;i<999;i++)
    {
        fprintf(fp,"%d %d %d\n",i+1,i+2,1);
    }
    fprintf(fp,"999\n");
    for(int i=0;i<1000;i++)
    {
        fprintf(fp,"%d ",i+1);
    }
}