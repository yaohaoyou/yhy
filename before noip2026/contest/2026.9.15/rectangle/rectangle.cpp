#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define NO exit(puts("syntax error")&0)
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,m;
int ans[maxn];
piii a[maxn],b[maxn];
int c[maxn];
set<pii> st;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n+n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n+n;i++)tr[i]=0;}
}T;
void discrete(){
    for(int i=1;i<=n;i++)   c[++m]=a[i].fi.fi,c[++m]=b[i].fi.fi;
    sort(c+1,c+m+1);m=unique(c+1,c+m+1)-c-1;
    for(int i=1;i<=n;i++)   a[i].fi.fi=lower_bound(c+1,c+m+1,a[i].fi.fi)-c,b[i].fi.fi=lower_bound(c+1,c+m+1,b[i].fi.fi)-c;
    m=0;
    for(int i=1;i<=n;i++)   c[++m]=a[i].fi.se,c[++m]=b[i].fi.se;
    sort(c+1,c+m+1);m=unique(c+1,c+m+1)-c-1;
    for(int i=1;i<=n;i++)   a[i].fi.se=lower_bound(c+1,c+m+1,a[i].fi.se)-c,b[i].fi.se=lower_bound(c+1,c+m+1,b[i].fi.se)-c;
}
vector<int> ins[maxn],era[maxn];
vector<pii> Q[maxn];
struct Rect {int r1, c1, r2, c2;}OUT[maxn];
static bool pairValid(Rect& a,Rect& b) {
    const bool disjoint = a.r2 < b.r1 || b.r2 < a.r1 || a.c2 < b.c1 || b.c2 < a.c1;
    const bool aContainsB = a.r1 < b.r1 && b.r2 < a.r2 && a.c1 < b.c1 && b.c2 < a.c2;
    const bool bContainsA = b.r1 < a.r1 && a.r2 < b.r2 && b.c1 < a.c1 && a.c2 < b.c2;
    return disjoint || aContainsB || bContainsA;
}
// void check(){
    // sort(a+1,a+n+1,[&](piii x,piii y){return x.se<y.se;});
    // sort(b+1,b+n+1,[&](piii x,piii y){return x.se<y.se;});
    // for(int i=1;i<=n;i++){
        // auto [a,b]=::a[i].fi;auto [c,d]=::b[ans[i]].fi;
        // OUT[i]={a,b,c,d};
    // }
    // for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(!pairValid(OUT[i],OUT[j]))NO;
// }
void check(){
    sort(a+1,a+n+1,[&](piii x,piii y){return x.se<y.se;});
    sort(b+1,b+n+1,[&](piii x,piii y){return x.se<y.se;});
    for(int i=1;i<=n;i++){
        auto [a,b]=::a[i].fi;auto [c,d]=::b[ans[i]].fi;
        ins[c].eb(b);ins[c].eb(d);era[a].eb(b);era[a].eb(d);
        Q[c].eb(b,d);Q[a].eb(b,d);
    }
    for(int i=n+n;i;i--){
        for(int j:ins[i])   T.add(j,1);
        for(auto [l,r]:Q[i]){
            int w=T.query(l,r);
            assert(w>=2);
            if(w>2) NO;
        }
        for(int j:era[i])   T.add(j,-1);
        ins[i].clear();Q[i].clear();era[i].clear();
    }
    T.clear();
    for(int i=1;i<=n;i++){
        auto [a,b]=::a[i].fi;auto [c,d]=::b[ans[i]].fi;
        ins[b].eb(a);ins[b].eb(c);era[d].eb(a);era[d].eb(c);
        Q[b].eb(a,c);Q[d].eb(a,c);
    }
    for(int i=1;i<=n+n;i++){
        for(int j:ins[i])   T.add(j,1);
        for(auto [l,r]:Q[i]){
            int w=T.query(l,r);
            assert(w>=2);
            if(w>2) NO;
        }
        for(int j:era[i])   T.add(j,-1);
        ins[i].clear();Q[i].clear();era[i].clear();
    }
}
bool mem2;
int main(){
    freopen("rectangle.in","r",stdin);freopen("rectangle.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi.fi,&a[i].fi.se),a[i].se=i;
    for(int i=1;i<=n;i++)   scanf("%d%d",&b[i].fi.fi,&b[i].fi.se),b[i].se=i;
    discrete();
    // for(int i=1;i<=n;i++)   printf("(%d,%d) ",a[i].fi.fi,a[i].fi.se);puts("");
    // for(int i=1;i<=n;i++)   printf("(%d,%d) ",b[i].fi.fi,b[i].fi.se);puts("");
    sort(a+1,a+n+1,[&](piii x,piii y){return x.fi.se==y.fi.se?x.fi.fi>y.fi.fi:x.fi.se>y.fi.se;});
    sort(b+1,b+n+1,[&](piii x,piii y){return x.fi.se==y.fi.se?x.fi.fi>y.fi.fi:x.fi.se>y.fi.se;});
    for(int i=1,j=1;i<=n;i++){
        while(j<=n&&b[j].fi.se>=a[i].fi.se){
            st.ep(b[j].fi.fi,b[j].se);
            j++;
        }
        auto it=st.lower_bound(pii(a[i].fi.fi,0));
        if(it==st.end())    NO;
        ans[a[i].se]=it->se;
        st.erase(it);
    }
    check();
    for(int i=1;i<=n;i++)   printf("%d\n",ans[i]);
}