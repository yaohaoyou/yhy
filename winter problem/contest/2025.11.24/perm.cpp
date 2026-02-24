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
const int maxn=1e5+10,maxm=1e6+10,B=100;
int n,m,q;
int a[maxn],b[maxn];
ll sum[maxm];
vector<int> v[maxn];
vector<pii> Q[maxn];
ll buc[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=m){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
int main(){
    freopen("perm.in","r",stdin);freopen("perm.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        v[a[i]].eb(i);
    }
    iota(b+1,b+m+1,1);
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans+=T.query(a[i]+1,m);
        T.add(a[i],1);
    }
    for(int i=1;i<=q;i++){
        int x;scanf("%d",&x);
        if(v[b[x]].size()<=B&&v[b[x+1]].size()<=B){
            for(int j=0,k=0;j<v[b[x+1]].size();j++){
                while(k<v[b[x]].size()&&v[b[x]][k]<v[b[x+1]][j]){
                    k++;
                }
                sum[i]+=k;
            }
            sum[i]<<=1;sum[i]-=1ll*v[b[x]].size()*v[b[x+1]].size();
        }
        else if(v[b[x]].size()>B){
            Q[b[x]].eb(b[x+1],i);
            sum[i]=1ll*v[b[x]].size()*v[b[x+1]].size();
        }
        else{
            Q[b[x+1]].eb(b[x],i);
            sum[i]=-1ll*v[b[x]].size()*v[b[x+1]].size();
        }
        swap(b[x],b[x+1]);
    }
    for(int i=1;i<=m;i++){
        if(Q[i].empty())  continue;
        mems(buc,0);
        int cnt=0;
        for(int j=n;j;j--){
            cnt+=(a[j]==i);
            buc[a[j]]+=cnt;
        }
        for(auto [j,k]:Q[i]){
            if(sum[k]>=0)    sum[k]-=buc[j]*2;
            else    sum[k]+=buc[j]*2;
        }
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans+=sum[i]);
}