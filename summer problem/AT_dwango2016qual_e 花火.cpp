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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
int n;
priority_queue<ll> q;
int main(){
    scanf("%d%*d",&n);
    ll k=0,b=0;  // 最右侧的点是 y=kx+b
    for(int i=1,lst=0;i<=n;i++){
        ll t,p;scanf("%lld%lld",&t,&p);
        if(t^lst){while(k>0)k--,b+=q.top(),q.pop();}
        k++;b-=p;q.ep(p);q.ep(p);
        lst=t;
    }
    while(k>0)  k--,b+=q.top(),q.pop();
    printf("%lld\n",b);
}