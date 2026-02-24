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
const int maxn=1e6+10;
int n,q;
unordered_map<ll,ll> tag;
inline ll fa(ll x){
    x--;
    ll l=1,r=sqrt(x+x)+10,res=0;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(mid*(mid+1)/2<=x)    res=mid,l=mid+1;
        else r=mid-1;
    }
    return res;
}
int main(){
    scanf("%d%d",&n,&q);
    while(q--){
        int op,x;ll c;scanf("%d%d",&op,&x);
        int u=fa(x);
        while(u){
            if(tag.find(u)!=tag.end())    tag[x]|=tag[u];
            u=fa(u);
        }
        if(op==1){
            scanf("%d",&c);tag[x]|=c;
            
        }
    }
}