#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
char s[4]={'w','a','s','d'};
int main(){
    srand(0);
    for(int i=0;i<100000;i++) putchar(s[rand()%4]);
    for(int i=0;i<50;i++)   rand();
    puts("");
    for(int i=0;i<10;i++) putchar(s[rand()%4]);
}