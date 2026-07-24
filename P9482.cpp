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
using namespace std;
const int maxn=2e5+10;
int n,m,q;
char a[maxn],s[maxn];
int buc[maxn],sa[maxn],rk[maxn],y[maxn];
int p[maxn],ans[maxn];
struct ques{int x,r,id;}Q[maxn];
vector<int> vq[maxn];
vector<pii> v[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=m){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return que(r)-que(l-1);}
    void clear(){mems(tr,0);}
}T[2];
void build_SA(int len){
    mems(buc,0);
    int m=511;
    for(int i=1;i<=len;i++) buc[rk[i]=s[i]]++;
    for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
    for(int i=1;i<=len;i++) sa[buc[s[i]]--]=i;
    for(int w=1;w<=len;w<<=1){
        int p=0;
        for(int i=len-w+1;i<=len;i++)   y[++p]=i;
        for(int i=1;i<=len;i++)if(sa[i]>w)  y[++p]=sa[i]-w;
        mems(buc,0);
        for(int i=1;i<=len;i++) buc[rk[i]]++;
        for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
        for(int i=len;i;i--)    sa[buc[rk[y[i]]]--]=y[i];
        memc(y,rk);
        rk[sa[1]]=m=1;
        for(int i=2;i<=len;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+w]==y[sa[i-1]+w])  rk[sa[i]]=m;
            else    rk[sa[i]]=++m;
        }
        if(m==len)  break;
    }
}
void matt(int _cases){
    T[0].clear();T[1].clear();m=0;
    scanf("%d%d%s",&n,&q,a+1);
    for(int i=1;i<=n;i++)   s[++m]=a[i];s[++m]='a'-1;
    for(int i=n;i;i--)  s[++m]=a[i];s[++m]='a'-2;
    build_SA(m);
    // for(int i=1;i<=m;i++)   putchar(s[i]);puts("");
    // for(int i=1;i<=m;i++)   printf("%d ",rk[i]);puts("");
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].x,&Q[i].r);
        Q[i].id=i;vq[Q[i].x].eb(i);
    }
    for(int i=m;i;i--){
        int x=sa[i];
        for(int j:vq[x]){
            int l=m-Q[j].x-Q[j].r*2+1,r=m-Q[j].x-1;
            ans[j]=T[l&1].query(l,r);
        }
        T[x&1].add(x,1);
        vq[x].clear();
    }
    m=0;
    s[++m]='a'-2;
    for(int i=1;i<=n;i++)   s[++m]='|',s[++m]=a[i];
    s[++m]='|';s[++m]='a'-1;
    for(int i=1,mid=0,r=0;i<=m;i++){
        p[i]=i>r?1:min(r-i+1,p[(mid<<1)-i]);
        while(s[i+p[i]]==s[i-p[i]]) p[i]++;
        if(i+p[i]-1>r)  r=i+p[i]-1,mid=i;
        if(!(i&1)&&(s[i+p[i]]<s[i-p[i]])){
            // 1<=(l=i/2-x)<=r && x>=i/2-p[i]/2
            // x+r>=i/2 && i/2-p[i]/2<=x<=i/2-1
            int l=i/2-p[i]/2,r=i/2-1;
            if(l<=r)    v[i/2].eb(l,r);
        }
    }
    for(int i=1;i<=q;i++)   v[Q[i].x+Q[i].r].eb(i,0);
    T[0].clear();
    for(int i=1;i<=n;i++){
        for(auto [l,r]:v[i]){
            if(r)   T[0].add(l,1),T[0].add(r+1,-1);
            else    ans[l]-=T[0].que(Q[l].x);
        }
        v[i].clear();
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}
int main(){int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}