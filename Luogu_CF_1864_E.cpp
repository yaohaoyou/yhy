#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10,maxp=maxn*32,mod=998244353;
int n;
int a[maxn],b[maxn];
map<int,int> buc;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;};return res;}
}
using namespace FastMod;
inline int calc(int x,int y){
    int res=0;
    for(int i=30;~i;i--){
        bool o1=x&(1<<i),o2=y&(1<<i);
        if(!o1&&!o2)    continue;
        res++;
        if(o1<o2)   return res+!(res&1);
        if(o1>o2)   return res+(res&1);
    }
    return res+1;
}
struct Trie{
    int tot;
    int nex[maxp][2],cnt[maxp];
    inline void insert(int x,int s){
        int p=0;
        for(int i=30;~i;i--){
            bool o=x&(1<<i);
            if(!nex[p][o])   nex[p][o]=++tot;
            p=nex[p][o];
            cnt[p]+=s;
        }
        // printf("tot = %d\n",tot);
    }
    inline int query(int x){
        // printf("x = %d\n",x);
        int p=0,res=0;bool fl=0;
        for(int i=30;~i;i--){
            bool o=x&(1<<i);
            // fl|=o;
            // if(fl){
                res+=cnt[nex[p][o^1]];
                if(o)   res+=cnt[nex[p][o]];
                // printf("%d : %d %d\n",i,cnt[nex[p][o]],cnt[nex[p][o^1]]);
            // }
            p=nex[p][o];
        }
        return res;
    }
    inline void init(){for(int i=0;i<=tot;i++)nex[i][0]=nex[i][1]=cnt[i]=0;tot=0;}
}tr;
int ans;
void solve(){
    buc.clear();tr.init();
    ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);b[i]=a[i];buc[b[i]]++;}
    for(int i=1;i<=n;i++) madd(ans,calc(a[i],a[i]));
    sort(b+1,b+n+1);int m=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=m;i++)   tr.insert(b[i],buc[b[i]]);
    int sum=n;
    for(int i=1;i<=m;i++){
        int res=0;
        tr.insert(b[i],-buc[b[i]]);
        res=tr.query(b[i]);
        madd(res,res);
        madd(ans,immul(res,buc[b[i]]));
        sum-=buc[b[i]];
        madd(ans,immul(sum,buc[b[i]]));
    }
    for(int i=1;i<=m;i++){
        int c=immul(buc[b[i]],buc[b[i]]-1);
        mmul(c,calc(b[i],b[i]));
        madd(ans,c);
    }
    mmul(ans,qpow(immul(n,n),mod-2));
    printf("%d\n",ans);
}
int main(){
    int T;scanf("%d",&T);while(T--)solve();
}