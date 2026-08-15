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
const int maxn=2e5+10,inf=1e9;
bool mem1;
int n,m,q,H,W;
struct point{int x,y,id;}a[maxn],b[maxn],Q[maxn];
inline int dis(point x,point y){return abs(x.x-y.x)+abs(x.y-y.y);}
int mn[maxn];
bool ans[maxn];
struct SET{
    priority_queue<pii,vector<pii>,greater<pii>> q1,q2;
    inline void clear(){while(!q1.empty())q1.pop();while(!q2.empty())q2.pop();}
    inline void ep(pii x){q1.ep(x);}
    inline void erase(pii x){q2.ep(x);}
    inline pii top(){while(!q2.empty()&&q1.top()==q2.top())q1.pop(),q2.pop();return q1.top();}
    inline void pop(){q1.pop();}
    inline bool empty(){return q1.size()==q2.size();}
};
struct BIT{
    int len,tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=len){gmn(tr[x],s);x+=lowbit(x);}}
    inline int que(int x){int res=inf;while(x){gmn(res,tr[x]);x^=lowbit(x);}return res;}
    void clear(){fill(tr,tr+len+1,inf);}
}T;
struct BIT2{
    int len,tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x){gmn(tr[x],s);x^=lowbit(x);}}
    inline int que(int x){int res=inf;while(x<=len){gmn(res,tr[x]);x+=lowbit(x);}return res;}
    void clear(){fill(tr,tr+len+1,inf);}
}T2;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,W
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2][2],pos[maxn];
    SET st1[maxn],st2[maxn];
    inline void pu(int p){tr[p][0]=min(tr[ls][0],tr[rs][0]);tr[p][1]=min(tr[ls][1],tr[rs][1]);}
    void build(setpos){tr[p][0]=tr[p][1]=inf;if(l==r)return st1[l].clear(),st2[l].clear(),pos[l]=p,void();setmid;build(lson);build(rson);pu(p);}
    int query(setpos,int pl,int pr,bool o){if(l>=pl&&r<=pr)return tr[p][o];setmid,res=inf;if(pl<=mid)res=query(lson,pl,pr,o);if(pr>mid)gmn(res,query(rson,pl,pr,o));return res;}
    inline void upd(int x,int s1,int s2,int id){
        st1[x].ep(pii(s1,id));st2[x].ep(pii(s2,id));
        int p=pos[x];
        gmn(tr[p][0],s1);gmn(tr[p][1],s2);
        while(p>>=1)pu(p);
    }
    void binary(setpos,int pl,int pr,bool o,int s){
        if(tr[p][o]>=s) return;
        if(l==r){
            if(!o){
                while(!st1[l].empty()&&st1[l].top().fi<s){
                    auto [w,x]=st1[l].top();st1[l].pop();
                    ans[x]=true;st2[l].erase(pii(w+l+l,x));
                }
                tr[p][0]=st1[l].empty()?inf:st1[l].top().fi;
            }
            else{
                while(!st2[l].empty()&&st2[l].top().fi<s){
                    auto [w,x]=st2[l].top();st2[l].pop();
                    ans[x]=true;st1[l].erase(pii(w-l-l,x));
                }
                tr[p][1]=st2[l].empty()?inf:st2[l].top().fi;
            }
            return;
        }
        setmid;
        if(l>=pl&&r<=pr){
            if(tr[ls][o]<s) binary(lson,pl,pr,o,s);
            if(tr[rs][o]<s) binary(rson,pl,pr,o,s);
            return pu(p);
        }
        if(pl<=mid&&tr[ls][o]<s)binary(lson,pl,pr,o,s);
        if(pr>mid&&tr[rs][o]<s)binary(rson,pl,pr,o,s);
        pu(p);
    }
}
using namespace SegmentTree;
void data(){
    const int V=2e5;
    auto rd=[&](){return 1ll*rand()*rand();};
    int T=1;printf("%d\n",T);
    while(T--){
        n=m=q=2e5;
        puts("200000 200000");
        printf("%d\n",n);for(int i=1;i<=n;i++)printf("%d %d\n",rd()%V+1,rd()%V+1);
        printf("%d\n",m);for(int i=1;i<=n;i++)printf("%d %d\n",rd()%V+1,rd()%V+1);
        printf("%d\n",q);for(int i=1;i<=n;i++)printf("%d %d\n",rd()%V+1,rd()%V+1);
    }
    exit(0);
}
bool mem2;
void matt(int _cases){
    // data();
    scanf("%d%d%d",&H,&W,&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,[&](point x,point y){return pii(x.x,x.y)<pii(y.x,y.y);});
    scanf("%d",&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&b[i].x,&b[i].y);
    sort(b+1,b+m+1,[&](point x,point y){return pii(x.x,x.y)<pii(y.x,y.y);});
    T.len=T2.len=W;T.clear();T2.clear();
    fill(mn+1,mn+n+1,inf);
    for(int i=1,j=0;i<=n;i++){
        while(j<m&&b[j+1].x<=a[i].x)    j++,T.add(b[j].y,-b[j].x-b[j].y),T2.add(b[j].y,-b[j].x+b[j].y);
        gmn(mn[i],a[i].x+a[i].y+T.que(a[i].y));
        gmn(mn[i],a[i].x-a[i].y+T2.que(a[i].y));
    }
    T.clear();T2.clear();
    for(int i=n,j=m+1;i;i--){
        while(j>1&&b[j-1].x>=a[i].x)    j--,T.add(b[j].y,b[j].x-b[j].y),T2.add(b[j].y,b[j].x+b[j].y);
        gmn(mn[i],-a[i].x+a[i].y+T.que(a[i].y));
        gmn(mn[i],-a[i].x-a[i].y+T2.que(a[i].y));
    }
    scanf("%d",&q);
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].x,&Q[i].y),Q[i].id=i,ans[i]=0;
    sort(Q+1,Q+q+1,[&](point x,point y){return pii(x.x,x.y)<pii(y.x,y.y);});
    build(all);
    for(int i=1,j=0;i<=n;i++){
        while(j<q&&Q[j+1].x<=a[i].x)    j++,upd(Q[j].y,-Q[j].x-Q[j].y,-Q[j].x+Q[j].y,Q[j].id);
        if(query(all,1,a[i].y,0)<mn[i]-a[i].x-a[i].y)   binary(all,1,a[i].y,0,mn[i]-a[i].x-a[i].y);
        if(query(all,a[i].y,W,1)<mn[i]-a[i].x+a[i].y)   binary(all,a[i].y,W,1,mn[i]-a[i].x+a[i].y);
    }
    build(all);
    for(int i=n,j=q+1;i;i--){
        while(j>1&&Q[j-1].x>=a[i].x)    j--,upd(Q[j].y,Q[j].x-Q[j].y,Q[j].x+Q[j].y,Q[j].id);
        if(query(all,1,a[i].y,0)<mn[i]+a[i].x-a[i].y)   binary(all,1,a[i].y,0,mn[i]+a[i].x-a[i].y);
        if(query(all,a[i].y,W,1)<mn[i]+a[i].x+a[i].y)   binary(all,a[i].y,W,1,mn[i]+a[i].x+a[i].y);
    }
    for(int i=1;i<=q;i++)   puts(ans[i]?"Yes":"No");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);freopen("escape.in","r",stdin);freopen("escape.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}