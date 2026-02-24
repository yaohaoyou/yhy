#include<bits/stdc++.h>
using namespace std;
int main()
{
//    freopen("DuiPai.txt","w",stdout);
    puts("start compiling");
    system("g++ D:\\yhy\\DuiPai\\Normal\\make_data.cpp -o D:\\yhy\\DuiPai\\Normal\\make_data.exe -O2 -std=c++14 -static");
    system("g++ D:\\yhy\\DuiPai\\Normal\\std.cpp -o D:\\yhy\\DuiPai\\Normal\\std.exe -O2 -std=c++14 -static");
    system("g++ D:\\yhy\\DuiPai\\Normal\\mine.cpp -o D:\\yhy\\DuiPai\\Normal\\mine.exe -O2 -std=c++14 -static");
    puts("finish compiling");
    for(int i=1;1;i++)
    {
        system("D:\\yhy\\DuiPai\\Normal\\make_data.exe>D:\\yhy\\DuiPai\\Normal\\data.in");
        double begin=clock(); 
        system("D:\\yhy\\DuiPai\\Normal\\std.exe<D:\\yhy\\DuiPai\\Normal\\data.in>D:\\yhy\\DuiPai\\Normal\\std.out");
        double end=clock();
        printf("std #%d  time:%.0lfms\n",i,end-begin);
        begin=clock();
        system("D:\\yhy\\DuiPai\\Normal\\mine.exe<D:\\yhy\\DuiPai\\Normal\\data.in>D:\\yhy\\DuiPai\\Normal\\mine.out");
        end=clock();
        if(system("fc D:\\yhy\\DuiPai\\Normal\\mine.out D:\\yhy\\DuiPai\\Normal\\std.out"))
            {
                printf("Wa on #%d\n--------------------------------------",i);
                while(1);
            } 
        if(end-begin>2000){
            printf("Time Limit Exceed on #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);
            while(1);
        }
        else 
            printf("Accepted #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);  
    }
}
