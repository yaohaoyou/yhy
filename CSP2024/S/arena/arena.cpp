#include<bits/stdc++.h>
#define ll long long
#define db double
#define pii pair<int,int>
#define pb push_back
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10;
int n,q,N;
int aa[maxn],c[maxn],a[maxn],x[4];
vector<bool> d[maxn];
ll res;
unordered_set<int> s;
void dfs(int R,vector<int> v){
    if(v.size()==1){
        if(s.find(v[0])==s.end())   res+=v[0];
        s.insert(v[0]);
        return;
    }
    vector<pii> nxt;nxt.clear();
    int rou=0,cnt=0;
    for(int i=0;i<v.size();i+=2){
        rou++;
        int x=v[i],y=v[i+1];
        if(d[R][rou])   swap(x,y);
        if(x<=N){
            if(a[x]>=R) nxt.pb(pii(x,0));
            else    nxt.pb(pii(y,0));
        }
        else{nxt.pb(pii(x,y));cnt++;}
    }
    for(int i=0;i<1<<cnt;i++){
        int k=0;
        vector<int> tmp;tmp.clear();
        for(int j=0;j<nxt.size();j++){
            if(nxt[j].se){
                if(i&(1<<k))    tmp.pb(nxt[j].se);
                else    tmp.pb(nxt[j].fi);
                k++;
            }
            else    tmp.pb(nxt[j].fi);
        }
        dfs(R+1,tmp);
    }
}
namespace Task123{
    bool check(){return n<=8&&q<=8;}
    void solve(){
        for(int i=0;i<4;i++)    scanf("%d",&x[i]);
        for(int i=1;i<=n;i++)   a[i]=aa[i]^x[i%4];
        ll ans=0;
        vector<int> tmp;
        for(int Q=1;Q<=q;Q++){
            res=0;s.clear();
            tmp.clear();
            int k=ceil(log10(c[Q])/log10(2));
            for(int i=1;i<=(1<<k);i++)    tmp.pb(i);
            N=c[Q];
            dfs(1,tmp);
            ans^=(1ll*Q*res);
        }
        printf("%lld\n",ans);
    }
}
namespace Task451112{
    bool check(){for(int i=1;i<=q;i++){int k=log10(c[i])/log10(2);if((1<<k)!=c[i])return false;}return true;}
    ll out[maxn];
    void solve(){
        for(int i=0;i<4;i++)    scanf("%d",&x[i]);
        for(int i=1;i<=n;i++)   a[i]=aa[i]^x[i%4];
        ll ans=0;
        vector<int> tmp;
        for(int i=1;i<=n;i<<=1){
            res=0;s.clear();
            tmp.clear();
            for(int j=1;j<=i;j++)    tmp.pb(j);
            N=i;
            dfs(1,tmp);
            out[i]=res;
        }
        for(int Q=1;Q<=q;Q++)
            ans^=(Q*out[c[Q]]);
        printf("%lld\n",ans);
    }
}
int main(){
    freopen("arena.in","r",stdin);freopen("arena.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&aa[i]);
    for(int i=1;i<=q;i++)   scanf("%d",&c[i]);
    int K=1;
    while((1<<K)<n) K++;
    for(int i=1;i<=K;i++){
        d[i].pb(0);
        for(int j=1;j<=(1<<K-i);j++){
            int x;
            scanf("%1d",&x);
            d[i].pb(x);
        }
    }
    int T;scanf("%d",&T);
    if(Task123::check())while(T--)Task123::solve();
    if(Task451112::check())while(T--)Task451112::solve();
}