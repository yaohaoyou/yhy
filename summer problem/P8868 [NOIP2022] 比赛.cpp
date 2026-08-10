#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2.5e5+10;
int n,q;
int a[maxn],b[maxn];
ll c[maxn],w[maxn];
vector<pii> Q[maxn];
ull ans[maxn],sw[maxn];
struct Stack{
    int s[maxn],tp;
    inline void clear(){tp=0;}
    inline bool empty(){return !tp;}
    inline void ep(int x){s[++tp]=x;}
    inline void pop(){tp--;}
    inline int top(){return s[tp];}
    inline int size(){return tp;}
    int& operator[](int x){return s[x];}
}stk[2];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define pos p,l,r
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    struct tree{ll suma,sumb,sumx;ull hisx;}tr[maxn<<2];
    struct lazy{int hcnt;ll taga,tagb,hisa,hisb;ull hisx;}tag[maxn<<2];
    inline void pu(int p){tr[p]={tr[ls].suma+tr[rs].suma,tr[ls].sumb+tr[rs].sumb,tr[ls].sumx+tr[rs].sumx,tr[ls].hisx+tr[rs].hisx};}
    inline void ptadda(setpos,ll s){tag[p].taga+=s;tr[p].suma+=s*(r-l+1);tr[p].sumx+=s*tr[p].sumb;}
    inline void ptaddb(setpos,ll s){tag[p].tagb+=s;tr[p].sumb+=s*(r-l+1);tr[p].sumx+=s*tr[p].suma;}
    inline void pthis(setpos,int s,ll va,ll vb,ll vx){
        tag[p].hcnt+=s;
        tag[p].hisa+=tag[p].taga*s+va;tag[p].hisb+=tag[p].tagb*s+vb;
        tag[p].hisx+=vx+tag[p].taga*vb+tag[p].tagb*va+tag[p].taga*tag[p].tagb*s;
        tr[p].hisx+=tr[p].sumx*s+tr[p].suma*vb+tr[p].sumb*va+vx*(r-l+1);
    }
    inline void pd(setpos){
        if(tag[p].hcnt||tag[p].hisa||tag[p].hisb||tag[p].hisx){
            setmid;
            pthis(lson,tag[p].hcnt,tag[p].hisa,tag[p].hisb,tag[p].hisx);
            pthis(rson,tag[p].hcnt,tag[p].hisa,tag[p].hisb,tag[p].hisx);
            tag[p].hcnt=tag[p].hisa=tag[p].hisb=tag[p].hisx=0;
        }
        if(tag[p].taga){setmid;ptadda(lson,tag[p].taga);ptadda(rson,tag[p].taga);tag[p].taga=0;}
        if(tag[p].tagb){setmid;ptaddb(lson,tag[p].tagb);ptaddb(rson,tag[p].tagb);tag[p].tagb=0;}
    }
    void upda(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return ptadda(pos,s);pd(pos);setmid;if(pl<=mid)upda(lson,pl,pr,s);if(pr>mid)upda(rson,pl,pr,s);pu(p);}
    void updb(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return ptaddb(pos,s);pd(pos);setmid;if(pl<=mid)updb(lson,pl,pr,s);if(pr>mid)updb(rson,pl,pr,s);pu(p);}
    ull query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p].hisx;pd(pos);setmid;ull res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
}
using namespace SegmentTree;
int main(){
    scanf("%*d%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[r].eb(l,i);}
    for(int i=1;i<=n;i++){
        // int mx=0,mx2=0;
        // for(int j=i;j;j--)  mx=max(mx,a[j]),mx2=max(mx2,b[j]),c[j]=1ll*mx*mx2;
        // for(int j=1;j<=i;j++)   w[j]+=c[j];
        // for(int j=i;j;j--)      sw[j]=sw[j+1]+w[j];
        // for(pii t:Q[i]) ans[t.se]=sw[t.fi];

        while(!stk[0].empty()&&a[stk[0].top()]<=a[i]){
            upda(all,stk[0][stk[0].size()-1]+1,stk[0].top(),a[i]-a[stk[0].top()]);
            stk[0].pop();
        }
        stk[0].ep(i);upda(all,i,i,a[i]);
        while(!stk[1].empty()&&b[stk[1].top()]<=b[i]){
            updb(all,stk[1][stk[1].size()-1]+1,stk[1].top(),b[i]-b[stk[1].top()]);
            stk[1].pop();
        }
        stk[1].ep(i);updb(all,i,i,b[i]);
        pthis(all,1,0,0,0);
        // for(int j=1;j<=i;j++)   printf("%llu ",query(all,j,j));puts("");
        for(pii t:Q[i]) ans[t.se]=query(all,t.fi,i);
    }
    for(int i=1;i<=q;i++)   printf("%llu\n",ans[i]);
}