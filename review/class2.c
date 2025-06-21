//max subsequence sum
    //o(n3)
int maxsubsequencesum1(const int A[],int N)
{
    int thissum,maxsum,i,j,k;
    maxsum=0;//store the maximum sum
    for(i=0;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            thissum=0;//store the current sum
            for(k=i;k<=j;j++)
            {
                thissum+=A[k];
                if(thissum>maxsum) maxsum=thissum;
            }
        }
    }

    return maxsum;
}

    //o(n2)
int maxsubsequence2(int A[],int N)
{
    int thissum,maxsum,i,j;
    maxsum=0;
    for(i=0;i<N;i++)
    {
        for(j=i;j<N;j++)
        {
            thissum+=A[j];
            if(thissum>maxsum)
                maxsum=thissum;
        }
    }
    return maxsum;
}
    //divide and conquer
int maxsubsequence3(int A[],int N)
{
    
}

    //o(n)
int maxsubsequence4(int A[],int N)
{
    int maxsum,thissum,i;
    maxsum=0;
    thissum=0;
    for(i=0;i<N;i++)
    {
        thissum+=A[i];
        if(thissum<0) thissum=0;
        if(thissum>maxsum) maxsum=thissum;
    }

    return maxsum;
}    
