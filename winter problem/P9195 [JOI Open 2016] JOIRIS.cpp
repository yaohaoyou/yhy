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
const int maxn=100;
int n,k;
int a[maxn],b[maxn],cc[maxn],s[maxn];
vector<pii> ans;
inline void chk(){
    int mn=1e9;
    for(int i=1;i<=n;i++)if(!a[i])return;else mn=min(mn,a[i]);
    for(int i=1;i<=n;i++)a[i]-=mn;
}
inline void put(){for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");}
inline void slv1(int x){ans.eb(1,x);a[x]+=k;chk();}
inline void slv2(int x){ans.eb(2,x);for(int i=x;i<x+k;i++)a[i]++;chk();}
int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[i]=(a[i]%k-a[i-1]%k+k)%k;
    for(int i=1;i<=n+1;i++)   (s[i%k]+=b[i])%=k;
    for(int i=0;i<k;i++)if(i!=1&&i!=(n+1)%k&&s[i])  return puts("-1"),0;
    for(int i=2;i<=n;i++)while(a[i]<a[i-1])slv1(i);
    for(int i=2;i+k-1<=n;i++){
        int c=(k-b[i])%k;
        while(c--){
            (++b[i])%=k;(b[i+k]+=k-1)%=k;
            int mx=0;
            for(int j=i;j<i+k;j++)mx=max(mx,a[j]);
            for(int j=1;j<i;j++)while(a[j]<mx+1)slv1(j);
            for(int j=i+k;j<=n;j++)while(a[j]<mx+1)slv1(j);
            slv2(i);
            chk();
        }
    }
    int i=1;while(i+k<=n+1)i+=k;
    for(;i>1;i-=k){
        int c=b[i];
        while(c--){
            (++b[i-k])%=k;(b[i]+=k-1)%=k;
            int mx=0;
            for(int j=i-k;j<i;j++)mx=max(mx,a[j]);
            for(int j=1;j<i-k;j++)while(a[j]<mx+1)slv1(j);
            for(int j=i;j<=n;j++)while(a[j]<mx+1)slv1(j);
            slv2(i-k);
            chk();
        }
    }
    int mx=0;for(int i=1;i<=n;i++)mx=max(mx,a[i]);
    for(int i=1;i<=n;i++)cc[i]=(mx-a[i])/k;
    for(int i=1;i<=n;i++)while(cc[i]--)slv1(i);
    chk();
    assert(count(a+1,a+n+1,0)==n);
    printf("%d\n",ans.size());
    for(auto [i,j]:ans) printf("%d %d\n",i,j);
}