#include<bits/stdc++.h>
using namespace std;
int main()
{
//    freopen("DuiPai.txt","w",stdout);
    puts("start compiling");
    system("g++ D:\\yhy\\DuiPai\\SpeedTest\\make_data.cpp -o D:\\yhy\\DuiPai\\SpeedTest\\make_data.exe -O2 -std=c++14 -static");
    system("g++ D:\\yhy\\DuiPai\\SpeedTest\\mine.cpp -o D:\\yhy\\DuiPai\\SpeedTest\\mine.exe -O2 -std=c++14 -static");
    puts("finish compiling");
    for(int i=1;1;i++)
    {
        system("D:\\yhy\\DuiPai\\SpeedTest\\make_data.exe>D:\\yhy\\DuiPai\\SpeedTest\\data.in");
        double begin=clock();
        system("D:\\yhy\\DuiPai\\SpeedTest\\mine.exe<D:\\yhy\\DuiPai\\SpeedTest\\data.in>D:\\yhy\\DuiPai\\SpeedTest\\mine.out");
        double end=clock();
        if(end-begin>2000){
            printf("Time Limit Exceed on #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);
            while(1);
        }
        else 
            printf("Accepted #%d  time: %.0lfms\n--------------------------------------\n",i,end-begin);  
    }
}
