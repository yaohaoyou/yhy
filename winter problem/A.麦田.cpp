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
int a[maxn];
ll s[maxn],w[maxn];
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    // vector<pii> v;
    // for(int i=1;i<=n;i++){
    //     int j=i+1;while(j<=n&&a[j]>a[j-1])j++;j--;
    //     v.eb(i,j);
    //     i=j;
    // }
    // for(int i=0;i<v.size();i++){
    //     auto [l,r]=v[i];
    //     s[i]=accumulate(a+l,a+r+1,0ll);
    //     w[i]=a[l];
    //     for(int j=l+1;j<=r;j++)   w[i]+=max(a[j],a[r+1]);
    // }
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        vector<pii> v;
        for(int i=l;i<=r;i++){
            int j=i+1;while(j<=r&&a[j]>a[j-1])j++;j--;
            v.eb(i,j);
            i=j;
        }
        ll ans=0;
        for(auto [vl,vr]:v){
            if(r==vr){ans+=accumulate(a+vl,a+vr+1,0ll);continue;}
            ans+=a[vl];
            if(vl^vr)   ans+=max(a[vl],a[vr+1]);
            for(int i=vl+2;i<=vr;i++) ans+=max(a[i],a[vr+1]);
        } 
        printf("%lld\n",ans);
    }
}