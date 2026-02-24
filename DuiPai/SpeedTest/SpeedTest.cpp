#include<bits/stdc++.h>
using namespace std;
int main()
{
    for(int i=1;1;i++)
    {
        system("make_data.exe");
        double begin=clock();
        system("mine.exe");
        double end=clock();
        if(end-begin>1000.0){
            printf("Time Limit Exceed on #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);
            while(1);
        }
        else 
            printf("Accepted #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);  
    }
}
