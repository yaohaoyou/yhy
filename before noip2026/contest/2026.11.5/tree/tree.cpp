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
const int maxn=4e5+10;
int n,m,N;
int a[maxn],b[maxn],ls[maxn],rs[maxn],mn[maxn],siz[maxn];
unordered_map<int,int> c;
int d[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,N
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tim;
    int tr[maxn<<2][2],tag[maxn<<2],ti[maxn<<2];
    inline void chk(int p){if(ti[p]^tim)tr[p][0]+=tr[p][1],tr[p][1]=0,tag[p]=0,ti[p]=tim;}
    inline void pu(int p){chk(ls);chk(rs);tr[p][0]=tr[ls][0]+tr[rs][0];tr[p][1]=tr[ls][1]+tr[rs][1];}
    inline void pt(int p,int s){chk(p);if(!s)return;if(s>0)tr[p][1]+=tr[p][0],tr[p][0]=0,tag[p]=1;else tr[p][0]+=tr[p][1],tr[p][1]=0,tag[p]=-1;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    int Q(setpos,int pl,int pr){chk(p);if(l>=pl&&r<=pr)return !tr[p][0];setmid,res=1;pd(p);if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)gmn(res,Q(rson,pl,pr));return res;}
    void upd(setpos,int pl,int pr,int s){
        chk(p);
        if(l>=pl&&r<=pr)    return pt(p,s);
        setmid;pd(p);if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);
        pu(p);
    }
    int bry(setpos,int pl,bool o){
        chk(p);
        if(!tr[p][o])   return 0;
        if(l==r)    return l;
        setmid;pd(p);
        if(pl>mid)  return bry(rson,pl,o);
        int res=bry(lson,pl,o);if(res)return res;
        return bry(rson,pl,o);
    }
    void build(setpos){if(l==r)return tr[p][0]=1,void();setmid;build(lson);build(rson);pu(p);}
    #undef ls
    #undef rs
}
using namespace SegmentTree;
void dfs1(int u){siz[u]=1;if(ls[u])dfs1(ls[u]),siz[u]+=siz[ls[u]];if(rs[u])dfs1(rs[u]),siz[u]+=siz[rs[u]];if(siz[ls[u]]>siz[rs[u]])swap(ls[u],rs[u]);}
void dfs(int u){
    if(ls[u])dfs(ls[u]);
    vector<piii> res;
    bool o=Q(all,1,1);int x=1;
    while(x){
        int y=bry(all,x,!o);assert(y!=x);
        if(!y)y=N+1;
        res.eb(pii(x,y-1),o);
        if(y<=N)    x=y,o^=1;
        else    break;
    }
    if(a[u]>=b[u]){
        int l=m-a[u],r=m-b[u]-1;
        if(l<=r){
            l=c[l];r=c[r+1]-1;
            vector<piii> tmp;
            for(auto [seg,w]:res){
                int i=seg.fi,j=seg.se;
                if(max(l,i)<=min(r,j)){
                    if(max(l,i)>i)  tmp.eb(pii(i,max(l,i)-1),w);
                    tmp.eb(pii(max(l,i),min(r,j)),w+1);
                    if(min(r,j)<j)  tmp.eb(pii(min(r,j)+1,j),w);
                }
                else    tmp.eb(seg,w);
            }
            res.swap(tmp);
        }
        tim++;
        if(rs[u])dfs(rs[u]);
        int k=1e9;
        for(auto [s,w]:res) gmn(k,Q(all,s.fi,s.se)+w);
        mn[u]=mn[ls[u]]+mn[rs[u]]+k;
        for(auto [s,w]:res)if(w^k)upd(all,s.fi,s.se,w-k);
    }
    else{
        for(auto [l,r]:{pii(0,m-b[u]-1),pii(m-a[u],m-1)}){
            if(l>r)continue;
            l=c[l];r=c[r+1]-1;
            vector<piii> tmp;
            for(auto [seg,w]:res){
                int i=seg.fi,j=seg.se;
                if(max(l,i)<=min(r,j)){
                    if(max(l,i)>i)  tmp.eb(pii(i,max(l,i)-1),w);
                    tmp.eb(pii(max(l,i),min(r,j)),w+1);
                    if(min(r,j)<j)  tmp.eb(pii(min(r,j)+1,j),w);
                }
                else    tmp.eb(seg,w);
            }
            res.swap(tmp);
        }
        tim++;
        if(rs[u])dfs(rs[u]);
        int k=1e9;
        for(auto [s,w]:res) gmn(k,Q(all,s.fi,s.se)+w);
        mn[u]=mn[ls[u]]+mn[rs[u]]+k;
        for(auto [s,w]:res)if(w^k)upd(all,s.fi,s.se,w-k);
    }
}
void discrete(){
    sort(d+1,d+N+1);N=unique(d+1,d+N+1)-d-1;
    for(int i=1;i<=N;i++)   c[d[i]]=i;
}
bool mem2;
int main(){
    // freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d%d",&a[i],&b[i],&ls[i],&rs[i]);
        d[++N]=m-b[i];if(a[i])d[++N]=m-a[i];
    }
    d[++N]=0;d[++N]=m;
    discrete();N--;
    // printf("N = %d\n",N);
    build(all);
    dfs1(1);dfs(1);
    printf("%d\n",min(mn[1]+1,mn[1]+Q(all,1,1)));
}