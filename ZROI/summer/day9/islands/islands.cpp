#include<bits/stdc++.h>
#include "islands.h"
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
const int maxn=300;
int len,mxd,n,cnt;
vector<int> now,nx,U,V,son[maxn];
int dep[maxn],f[maxn];
inline vector<int> mrg(vector<int> x,vector<int> y){for(int i:y)x.eb(i);return x;}
int Q(vector<int> qq){cnt++;return query(qq);}
void dvd(vector<int> v){
    if(v.empty())   return;
    if(v.size()==1){
        if(query(mrg(v,now))>len)nx.eb(v[0]);
        return;
    }
    vector<int> vl,vr;
    int mid=v.size()/2;
    for(int i=0;i<mid;i++)vl.eb(v[i]);
    for(int i=mid;i<v.size();i++)vr.eb(v[i]);
    if(Q(mrg(vl,now))==len) return dvd(vr);
    if(Q(mrg(vr,now))==len) return dvd(vl);
    dvd(vl);dvd(vr);
}
void find_len(){
    len=0;
    for(int i=int(now.size())-1;~i;i--){
        int u=now[i];
        f[u]=dep[u];
        for(int t:son[u]){
            gmx(len,f[u]+f[t]-(dep[u]<<1)+1);
            gmx(f[u],f[t]);
        }
    }
}
void data(){
    int T=10;
    while(T--){
        puts("256 3000");
        for(int i=2;i<=256;i++)printf("%d %d\n",i-1,i);
    }
    exit(0);
}
void solve(int N, int L) {
        cnt=0;
    n=N;
    now.clear();nx.clear();U.clear();V.clear();
    for(int i=1;i<=n;i++)son[i].clear();
    mems(dep,0);
    int rt=rand()%n+1;now.eb(rt);dep[rt]=len=mxd=1;
    while(now.size()^n){
        vector<int> lst;for(int i=1;i<=n;i++)if(!dep[i])lst.eb(i);
        random_shuffle(lst.begin(),lst.end());
        nx.clear();dvd(lst);
        vector<int> vec;vec.clear();
        for(int i=1;i<=n;i++)if(dep[i]){
            if(dep[i]==mxd) vec.eb(i);
        }
        mxd++;
        for(int i:nx)   dep[i]=mxd;
        if(vec.size()==1){
            for(int i:nx)now.eb(i),U.eb(vec[0]),V.eb(i),son[vec[0]].eb(i);
            find_len();
            debug("cnt = %d\n",cnt);
            continue;
        }
        for(int i:nx){
            int l=0,r=vec.size()-1,p=-1;
            while(l^r){
                int mid=(l+r)>>1;
                vector<int> tmp;tmp.clear();
                for(int j=l;j<=mid;j++)tmp.eb(vec[j]);
                tmp.eb(i);
                if(Q(tmp)==2)  r=mid,p=mid;
                else    l=mid+1;
            }
            p=l;
            U.eb(vec[p]);V.eb(i);
            son[vec[p]].eb(i);
        }
        for(int i:nx)  now.eb(i);
        find_len();
    }
    debug("cnt = %d\n",cnt);
    // debug("mxd = %d\n",mxd);
    answer(U,V);
}