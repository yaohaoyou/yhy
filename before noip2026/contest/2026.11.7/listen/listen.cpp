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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5e5+10,N=4e5;
int n,q;
multiset<piii> s;
struct SET{
    priority_queue<int,vector<int>,greater<int>> q1,q2;
    inline void clear(){while(!q1.empty())q1.pop();while(!q2.empty())q2.pop();}
    inline void ep(int x){q1.ep(x);}
    inline void erase(int x){q2.ep(x);}
    inline int top(){while(!q2.empty()&&q1.top()==q2.top())q1.pop(),q2.pop();return q1.top();}
    inline void pop(){q1.pop();}
    inline bool empty(){return q1.size()==q2.size();}
}st;
int cnt[maxn];
struct DSU{
    int fa[maxn],mx[maxn],cir[maxn],siz[maxn];
    stack<piii> stk;
    void init(){iota(fa,fa+N+1,0);iota(mx,mx+N+1,0);fll(cir,0,N);fll(siz,1,N);}
    inline int find(int x){while(fa[x]^x)x=fa[x];return x;}
    inline void merge(int x,int y){
        x=find(x);y=find(y);
        if(siz[x]<siz[y])swap(x,y);
        if(x^y){
            if(!cir[x]) st.erase(mx[x]);
            if(!cir[y]) st.erase(mx[y]);
            stk.ep(pii(mx[x],cir[x]),y);
            fa[y]=x;
            gmx(mx[x],mx[y]);
            cir[x]+=cir[y];siz[x]+=siz[y];
            if(!cir[x]) st.ep(mx[x]);
        }
        else{
            if(!cir[x]) st.erase(mx[x]);
            stk.ep(pii(mx[x],cir[x]),x),cir[x]++;
        }
    }
    inline void bck(int sz){
        while(stk.size()^sz){
            int y=stk.top().se,x=fa[y];
            if(x^y)siz[x]-=siz[y];
            if(!cir[x]) st.erase(mx[x]);
            if(x!=y&&!cir[y]) st.ep(mx[y]);
            fa[y]=y;mx[x]=stk.top().fi.fi;cir[x]=stk.top().fi.se;
            if(!cir[x]) st.ep(mx[x]);
            stk.pop();
        }
    }
    inline int operator[](int x){return find(x);}
}U;
int sm[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,0,q
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<pii> v[maxn<<2];
    inline void upd(setpos,int pl,int pr,pii x){if(l>=pl&&r<=pr)return v[p].eb(x),void();setmid;if(pl<=mid)upd(lson,pl,pr,x);if(pr>mid)upd(rson,pl,pr,x);}
    void dfs(setpos){
        int sz=U.stk.size();
        for(auto [i,j]:v[p])    U.merge(i,j);
        if(l==r)    printf("%d\n",sm[l]+st.top());
        else{setmid;dfs(lson);dfs(rson);}
        U.bck(sz);
    }
}
using namespace SegmentTree;
int main(){
    freopen("listen.in","r",stdin);freopen("listen.out","w",stdout);
    scanf("%d%d",&n,&q);
    for(int i=0;i<=N;i++)st.ep(i);
    for(int i=1;i<=n;i++){
        int x,y;scanf("%d%d",&x,&y);
        gmn(x,N);gmn(y,N);
        s.ep(pii(x,y),0);
        cnt[x]++;if(cnt[x]==2)st.erase(x);
        cnt[y]++;if(cnt[y]==2)st.erase(y);
    }
    sm[0]=st.top();
    for(int i=1;i<=q;i++){
        char op[5];int x,y;
        scanf("%s%d%d",op,&x,&y);
        gmn(x,N);gmn(y,N);
        if(op[0]=='-'){
            auto it=s.lower_bound(piii(pii(x,y),0));
            upd(all,it->se,i-1,it->fi);
            s.erase(it);
            if(cnt[x]==2)st.ep(x);cnt[x]--;
            if(cnt[y]==2)st.ep(y);cnt[y]--;
        }
        else{
            s.ep(pii(x,y),i);
            cnt[x]++;if(cnt[x]==2)st.erase(x);
            cnt[y]++;if(cnt[y]==2)st.erase(y);
        }
        sm[i]=st.top();
    }
    st.clear();
    for(auto it=s.begin();it!=s.end();it++) upd(all,it->se,q,it->fi);
    U.init();
    for(int i=0;i<=N;i++)st.ep(i);
    dfs(all);
}