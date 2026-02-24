#include<bits/stdc++.h>
using namespace std;
int main()
{
    for(int i=1;1;i++)
    {
        system("D:\\yhy\\DuiPai\\SPJ\\make_data.exe");
        double begin=clock();
        system("D:\\yhy\\DuiPai\\SPJ\\mine.exe");
        double end=clock();
        if(system("D:\\yhy\\GDFZ_yhy\\down\\pixel\\checker.exe \"D:\\yhy\\DuiPai\\SPJ\\data.in\" \"D:\\yhy\\DuiPai\\SPJ\\mine.out\" \"D:\\yhy\\DuiPai\\SPJ\\checker.out\""))
            {
                printf("Wa on #%d\n--------------------------------------",i);
                while(1);
            } 
        if(end-begin>1000.0){
            printf("Time Limit Exceed on #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);
            while(1);
        }
        else 
            printf("Accepted #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);  
    }
}
