#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2.5e5+10,B=500;
int n,m,q;
int now;
int a[maxn],b[maxn],c[maxn],id[maxn],ans[maxn];
pii d[maxn];
struct ques{int l,r,id;}Q[maxn];
int fa[maxn],siz[maxn],lim[maxn],mn[maxn];
struct DSU{
    stack<piii> stk;
    void init(){iota(fa+1,fa+m+1,1);fill(siz+1,siz+m+1,1);mems(lim,0x3f);mems(mn,0x3f);}
    inline int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline int find2(int x){while(fa[x]^x)x=fa[x];return x;}
    inline void merge1(int x,int y){
        x=find(x);y=find(y);
        if(x==y)return;
        if(siz[x]>siz[y])   swap(x,y);
        fa[x]=y;siz[y]+=siz[x];gmn(lim[y],lim[x]);gmn(mn[y],mn[x]);
    }
    inline void merge2(int x,int y){
        x=find2(x);y=find2(y);
        if(x==y)return;
        if(siz[x]>siz[y])   swap(x,y);
        stk.ep(x,pii(lim[y],mn[y]));
        fa[x]=y;siz[y]+=siz[x];gmn(lim[y],lim[x]);gmn(mn[y],mn[x]);
    }
    inline bool chk(int x){return mn[x]>lim[x];}
    inline int operator[](int x){return find2(x);}
    inline void back(){
        while(!stk.empty()){
            int x=stk.top().fi;
            if(x>0){
                int y=fa[x];
                fa[x]=x;siz[y]-=siz[x];lim[y]=stk.top().se.fi;mn[y]=stk.top().se.se;
            }
            else    lim[-x]=stk.top().se.fi,mn[-x]=stk.top().se.se;
            stk.pop();
        }
    }
}U;
int vis[maxn];
inline void add(int x){
    int p=U.find(b[x]);
    now-=U.chk(p);
    gmn(lim[p],a[x]);gmn(mn[p],c[b[x]]);
    if(!vis[b[x]]){
        if(vis[b[x]-1]&&c[b[x]]==c[b[x]-1]+1){
            int pp=U.find(b[x]-1);
            now-=U.chk(pp),U.merge1(p,pp);
        }
        if(vis[b[x]+1]&&c[b[x]+1]==c[b[x]]+1){
            int pp=U.find(b[x]+1);
            now-=U.chk(pp),U.merge1(p,pp);
        }
    }
    vis[b[x]]++;
    now+=U.chk(U.find(p));
}
inline void add2(int x){
    int p=U[b[x]];
    now-=U.chk(p);
    U.stk.ep(-p,pii(lim[p],mn[p]));
    gmn(lim[p],a[x]);gmn(mn[p],c[b[x]]);
    if(!vis[b[x]]){
        if(vis[b[x]-1]&&c[b[x]]==c[b[x]-1]+1){
            int pp=U[b[x]-1];
            now-=U.chk(pp),U.merge2(p,pp);
        }
        if(vis[b[x]+1]&&c[b[x]+1]==c[b[x]]+1){
            int pp=U[b[x]+1];
            now-=U.chk(pp),U.merge2(p,pp);
        }
    }
    vis[b[x]]++;
    now+=U.chk(U[p]);
}
void discrete(){
    memc(c,b);sort(c+1,c+n+1);
    m=unique(c+1,c+n+1)-c-1;
    for(int i=1;i<=n;i++)   b[i]=lower_bound(c+1,c+m+1,b[i])-c;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    discrete();
    for(int i=1;i<=q;i++)   scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].l++,Q[i].r++,Q[i].id=i;
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    sort(Q+1,Q+q+1,[&](ques x,ques y){return id[x.l]==id[y.l]?x.r<y.r:x.l<y.l;});
    int lst=0;
    for(int _=1,l,r;_<=q;_++){
        auto [ql,qr,qid]=Q[_];
        if(qr-ql+1<=B){
            int len=0;
            for(int i=ql;i<=qr;i++)d[++len]=pii(c[b[i]],a[i]);
            sort(d+1,d+len+1);
            bool flag=true;
            for(int i=1;i<=len;i++){
                int j=i+1,mn=d[i].se;
                while(j<=len&&d[j].fi-d[j-1].fi<=1)   gmn(mn,d[j++].se);
                if(mn<d[i].fi){flag=false;break;}
                i=j-1;
            }
            ans[qid]=flag;
            continue;
        }
        if(id[ql]^lst){
            l=min(n,id[ql]*B);r=l-1;
            now=0;U.init();lst=id[ql];mems(vis,0);
        }
        while(r<qr) add(++r);
        if(l>ql){
            int L=l,nw=now;
            while(l>ql) add2(--l);
            ans[qid]=!now;
            for(int i=l;i<L;i++)    vis[b[i]]--;
            now=nw;U.back();l=L;
        }
        else    ans[qid]=!now;
    }
    for(int i=1;i<=q;i++)   printf("%d ",ans[i]);
}