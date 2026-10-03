#pragma GCC optimize(2,3,"Ofast")
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
const int maxn=4e5+10,maxq=2e6+10;
int c,n,X,q,q_,e,m;
int w[maxn],Log[maxn];
ull pq[maxn];
vector<piii> Q[20][maxn];
int sa[maxn],rnk[maxn],y[maxn],buc[maxn];
ull ans[maxq];int cnt[maxq];
ull as[20][maxn];int ct[20][maxn];
char s[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,(n+n)
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{
        ull hsh;int cnt;
        tree operator+(tree y){return (tree){hsh+y.hsh*pq[cnt],cnt+y.cnt};}
    }tr[maxn<<2];
    int pos[maxn];
    inline void pu(int p){tr[p]=tr[rs]+tr[ls];}
    void build(setpos){tr[p]=(tree){0,0};if(l==r)return pos[l]=p,void();setmid;build(lson);build(rson);}
    inline void upd(int x){int p=pos[x];tr[p]=(tree){1ull*w[n+n-x+1]*X,1};while(p>>=1)pu(p);}
    tree query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;return pr<=mid?query(lson,pl,pr):(pl>mid?query(rson,pl,pr):query(rson,pl,pr)+query(lson,pl,pr));}
}
using namespace SegmentTree;
void solve(bool T){
    for(int o=0,w=0;o<=Log[n];o++,w<<=1){
        mems(buc,0);
        if(!o){
            m='z';
            for(int i=1;i<=n+n;i++)   buc[rnk[i]=s[i]]++;
            for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
            for(int i=n+n;i;i--)  sa[buc[rnk[i]]--]=i;
        }
        else{
            if(o==1)    w=1;
            int p=0;
            for(int i=n+n-w+1;i<=n+n;i++)   y[++p]=i;
            for(int i=1;i<=n+n;i++)if(sa[i]>w)y[++p]=sa[i]-w;
            for(int i=1;i<=n+n;i++)   buc[rnk[i]]++;
            for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
            for(int i=n+n;i;i--)  sa[buc[rnk[y[i]]]--]=y[i];
        }
        memc(y,rnk);
        m=rnk[sa[1]]=1;
        for(int i=2;i<=n+n;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+w]==y[sa[i-1]+w])    rnk[sa[i]]=rnk[sa[i-1]];
            else    rnk[sa[i]]=++m;
        }
        build(all);
        for(int i=n+n;i;i--){
            int j=i;while(j>1&&rnk[sa[j-1]]==rnk[sa[i]])j--;
            sort(sa+j,sa+i+1);
            for(int _=j;_<=i;_++){
                int x=sa[_];
                if(x<=n){
                    for(auto [seg,id]:Q[o][x]){
                        tree res=query(all,seg.fi,seg.se);
                        if(!T){
                            res.hsh*=pq[cnt[id]];
                            ans[id]+=res.hsh;
                            cnt[id]+=res.cnt;
                        }
                        else{
                            as[o][id]=res.hsh;
                            ct[o][id]=res.cnt;
                        }
                    }
                    Q[o][x].clear();
                }
                else    upd(x);
            }
            i=j;
        }
    }
}
int main() {
    scanf("%*d%d%d%d%d%d%s",&n,&X,&q,&q_,&e,s+1);
    for(int i=n+1;i<=n+n;i++)   s[i]=s[n+n-i+1];
    // for(int i=1;i<=n+n;i++) printf("%c",s[i]);puts("");
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=pq[i-1]*X;
    for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
    for (int i = 1; i <= n; ++i)    scanf("%d",&w[i]);
    mt19937 rng(e);
    auto rnd = [&](uint32_t L, uint32_t R) -> uint32_t {
        uint64_t range = (uint64_t)R - L + 1;
        uint64_t bucket = (1ULL << 32) / range;
        uint64_t limit = bucket * range;
        uint32_t v;
        do {
            v = rng();
        } while ((uint64_t)v >= limit);
        return L + (uint32_t)((uint64_t)v / bucket);
    };
    for(int b=0;b<=Log[n];b++){
        for(int l=1;l<=n;l++)if(l+(1<<b)-1<=n){
            Q[b][l].eb(pii(2*n-min(l+(1<<b+1)-2,n)+1,2*n-l-(1<<b)+2),l);
        }
    }
    solve(1);
    for (int i = 1; i <= q; ++i) {
        int l, r;
        if (i <= q_) {
            scanf("%d%d",&l,&r);
        } else {
            l = rnd(1, n), r = rnd(1, n);
            if (l > r) {
                swap(l, r);
            }
        }
        int b=Log[r-l+1];
        for(;~b;b--)if(l+(1<<b)-1<=r){
            Q[b][l].eb(pii(2*n-min(l+(1<<b+1)-2,r)+1,2*n-l-(1<<b)+2),i);
            break;
        }
        for(int o=0;o<b;o++){
            ans[i]+=as[o][l]*pq[cnt[i]];
            cnt[i]+=ct[o][l];
        }
    }
    solve(0);
    ull res = 0;
    for(int i=1;i<=q;i++)   res^=ans[i]+1ull*i*i*i;
    // for(int i=1;i<=q;i++)   printf("%llu\n",ans[i]);
    printf("%llu\n",res);
}