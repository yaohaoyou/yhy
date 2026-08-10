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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=3e5+10;
int n,m,len;
char s[maxn],t[maxn],a[maxn];
int buc[maxn],rk[maxn],sa[maxn],y[maxn],ht[maxn];
int pr[maxn],nx[maxn];
void SA(){
    int V='z';
    for(int i=1;i<=len;i++) buc[rk[i]=a[i]]++;
    for(int i=1;i<=V;i++)   buc[i]+=buc[i-1];
    for(int i=1;i<=len;i++) sa[buc[rk[i]]--]=i;
    for(int w=1;w<=len;w++){
        int p=0;
        for(int i=len-w+1;i<=len;i++)   y[++p]=i;
        for(int i=1;i<=len;i++)if(sa[i]>w)y[++p]=sa[i]-w;
        mems(buc,0);
        for(int i=1;i<=len;i++)   buc[rk[i]]++;
        for(int i=1;i<=V;i++)   buc[i]+=buc[i-1];
        for(int i=len;i;i--)    sa[buc[rk[y[i]]]--]=y[i];
        memc(y,rk);
        rk[sa[1]]=V=1;
        for(int i=2;i<=len;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+w]==y[sa[i-1]+w])  rk[sa[i]]=V;
            else    rk[sa[i]]=++V;
        }
        if(V==len)    return;
    }
}
void build_ht(){
    int k=0;a[len+1]='?';
    for(int i=1;i<=len;i++){
        if(k)   k--;
        while(a[i+k]==a[sa[rk[i]-1]+k]) k++;
        ht[rk[i]]=k;
    }
}
struct st{
    int st[20][maxn],Log[maxn];
    void build(){
        for(int i=2;i<=len;i++)   Log[i]=Log[i/2]+1;
        memc(st[0],ht);
        for(int i=1;i<=Log[len];i++)
            for(int j=1;j+(1<<i)-1<=len;j++)    st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    int query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
bool kil[maxn];
priority_queue<piii> q;
inline void era(int x){int pre=pr[x],nxt=nx[x];pr[nxt]=pre;nx[pre]=nxt;}
inline bool in(int x){return x<=n;}
void data(){
    n=20;m=rand()%n+1;
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)   printf("%c",'a'+rand()%26);puts("");
    for(int i=1;i<=n;i++)   printf("%c",'a'+rand()%26);puts("");
    exit(0);
}
int main(){
    // data();
    scanf("%d%d",&n,&m);
    scanf("%s%s",s+1,t+1);
    // printf("%d,",m);
    // for(int i=1;i<=n;i++)   printf("%c",s[i]);puts("");
    for(int i=1;i<=n;i++)   a[++len]=s[i];
    a[++len]='#'; 
    for(int i=1;i<=n;i++)   a[++len]=t[i];
    SA();build_ht();st.build();
    // for(int i=1;i<=len;i++) printf("%c",a[i]);puts("");
    // for(int i=1;i<=len;i++) printf("%d ",sa[i]);puts("");
    for(int i=2,lst=0;i<=len;i++){
        if(sa[i]<=n-m+1||(sa[i]>n+1&&sa[i]<=len-m+1)){
            nx[lst]=i,pr[i]=lst;
            lst=i;
        }
    }
    for(int i=n-m+2;i<=n+1;i++) kil[rk[i]]=true;
    for(int i=len-m+2;i<=len;i++)   kil[rk[i]]=true;
    for(int i=nx[0];i;i=nx[i]){
        // printf("%d ",sa[i]);
        if(nx[i]&&in(sa[i])^in(sa[nx[i]]))q.ep(st.query(i+1,nx[i]),pii(i,nx[i]));
    }
    ll ans=0;int tim=0;
    while(!q.empty()){
        auto [w,t]=q.top();int i=t.fi,j=t.se;q.pop();
        // assert(i^325&&j^325);
        // if(i==18||j==18)  printf("! %d %d %d %d\n",i,j,kil[i],kil[j]);
        // if(i==325)  printf("%d %d\n",x,y);
        // printf("%d %d %d\n",w,sa[i],sa[j]);
        int x=i,y=j;
        if(!kil[i]&&!kil[j]){
            ans+=max(0,m-w);
            tim++;
            // printf("lcp(%d,%d) = %d\n",sa[i],sa[j],w);
            era(i);era(j);
            kil[i]=kil[j]=true;
        }
        while(x&&kil[x])    x=pr[x];
        while(y&&kil[y])    y=nx[y];
        if(!x||!y)  continue;
        // if(x==324||y==324)  printf("%d %d\n",x,y);
        if(in(sa[x])^in(sa[y])) q.ep(st.query(x+1,y),pii(x,y));
    }
    // assert(tim==n-m+1);
    // for(int i=1;i<=len;i++)if(!kil[i])printf("%d ",i);puts("");
    // for(int i=nx[0];i;i=nx[i])printf("%d ",i);puts("");
    // printf("%d\n",tim);
    printf("%lld\n",ans);
}