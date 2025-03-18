#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//include time.h to record the running time

clock_t start,stop;
double duration,total_time,ticks;

int* ordered_list(int num);
//to produce a ordered list
int seq_inter(int* list,int num,int length);
//iterative version of sequential search
int seq_rec(int* list,int num,int index,int length);
//recursive version of sequential search
int bin_inter(int* list,int num,int length);
//iterative version of bbinary search
int bin_rec(int* list,int num,int first,int end);
//recursive version of binary search

int main()
{
    int num,to_find,k,i;
    int* list;
    scanf("%d %d",&num,&k);
    //receive the number to be searched and the repeat times(to improve the accuracy)
    list=ordered_list(num);
    //to produce a ordered list
    to_find=list[num-1];
    //the target is the last number in the list,to convince the worst case
    printf("                        ticks         total_time           duration\n");
    //show the data need to be tested
    start=clock();
    for(i=0;i<k;i++)
        seq_inter(list,to_find,num);
    //repeat the function for k times to get a accurate answer
    stop=clock();
    ticks=(double)(stop-start)/k;
    //record the ticks
    total_time=((double)ticks)/CLK_TCK;
    //record the total time
    duration=total_time/k;
    //record the duration
    printf("seq_inter: ");
    printf("%.16lf %.16lf %.16lf\n",ticks,total_time,duration);
    //print the data,sixteen digits of precision
    start=clock();
    for(i=0;i<k;i++)
        seq_rec(list,to_find,0,num);
    //repeat the function for k times to get a accurate answer
    stop=clock();
    ticks=(double)(stop-start)/k;
    //record the ticks
    total_time=((double)ticks)/CLK_TCK;
    //record the total time
    duration=total_time/k;
    //record the duration
    printf("seq_rec:   ");
    printf("%.16lf %.16lf %.16lf\n",ticks,total_time,duration);
    //print the data,sixteen digits of precision
    start=clock();
    for(i=0;i<k;i++)
        bin_inter(list,to_find,num);
    //repeat the function for k times to get a accurate answer
    stop=clock();
    ticks=(double)(stop-start)/k;
    //record the ticks
    total_time=((double)ticks)/CLK_TCK;
    //record the total time
    duration=total_time/k;
    //record the duration
    printf("bin_inter: ");
    printf("%.16lf %.16lf %.16lf\n",ticks,total_time,duration);
    //print the data,sixteen digits of precision
    start=clock();
    for(i=0;i<k;i++)
        bin_rec(list,to_find,0,num-1);
    //repeat the function for k times to get a accurate answer
    stop=clock();
    ticks=(double)(stop-start)/k;
    //record the ticks
    total_time=((double)ticks)/CLK_TCK;
    //record the total time
    duration=total_time/k;
    //record the duration
    printf("bin_rec:   ");
    printf("%.16lf %.16lf %.16lf\n",ticks,total_time,duration);
    //print the data,sixteen digits of precision

    return 0;
}

int* ordered_list(int num)
{
    int* list;
    list=(int*)malloc(sizeof(int)*num);
    //prevent pointers from being destroyed after the program is over
    int i;
    for(i=0;i<num;i++)
    {
        list[i]=i+1;
        //produce a list which is increasingly
    }
    
    return list;
    //return the pointer point to the list
}

//iterative version of sequential search
//input the pointer point to the list and the number to search,output the index of the number
//if not find, return -1
int seq_inter(int* list,int num,int length)
{
    int i;
    for(i=0;i<length;i++)
    {
        if(num==list[i])
            return i;
        //if find,return the index of the number  
    }

    return -1;
}
//O(n)

//recursive version of sequential search
//at the first index should be 0
int seq_rec(int* list,int num,int index,int length)
{
    if(num==list[index])
        return  index;
    //if find,return the index of the number
    else if(index<length)
    {
        index+=1;
        seq_rec(list,num,index,length);
        //if not find,index plus 1 and judge if the next number fit the target
    }
    else
        return -1;

}
//O(n)

//iterative version of binary search
int bin_inter(int* list,int num,int length)
{
    int first=0;
    int end=length-1;
    int mid=(first+end)/2;

    while(list[mid]!=num)
    {
        //base case-two items in a branch
        if((end-first)==1)
        {
            if(list[first]==num)
                return first;
            else if(list[end]==num)
                return end;
            else
                return -1;
        }
        //base case-three items in a branch
        else if((end-first)==2)
        {
            if(list[mid]==num)
                return mid;
            else if(list[mid]>num)
                return first;
            else if(list[mid]<num)
                return end;
            else 
                return -1;
        }
        //other cases--reduce the number of items in a branch
        else
        {
            if(list[mid]==num)
                return mid;
            else if(list[mid]>num)
            {
                end=mid-1;
                mid=(end+first)/2;
            }
            else
            {
                first=mid+1;
                mid=(end+first)/2;
            }
        }
    }

    return mid;

}
//O(logn)

//recursive version of binary search
//at the first first must be 0,and end must be num-1
int bin_rec(int* list,int num,int first,int end)
{
    int mid;
    mid=(end+first)/2;
    //base case-two items in a branch
    if((end-first)==1)
    {
        if(list[first]==num)
            return first;
        else if(list[end]==num)
            return end;
        else
            return -1;
    }
    //base case-three items in a branch
    else if((end-first)==2)
    {
        if(list[mid]==num)
            return mid;
        else if(list[mid]>num)
            return first;
        else if(list[mid]<num)
            return end;
        else 
            return -1;
    }
    //other cases--reduce the number of items in a branch
    else
    {
        if(list[mid]==num)
            return mid;
        else if(list[mid]>num)
        {
            end=mid-1;
            mid=(end+first)/2;
        }
        else
        {
            first=mid+1;
            mid=(end+first)/2;
        }
        bin_rec(list,num,first,end);
    }
}
//O(logn)