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
const int maxn=5e5+10;
int n;
int a[maxn],b[maxn],pre[maxn],suf[maxn];
int s[maxn];
int ans[maxn];
vector<int> v[maxn];
vector<ll> sum[maxn];
inline ll C2(int x){return 1ll*x*(x-1)/2+x;}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){scanf("%d",&b[i]);v[b[i]].eb(i);}
    for(int i=1;i<=n;i++){
        ll ss=0;
        for(int j:v[i]) ss+=j,sum[i].eb(ss);
    }
    ll out=0;
    for(int i=1;i<=n;i++){
        if(a[i]==b[i])  out+=C2(i-1)+C2(n-i);
        int siz=v[a[i]].size();
        int x=upper_bound(v[a[i]].begin(),v[a[i]].end(),min(i,n-i+1))-v[a[i]].begin();
        if(x)   out+=sum[a[i]][x-1];
        int y=upper_bound(v[a[i]].begin(),v[a[i]].end(),n-i+1)-v[a[i]].begin();
        out+=1ll*i*(y-x);
        if(n-i+1<i){
            int p=upper_bound(v[a[i]].begin(),v[a[i]].end(),i)-v[a[i]].begin();
            out+=1ll*(p-y)*(n-i+1);
        }
        int q=upper_bound(v[a[i]].begin(),v[a[i]].end(),max(i,n-i+1))-v[a[i]].begin();
        out+=1ll*(n+1)*(siz-q);
        if(!sum[a[i]].empty()){
            out-=sum[a[i]].back();
            if(q)   out+=sum[a[i]][q-1];
        }
        // if(q)   printf("+ %d - %d\n",(n+1)*(siz-q),sum[a[i]].back()-sum[a[i]][q-1]);
        // printf("%lld\n",out);
        // (j,i) , (1,i+j-1) : sum j
        // (i,j) , (1,i+j-1) : i*sum
        // n-i+1<j && j<=i
        // (j,i) , (i+j-n,n) : (n-i+1)*sum
        // n-i+1<j && j>i
        // (i,j) , (i+j-n,n) : (n+1)*sum - sum j
        // i-(i+j-n)+1=n-j+1
    }
    printf("%lld\n",out);
}