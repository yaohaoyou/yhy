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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5e5+10,inf=1e9;
int n,q;
pii a[maxn];int s[maxn];
int b[maxn];
vector<piii> Q[maxn];
int ans[maxn];
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    inline void pt(int p,int s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);setmid;pd(p);if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    int Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=inf;pd(p);if(pl<=mid)res=Q(lson,pl,pr);if(pr>mid)gmn(res,Q(rson,pl,pr));return res;}
    void build(setpos,bool o){tr[p]=tag[p]=0;if(l==r)return tr[p]=(l&1)==o?b[l]:inf,void();setmid;build(lson,o);build(rson,o);pu(p);}
    inline int qry(int x){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}return tr[p];}
}T[2];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].fi),a[i].se=i;
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);a[i].fi-=x;}
    for(int i=1;i<=q;i++){
        int l,r,k;scanf("%d%d%d",&l,&r,&k);
        if(k==l)    ans[i]=1;
        else if(k==r)   ans[i]=2;
        else    Q[k].eb(pii(l,r),i);
    }
    // for(int i=1;i<=n;i++)   printf("%d ",a[i].fi);puts("");
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)   b[i]=(i>>1);
    T[0].build(all,0);T[1].build(all,1);
    for(int i=1;i<=n;i++){
        int j=i;
        while(j<=n&&a[j].fi==a[i].fi){
            int k=a[j].se;
            for(auto [sg,id]:Q[k]){
                int l=sg.fi,r=sg.se;
                int q1=T[l&1].Q(all,k,r),q2=T[l&1].Q(all,l+2,r),q3=T[l&1].qry(l);
                // printf("%d : %d %d %d\n",id,q1,q2,q3);
                ans[id]=(q1==q2&&q1<=q3);
            }
            j++;
        }
        j--;
        for(int k=i;k<=j;k++){
            int x=a[k].se;
            T[x&1].upd(all,x,n,-1);
            if(x^n)T[(x+1)&1].upd(all,x+1,n,-1);
        }
        i=j;
    }
    // for(int i=1;i<=q;i++)   puts(ans[i]==1?"(":ans[i]==2?")":"x");
    reverse(a+1,a+n+1);
    for(int i=1;i<=n;i++)   b[i]=(n-i+1>>1);
    T[0].build(all,0);T[1].build(all,1);
    for(int i=1;i<=n;i++){
        int j=i;
        while(j<=n&&a[j].fi==a[i].fi){
            int k=a[j].se;
            for(auto [sg,id]:Q[k]){
                int l=sg.fi,r=sg.se;
                int q1=T[r&1].Q(all,l,k),q2=T[r&1].Q(all,l,r-2),q3=T[r&1].qry(r);
                if(q1==q2&&q1<=q3)  ans[id]=2;
            }
            j++;
        }
        j--;
        for(int k=i;k<=j;k++){
            int x=a[k].se;
            T[x&1].upd(all,1,x,-1);
            if(x^1)T[(x-1)&1].upd(all,1,x-1,-1);
        }
        i=j;
    }
    for(int i=1;i<=q;i++)   puts(ans[i]==1?"(":ans[i]==2?")":"x");
}