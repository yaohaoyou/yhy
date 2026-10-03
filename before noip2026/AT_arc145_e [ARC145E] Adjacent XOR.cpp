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
bool mem1;
const int maxn=1010;
int n;
ll a[maxn],b[maxn],c[maxn];  // c[i] 表示操作成 b[i] 的集合
struct Linear_basis{
    int tot;
    ll p[80];int id[80],pos[80];
    void init(){tot=0;mems(p,0);mems(id,0);mems(pos,0);}
    bool find(ll x){
        for(int i=59;~i;i--)if(x&(1ll<<i)){
            if(!p[i])   return false;
            x^=p[i];
        }
        return true;
    }
    ll insert(ll x){
        ll res=0;  // 构成 x 的集合
        for(int i=59;~i;i--){
            if(x&(1ll<<i)){
                if(!p[i]){
                    p[i]=x;
                    id[i]=++tot;
                    res|=(1ll<<tot-1);
                    return res;
                }
                x^=p[i];
                res|=(1ll<<id[i]-1);
            }
        }
        return res;
    }
}lb;
vector<int> ans;
void solve(int x){ans.eb(x);for(int i=1;i<=x;i++)b[i]^=b[i-1],c[i]^=c[i-1];}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%lld",&b[i]);
    lb.init();
    for(int i=1;i<=n;i++){
        if(!lb.find(a[i]^b[i])) return puts("No"),0;
        lb.insert(b[i]);
    }
    for(int i=n;i;i--){
        lb.init();
        for(int j=1;j<=i;j++){
            bool fl=lb.find(b[j]);
            c[j]=lb.insert(b[j]);
            if(!fl) lb.pos[lb.tot-1]=j,assert(lb.tot-1==__lg(c[j]));
        }
        ll nd=lb.insert(a[i]);
        for(int j=lb.tot-1;~j;j--){
            ll now=0;for(int k=1;k<=i;k++)now^=c[k];
            if((now&(1ll<<j))!=(nd&(1ll<<j)))   solve(lb.pos[j]+1);
        }
        solve(i);
    }
    printf("Yes\n%d\n",ans.size());
    reverse(ans.begin(),ans.end());for(int i:ans)   printf("%d ",i);
}