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
#define TIME chrono::system_clock::now().time_since_epoch().count()
int rnd_seed = TIME;
mt19937 matt(rnd_seed);
inline int rndI(){return abs(int(matt()));}
int main(){
    freopen("D:\\yhy\\DuiPai\\SPJ\\data.in","w",stdout);
    int x=rndI()%100+1,y=rndI()%(x*x*x)+1;
    printf("%d %d\n",x,y);
}