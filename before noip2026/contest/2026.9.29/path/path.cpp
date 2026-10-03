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
bool mem1;
const int maxn=5e5+10;
int n,m,e;
int c[maxn],d[maxn],deg[maxn],L[maxn],mn[maxn];
vector<int> v[maxn];
pii a[maxn];
priority_queue<ll,vector<ll>,greater<ll>> q;
struct odt{
    int l,r,v;odt(int x=0,int y=0,int w=0){l=x;r=y;v=w;}
    inline bool operator<(odt x)const{return l<x.l;}
};
set<odt> s;
inline auto split(int p){
    auto it=s.lower_bound(odt(p));
    if(it!=s.end()&&it->l==p)   return it;
    if(it==s.begin()) return s.end();
    it--;
    if(it->r<p) return s.end();
    int l=it->l,r=it->r,v=it->v;
    s.erase({l,r,v});s.ep(l,p-1,v);
    return s.ep(p,r,v).fi;
}
set<int> now;
void chk(int l,int r){
    auto it=now.upper_bound(r);
    while(it!=now.begin()){
        it--;
        if(*it>=l)  it=now.erase(it);
        else    break;
    }
}
bool mem2;
ll findEdges(int N,vector<int> A,vector<int> B){
    n=N;m=A.size();
    mems(mn,0x3f);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    deg[1]=deg[n]=1;
    for(int i=2;i<n;i++)deg[i]=2;
    for(int i=1;i<=m;i++){
        int l=A[i-1],r=B[i-1];if(l>r)swap(l,r);
        v[r].eb(l);
        gmn(mn[r],l);
        deg[l]++;deg[r]++;
        if(l+1<=r-1)    c[l+1]++,c[r]--;
        if(l<=r-1)  d[l]++,d[r]--;
    }
    for(int i=1;i<n;i++){
        d[i]+=d[i-1];
        if(!d[i]){
            q.ep(1ll*i*(n-i));
            while(q.size()>2)  q.pop();
        }
    }
    ll ans=0;
    while(!q.empty())   ans+=q.top(),q.pop();
    set<int> st;
    for(int i=n;i;i--){
        auto it=st.upper_bound(i);
        L[i]=it==st.begin()?0:*prev(it);
        for(int j:v[i]) st.ep(j);
    }
    for(int i=1;i<=n;i++){
        if(i<=mn[i])    now.ep(i);
        {
            auto it=s.end();
            int l=i;
            while(it!=s.begin()){
                it--;if(it->v<=mn[i])break;
                l=it->l;
                if(it->r>mn[i]) chk(max(it->l,mn[i]+1),it->r);
                it=s.erase(it);
            }
            s.ep(l,i,mn[i]);
        }
        L[i]++;
        auto it=now.lower_bound(max(L[i],i-n/2+1));
        if(it!=now.end())   gmx(ans,1ll*(i-(*it)+1)*(n-i+(*it)-1));
        if(it!=now.end()&&next(it)!=now.end()) gmx(ans,1ll*(i-*next(it)+1)*(n-i+*next(it)-1));
        if(it!=now.begin()){
            it--;
            if(*it>=L[i])   gmx(ans,1ll*(i-(*it)+1)*(n-i+(*it)-1));
        }
    }
    for(int i=1;i<n;i++){
        if(d[i]<=1) gmx(ans,1ll*i*(n-i));
    }
    for(int i=1;i<=n;i++){
        c[i]+=c[i-1];
        if(deg[i]<=2){
            if(!c[i])   gmx(ans,1ll*(i-1)*(n-i)+n-1);
            else    gmx(ans,n-1);
        }
    }
    return ans<<1;
}