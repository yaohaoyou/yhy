//  P5043 【模板】树同构（[BJOI2015]树的同构）
#include<bits/stdc++.h>
#define ull unsigned long long
#define puu pair<ull,ull>
using namespace std;
const int maxn=60;
int n,T;
map<puu,int> mp;
struct Graph{
    int cnt=0,head[maxn];
    struct edge{
        int nxt,to;
    }e[maxn<<1];
    void add(int u,int v){
        e[++cnt]={head[u],v};
        head[u]=cnt;
    }
}G[maxn];
int maxx[maxn],siz[maxn];
int wc[3];
void findWC(int u,int fa,int id){
    siz[u]=1;
    maxx[u]=0;
    for(int i=G[id].head[u];i;i=G[id].e[i].nxt){
        int t=G[id].e[i].to;
        if(t==fa)   continue;
        findWC(t,u,id);
        siz[u]+=siz[t];
        maxx[u]=max(maxx[u],siz[t]);
    }
    // maxx[u]=min(siz[u],n-siz[u]);
    // if(maxx[u]>maxx[wc[1]]){wc[1]=u;wc[2]=0;}
    // else if(maxx[u]==maxx[wc[1]]){wc[2]=u;}
    maxx[u]=max(maxx[u],n-siz[u]);
    if(maxx[u]<=n/2){
        if(!wc[1])  wc[1]=u;
        else    wc[2]=u;
    }
}
int base;
ull Hash(ull x){x^=(x<<base);x^=(x<<6);x^=(x>>10);x^=(x<<3);return x;}
ull dfshash(int u,int fa,int id){
    ull res=1;
    for(int i=G[id].head[u];i;i=G[id].e[i].nxt){
        int t=G[id].e[i].to;
        if(t==fa)   continue;
        res+=Hash(dfshash(t,u,id));
    }
    return res;
}
int main(){
    srand(time(0)+clock()*114ll+rand()*rand()%124098);
    base=rand()%15+1;
    // printf("%d\n",base);
    // cout<<Hash(444)<<"\n\n";
    scanf("%d",&T);
    for(int t=1;t<=T;t++){
        wc[1]=wc[2]=0;
        scanf("%d",&n);
        for(int i=1,v;i<=n;i++){
            scanf("%d",&v);if(!v)   continue;
            G[t].add(i,v);G[t].add(v,i);
        }
        findWC(1,0,t);
        // printf("%d %d\n",wc[1],wc[2]);
        ull now1=dfshash(wc[1],0,t),now2=0;
        // printf("%llu\n",now);
        if(maxx[wc[2]]==maxx[wc[1]])    now2=dfshash(wc[2],0,t);
        if(now2==0) now2=now1;
        if(now1<now2)   swap(now1,now2);
        if(!mp[puu(now1,now2)])    mp[puu(now1,now2)]=t;
        printf("%d\n",mp[puu(now1,now2)]);
    }
}