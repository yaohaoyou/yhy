/*
Author?ForgotMe
????????????? 
*/
#include <bits/stdc++.h>
#include <cstdio>
#include <map>
#include <set>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <cstring>
#include <ctime>
#include <cmath>
#include <assert.h> 
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
#define LL long long
#define pp pair<int,int>
#define mp make_pair 
#define ull unsigned long long
#define ui unsigned int
#define ld long double
namespace IO{
    const int sz=1<<22;
    char a[sz+5],b[sz+5],*p1=a,*p2=a,*t=b,p[105];
    inline char gc(){
    //  return p1==p2?(p2=(p1=a)+fread(a,1,sz,stdin),p1==p2?EOF:*p1++):*p1++;
        return getchar();
    }
    template<class T> void gi(T& x){
        x=0; int f=1;char c=gc();
        if(c=='-')f=-1;
        for(;c<'0'||c>'9';c=gc())if(c=='-')f=-1;
        for(;c>='0'&&c<='9';c=gc())
            x=x*10+(c-'0');
        x=x*f;
    }
    inline void flush(){fwrite(b,1,t-b,stdout),t=b; }
    inline void pc(char x){*t++=x; if(t-b==sz) flush(); }
    template<class T> void pi(T x,char c='\n'){
        if(x<0)pc('-'),x=-x;
        if(x==0) pc('0'); int t=0;
        for(;x;x/=10) p[++t]=x%10+'0';
        for(;t;--t) pc(p[t]); pc(c);
    }
    struct F{~F(){flush();}}f; 
}
using IO::gi;
using IO::pi;
using IO::pc;
const int mod=998244353;
//const int mod=1e9+7;
const int inv2=(mod+1)>>1;
const int Groot=3;
inline int add(int x,int y){
    return x+y>=mod?x+y-mod:x+y;
}
inline int dec(int x,int y){
    return x-y<0?x-y+mod:x-y;
}
inline int mul(int x,int y){
    return 1ll*x*y%mod;
}
inline int qkpow(int a,LL b){
    if(b<0)return 0;
    int ans=1,base=a%mod;
    while(b){
        if(b&1)ans=1ll*ans*base%mod;
        base=1ll*base*base%mod;
        b>>=1;
    }
    return ans;
}
int fac[1000005],inv[1000005];//,Invn[1000005];
inline int binom(int n,int m){
    if(n<m||m<0)return 0;
    return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void init_C(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=1ll*fac[i-1]*i%mod; 
    inv[0]=1;
    inv[n]=qkpow(fac[n],mod-2);
    for(int i=n-1;i>=1;i--)inv[i]=1ll*inv[i+1]*(i+1)%mod;
   // Invn[0]=1;
  //  for(int i=1;i<=n;i++)Invn[i]=1ll*inv[i]*fac[i-1]%mod;
}
#define vi vector<int>
#define ls(p) p<<1
#define rs(p) p<<1|1
#define i128 __int128
#define IT set<int>::iterator
const int sft=(1<<20);
const int INF=2e9;
int n,a[1000005],g[1000005],f[1000005],ch[2][31000005],tag[2][31000005],st[31000005],cnt,rt,top;
bool ful[31000005];
inline int newnode(int full=0){
    int u=top?st[top--]:++cnt;
    ch[0][u]=ch[1][u]=0;
    tag[0][u]=tag[1][u]=0;
    ful[u]=full;
    return u;
}
inline void del(int u){
    if(!u)return;
    if(!ful[u]){
        del(ch[0][u]);
		del(ch[1][u]);
    }
    st[++top]=u;
}
inline int apply(int u,int x,int y){
    if(!u)return 0;
    tag[0][u]|=x;
	tag[1][u]|=y;
    if(tag[0][u]&tag[1][u]){
        del(u);
		return 0;
    }
    return u;
}
inline void pushdown(int u,int d){
    if(ful[u]){
        int l=newnode(1),r=newnode(1);
        ch[0][u]=l;ch[1][u]=r;
        ful[u]=0;
    }
    int w=1<<d,x=tag[0][u],y=tag[1][u];
    if(x&w){
        del(ch[1][u]);
		ch[1][u]=0;
    }
    if(y&w){
        del(ch[0][u]);
		ch[0][u]=0;
    }
    x&=w-1;y&=w-1;
    ch[0][u]=apply(ch[0][u],x,y);
    ch[1][u]=apply(ch[1][u],x,y);
    tag[0][u]=tag[1][u]=0;
}
inline int cover(int u){
    if(!u)return newnode(1);
    if(!ful[u]){
        del(ch[0][u]);
		del(ch[1][u]);
    }
    ch[0][u]=ch[1][u]=0;
    tag[0][u]=tag[1][u]=0;
    ful[u]=1;
    return u;
}
inline void Clear(){
    cnt=rt=top=0;
}
inline void getlimit(int d,int x){
    int w=1<<d;
    rt=apply(rt,x?0:w,x?w:0);
}
inline int ins(int u,int d,int x,int v){
    if(d<0||!(v&((1<<(d+1))-1)))return cover(u);
    if(!u)u=newnode();
    pushdown(u,d);
    int p=x>>d&1,q=v>>d&1;
    ch[p^q][u]=ins(ch[p^q][u],d-1,x,v);
    if(!q)ch[p^1][u]=cover(ch[p^1][u]);
    return u;
}
inline int query(int u,int d,int x){
    if(!u)return INF;
    if(ful[u])return (x&tag[0][u])|((~x)&tag[1][u]);
    if(d<0)return 0;
    pushdown(u,d);
    int v=x>>d&1,ans=query(ch[v][u],d-1,x);
    if(ans!=INF)return ans;
    del(ch[v][u]);ch[v][u]=0;
    ans=query(ch[v^1][u],d-1,x);
    if(ans!=INF)return ans|(1<<d);
    del(ch[v^1][u]);ch[v^1][u]=0;
    return INF;
}
inline void sol(){
	gi(n);
    for(int i=1;i<=n;i++)gi(a[i]);
    g[0]=f[0]=0;
	g[1]=1;
    int m=0,c=0,s=1;
    for(int i=2;i<=n;i++){
        g[i]=g[i-1];
        if(a[i-1]>a[i])s=i; 
        int x=a[i-1]^a[i];
        if(!x)continue;
        int d=31-__builtin_clz(x),w=1<<d;
        if((m&w)&&((c^a[i-1])&w)){
            g[i]++;
			m=c=0; 
        }else{
            m|=w;
			c=(c&~w)|(a[i-1]&w);
        }
    }
    int k=g[n],l=0,r=0;
    while(g[r]<k-1){
        int p=r+1;
        while(p<n&&g[p+1]==g[p])p++;
        Clear();
        for(int i=l+1;i<=p;i++){
            if(i>l+1){
                int x=a[i-1]^a[i];
                if(x){
                    int d=31-__builtin_clz(x);
                    getlimit(d,(a[i-1]>>d)&1);
                }
            }
            if(i<=r+1&&f[i-1]!=INF)rt=ins(rt,29,a[i],f[i-1]);
            if(i>=r+1)f[i]=query(rt,29,a[i]);
        }
        l=r+1;
		r=p;
    }
	for(int i=max(l,s-1);i<=r;i++){
        if(f[i]<=a[i+1]){
            pi(k-1);
			return;
        }
    }
    pi(k);
}
signed main(){
    cin.tie(0)->sync_with_stdio(0);		
    srand(time(0)); 
 //   init_C(1000000);
	int c,t=1;
//	cin>>t; 
	gi(c),gi(t);
    while(t--)sol();
    return 0;
}

/*
*/