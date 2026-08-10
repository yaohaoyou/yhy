#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
const int maxn=5e4+10;
int n,q;
int a[maxn];
ll s[maxn],b[maxn];
vector<ll> ans[maxn];
int Log[maxn];
struct ST{
    vector<ll> st[20];
    void build(vector<ll> v,int m){
        for(int i=2;i<=m;i++)   Log[i]=Log[i/2]+1;
        st[0]=v;
        for(int i=1;i<=Log[m];i++)  st[i].resize(m+1);
        for(int i=1;i<=Log[m];i++)
            for(int j=1;j+(1<<i)-1<=m;j++)  st[i][j]=max(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline ll query(int l,int r){int k=Log[r-l+1];return max(st[k][l],st[k][r-(1<<k)+1]);}
}st[maxn];
pii Q[maxn];
deque<int> dq;
bool mem2;
namespace SpecialA{
    bool check(){for(int i=1;i<=q;i++)if(Q[i].fi^Q[i].se)return false;return true;}
    void solve(){
        for(int _=1;_<=q;_++){
            int i=Q[_].fi;
            dq.clear();
            ull ans=0;
            for(int l=1,r=i;r<=n;l++,r++){
                while(!dq.empty()&&dq.front()<l-i+1)    dq.pop_front();
                b[l]=s[r]-s[l-1];
                while(!dq.empty()&&b[dq.back()]<b[l])   dq.pop_back();
                dq.push_back(l);
                ans^=1ull*l*b[dq.front()];
            }
            for(int j=n-i+2;j<=n;j++){
                while(!dq.empty()&&dq.front()<j-i+1)    dq.pop_front();
                ans^=1ull*j*b[dq.front()];
            }
            printf("%llu\n",ans);
        }
        exit(0);
    }
}
void MATT(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    scanf("%d",&q);
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].fi,&Q[i].se);
    if(SpecialA::check())   SpecialA::solve();
    int len=0;for(int i=1;i<=q;i++)len=max(len,Q[i].se);
    for(int i=1;i<=n;i++)   ans[i].push_back(0);
    for(int i=1;i<=len;i++){
        dq.clear();
        for(int l=1,r=i;r<=n;l++,r++){
            while(!dq.empty()&&dq.front()<l-i+1)    dq.pop_front();
            b[l]=s[r]-s[l-1];
            while(!dq.empty()&&b[dq.back()]<b[l])   dq.pop_back();
            dq.push_back(l);
            ans[l].push_back(b[dq.front()]);
        }
        for(int j=n-i+2;j<=n;j++){
            while(!dq.empty()&&dq.front()<j-i+1)    dq.pop_front();
            ans[j].push_back(b[dq.front()]);
        }
    }
    for(int i=1;i<=n;i++)   st[i].build(ans[i],len);
    for(int _=1;_<=q;_++){
        int l=Q[_].fi,r=Q[_].se;
        ull ans=0;
        for(int i=1;i<=n;i++)   ans^=1ull*i*st[i].query(l,r);
        printf("%llu\n",ans);
    }
}
int main(){
    // freopen("query.in","r",stdin);freopen("query.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=1;while(T--)MATT();
}