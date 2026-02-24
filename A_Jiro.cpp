#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
int main(){
    char c1,c2,c3;
    cin>>c1>>c2>>c3;
    for(int a:{0,1,2}){
        for(int b:{0,1,2}){
            for(int c:{0,1,2}){
                if(c1=='<'&&a>=b)    continue;
                if(c1=='>'&&a<=b)    continue;
                if(c2=='<'&&a>=c)    continue;
                if(c2=='>'&&a<=c)    continue;
                if(c3=='<'&&b>=c)    continue;
                if(c3=='>'&&b<=c)    continue;
                if(a==1) puts("A");
                else if(b==1)   puts("B");
                else    puts("C");
                return 0;
            }
        }
    }
}