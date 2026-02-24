#include<bits/stdc++.h>
#define ll long long
#define int long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
const ll INF=1e18;
int n,k,m;
int W2[maxn];ll W3[maxn];
vector<int> v[maxn];
set<pii> q0,q1,q3;
set<pli> q2;
set<pii> st;
bool used[maxn];
int sum[maxn];
pli b[maxn];
inline void add(int x){for(int i=2;i<v[x].size();i++)q1.ep(v[x][i],x);}
main(){
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++){int c,val;scanf("%lld%lld",&c,&val);v[c].eb(val<<1);}
    for(int i=1;i<=k;i++){
        if(v[i].size()<=1)  continue;
        sort(v[i].begin(),v[i].end(),greater<ll>());
        v[i][0]=v[i][1]=(v[i][0]+v[i][1])>>1;
        q0.ep(W2[i]=v[i][0]+v[i][1],i);
        if(v[i].size()>2)   q2.ep(W3[i]=1ll*v[i][0]+v[i][1]+v[i][2],i);
        for(int j:v[i]) b[++m]=pii(j,i);
    }
    sort(b+1,b+m+1,greater<pli>());
    ll ss=0;
    for(int i=1;i<=m;i++){
        ll res=-INF;int id=0;
        int val=b[i].fi,c=b[i].se;
        sum[c]++;ss+=val;
        if(sum[c]>1){
            q0.erase(pii(W2[c],c));q2.erase(pli(W3[c],c));
            if(sum[c]==2)   add(c),st.ep(W2[c],c);
            if(sum[c]==3)   st.erase(pii(W2[c],c));
            if(sum[c]>2)    q1.erase(pii(val,c)),q3.ep(val,c);
            printf("%lld\n",ss>>1);
            continue;
        }
        ll ans=-2;
        if(!q1.empty()) ans=ss-val+prev(q1.end())->fi;
        if(!q3.empty()) ans=max(ans,ss+val-q3.begin()->fi);
        if(!st.empty()&&!q2.empty()) ans=max(ans,ss-val-st.begin()->fi+prev(q2.end())->fi);
        printf("%lld\n",ans>>1);
        q0.erase(pii(W2[c],c));q2.erase(pli(W3[c],c));
    }
    for(int i=m+1;i<=n;i++) puts("-1");
}