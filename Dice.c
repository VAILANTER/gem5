#include<stdio.h>
#include<time.h>
#include<stdlib.h>
//Dice program
int dice()
{
    int x=1+rand()%6;
    return x;
}
int main()
{
    int y,S1=0,S2=0,S3=0,S4=0,S5=0,S6=0,i;
    time_t t;
    srand(time(&t));
    for(i=0; i<50000; ++i)
    {
        y=dice();
        if(y==1)
        {
            S1+=1;
        }
        else if(y==2)
        {
            S2+=1;
        }
        else if(y==3)
        {
            S3+=1;
        }
        else if(y==4)
        {
            S4+=1;
        }
        else if(y==5)
        {
            S5+=1;
        }
        else if(y==6)
        {
            S6+=1;
        }
    }
    printf("1:%d times\n2:%d times\n3:%d times\n4:%d times\n5:%d times\n6:%d times\n",S1,S2,S3,S4,S5,S6);
    return 0;

}
