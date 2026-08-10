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
const int maxn=3e5+10,maxv=maxn*5;
bool mem1;
int n,m,t;
int b[maxv];
bool liv[maxn];
struct node{int x,l,r,a,id;}a[maxn];
vector<int> al;
unordered_map<int,vector<int>> v;
ll ans[maxn];
priority_queue<pii,vector<pii>,greater<pii>> q;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<int> vec[maxv<<2];int ps[maxv<<2];
    struct tree{
        int s,col,mn;
        tree operator+(tree y){
            if(!s)  return y;
            if(!y.s)    return *this;
            tree res;
            if(s==1&&y.s==1&&col==y.col)    return {s,col,min(mn,y.mn)};
            return (tree){2,0,0};
        }
    };
    tree tr[maxv<<2];
    inline void chk(int p){while(ps[p]<vec[p].size()&&!liv[vec[p][ps[p]]])ps[p]++;while(ps[p]<vec[p].size()&&!liv[vec[p].back()])vec[p].pop_back();}
    inline void init(int p){
        if(ps[p]==vec[p].size())  tr[p]={0,0,0};
        else if(a[vec[p][ps[p]]].a==a[vec[p].back()].a)    tr[p]={1,a[vec[p][ps[p]]].a,a[vec[p][ps[p]]].x};
        else    tr[p]={2,0,0};
    }
    inline void slv(int p,int l,ll T){
        if(tr[p].s==1&&tr[p].mn>=l){
            int c=tr[p].col;
            while(!v[c].empty()&&a[v[c].back()].x>=l){
                int x=v[c].back();v[c].pop_back();
                if(~ans[a[x].id]) continue;
                ans[a[x].id]=(T-c+t-1)/t*t+c;
                // printf("1 %d %d\n",a[x].id,(T-a[x].a+t-1)/t*t+a[x].a);
                q.ep(ans[a[x].id],x);
            }
        }
        if(tr[p].s==0){
            while(!al.empty()&&a[al.back()].x>=l){
                int x=al.back();al.pop_back();
                if(~ans[a[x].id]) continue;
                ans[a[x].id]=(T-a[x].a+t-1)/t*t+a[x].a;
                // printf("0 %d %d %d\n",a[x].id,T,(T-a[x].a+t-1)/t*t+a[x].a);
                q.ep(ans[a[x].id],x);
            }
        }
        // printf("ans = %d\n",ans[3]);
    }
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return vec[p].eb(s),void();setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);}
    void build(setpos){
        init(p);
        if(p>1) tr[p]=tr[p]+tr[p>>1];
        // if(l==r)    printf("[%d,%d] : %d %d\n",b[l],b[r],tr[p].s,tr[p].col);
        if(l==r)return slv(p,l,0);
        setmid;build(lson);build(rson);
    }
    void era(setpos,int pl,int pr,ll T){
        if(l>=pl&&r<=pr){
            int bef=tr[p].s;
            chk(p);init(p);if(p>1)tr[p]=tr[p]+tr[p>>1];
            // if(l==r)    printf("%d [%d,%d] : %d %d\n",T,b[l],b[r],tr[p].s,tr[p].col);
            if(l==r)    return slv(p,l,T);
            setmid;
            if(bef^tr[p].s) era(lson,pl,pr,T),era(rson,pl,pr,T);
            return;
        }
        setmid;if(pl<=mid)era(lson,pl,pr,T);if(pr>mid)era(rson,pl,pr,T);
    }
}
using namespace SegmentTree;
bool mem2;
void discrete(){
    for(int i=1;i<=n;i++)   b[++m]=a[i].l,b[++m]=a[i].r,b[++m]=a[i].r+1,b[++m]=a[i].x,b[++m]=a[i].x+1;
    b[++m]=0;
    sort(b+1,b+m+1);m=unique(b+1,b+m+1)-b-1;
    for(int i=1;i<=n;i++)   a[i].l=lower_bound(b+1,b+m+1,a[i].l)-b,a[i].r=lower_bound(b+1,b+m+1,a[i].r)-b,a[i].x=lower_bound(b+1,b+m+1,a[i].x)-b;
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&t);
    for(int i=1;i<=n;i++)   scanf("%d%d%d%d",&a[i].x,&a[i].l,&a[i].r,&a[i].a),a[i].id=i,a[i].x--,a[i].r--;
    discrete();
    sort(a+1,a+n+1,[&](node x,node y){return x.a==y.a?x.x<y.x:x.a<y.a;});
    for(int i=1;i<=n;i++){
        al.eb(i);
        v[a[i].a].eb(i);
    }
    sort(al.begin(),al.end(),[&](int x,int y){return a[x].x<a[y].x;});
    for(auto &i:v)  sort(i.se.begin(),i.se.end(),[&](int x,int y){return a[x].x<a[y].x;});
    for(int i=1;i<=n;i++)   upd(all,a[i].l,a[i].r,i);
    mems(liv,1);mems(ans,-1);
    build(all);
    while(!q.empty()){
        int x=q.top().se;q.pop();
        liv[x]=false;
        era(all,a[x].l,a[x].r,ans[a[x].id]);
    }
    for(int i=1;i<=n;i++)   printf("%lld\n",ans[i]);
}