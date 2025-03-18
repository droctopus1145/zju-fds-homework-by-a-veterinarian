#include <stdio.h>
void display(int);
int main()
{
    int input;
    scanf("%d",&input);
    display(input);
}
void display(int x)
{
    int n=x;
    while(n!=0)
    {
        putchar(48+n%10);
        n=n/10;
    }
    //printf("%d",x);
}