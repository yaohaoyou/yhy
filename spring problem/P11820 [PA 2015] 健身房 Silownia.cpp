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
using namespace std;
const int maxn=1e6+10;
int n,k,m;
piii a[maxn];
int c[maxn<<1],ans[maxn];
set<pii> st;set<int> s;
int bk[maxn<<1];
vector<int> vl[maxn<<1],b[maxn];
unordered_map<int,int> mp;
priority_queue<pii,vector<pii>,greater<pii>> q[maxn];
inline void ins(int x){
    int l=x,r=x;auto it=st.ep(x,x).fi;
    if(it!=st.begin()&&(--it)->se==x-1) l=it->fi,st.erase(pii(l,x-1));
    it=st.find(pii(x,x));
    if((++it)!=st.end()&&it->fi==x+1)   r=it->se,st.erase(pii(x+1,r));
    if(l^r) st.erase(pii(x,x)),st.ep(l,r);
}
void discrete(){
    for(int i=1;i<=n;i++)   c[++m]=a[i].fi.fi,c[++m]=a[i].fi.se;
    sort(c+1,c+m+1);
    m=unique(c+1,c+m+1)-c-1;
    for(int i=1;i<=n;i++)   a[i].fi.fi=lower_bound(c+1,c+m+1,a[i].fi.fi)-c,a[i].fi.se=lower_bound(c+1,c+m+1,a[i].fi.se)-c;
}
int main(){
    scanf("%d%*d",&n);
    for(int i=1;i<=n;i++){
        int l,r,p;
        scanf("%d%d%d",&l,&r,&p);
        if(mp.find(p)==mp.end())    mp[p]=++k;
        p=mp[p];
        a[i]=piii(pii(l,r),p);
        b[p].eb(i);
    }
    for(int i=1;i<=k;i++){
        st.clear();
        sort(b[i].begin(),b[i].end(),[&](int x,int y){return a[x].fi.fi>a[y].fi.fi;});
        for(int j:b[i]){
            int l=a[j].fi.fi,r=a[j].fi.se;
            auto it=st.lower_bound(pii(r+1,0));
            if(it!=st.begin()&&(--it)->se>=r)   r=it->fi-1;
            if(r<l) exit(puts("NIE")&0);
            ins(r);
            a[j].fi.se=r;
        }
    }
    // for(int i=1;i<=n;i++)   if(a[i].se==1)printf("# %d %d %d\n",a[i].fi.fi,a[i].fi.se,a[i].se);
    discrete();
    // for(int i=1;i<=n;i++)   if(a[i].se==1)printf("## %d %d %d\n",c[a[i].fi.fi],c[a[i].fi.se],a[i].se);
    for(int i=1;i<=n;i++)   vl[a[i].fi.fi].eb(i);
    int out=0;
    for(int i=1;i<=m;i++){
        for(int j:vl[i])    q[a[j].se].ep(a[j].fi.se,j),s.ep(a[j].se),bk[a[j].fi.se]++;
        if(bk[i]){
            out++;
            for(auto it=s.begin();it!=s.end();){
                int j=*it;
                ans[q[j].top().se]=i;bk[q[j].top().fi]--;q[j].pop();
                if(q[j].empty())    it=s.erase(it);
                else    it++;
            }
        }
    }
    printf("%d\n",out);
    for(int i=1;i<=n;i++)   printf("%d\n",c[ans[i]]);
}