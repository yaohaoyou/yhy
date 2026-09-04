#include<bits/stdc++.h>
#include<tr2/dynamic_bitset>
#define db double
#define ll long long
#define ep emplace
#define eb emplace_back
#define ef emplace_front
#define pii pair<int,int>
#define piiii pair<pii,pii>
#define fi first
#define se second
#define bsn tr2::dynamic_bitset<>
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
bool mem1;
namespace MATT{
	const int maxn=1e5+10,B=350,block=maxn/B+10;
	int n,m,q;
	int a[maxn],b[maxn];
	int pa[maxn],pb[maxn];
	namespace Graph{
	    const int maxm=2e5+10;
	    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
	    int cnt=1;
	    int head[maxn],deg[maxn];
	    struct edge{int nxt,to;}e[maxm];
	    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
	    inline void adde(int u,int v){add(u,v);add(v,u);}
	    void rebuild(){mems(head,0);cnt=1;}
	}
	using namespace Graph;
	bsn to[maxn],S;
	int id[maxn],bl[block],br[block];
	bsn bsa[block],bsb[block];
	queue<int> Q;
	void bfs(){
	    for(int i=1;i<=n;i++)if(!deg[i])Q.ep(i);
	    while(!Q.empty()){
	        int u=Q.front();Q.pop();
	        go(u,i){
	            int t=e[i].to;
	            to[t]|=to[u];
	            if(!(--deg[t])) Q.ep(t);
	        }
	    }
	}
	void init(){
		for(int i=1;i<=n;i++)	id[i]=(i-1)/B+1;
		for(int i=1;i<=id[n];i++)	bsa[i].resize(n+1),bsb[i].resize(n+1),bsa[i].reset(),bsb[i].reset();
		for(int i=1;i<=id[n];i++)	bl[i]=br[i-1]+1,br[i]=min(i*B,n);
		for(int i=1;i<=n;i++)	bsa[id[a[i]]].set(i),bsb[id[b[i]]].set(i);
		for(int i=id[n]-1;i;i--)	bsa[i]|=bsa[i+1],bsb[i]|=bsb[i+1];
	}
	inline void insA(int x){for(int i=id[a[x]];i;i--)bsa[i].set(x);}
	inline void insB(int x){for(int i=id[b[x]];i;i--)bsb[i].set(x);}
	inline void eraA(int x){for(int i=id[a[x]];i;i--)bsa[i].reset(x);}
	inline void eraB(int x){for(int i=id[b[x]];i;i--)bsb[i].reset(x);}
	inline void query(int l,int r){
		int idl=id[l],idr=id[r];
		bsn tmp(n+1);tmp.reset();
		if(idl==idr){
			for(int i=l;i<=r;i++)	tmp.set(pa[i]);
			S&=tmp;
			return;
		}
		while(id[l]==idl)	tmp.set(pa[l++]);
		while(id[r]==idr)	tmp.set(pa[r--]);
		tmp|=(bsa[idl+1]^bsa[idr]);
		S&=tmp;
	}
	void matt(){
	    rebuild();
	    scanf("%d%d%d",&n,&m,&q);
        for(int i=1;i<=n;i++)   to[i].resize(n+1);
	    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);add(v,u);}
	    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),pa[a[i]]=i;
	    for(int i=1;i<=n;i++)   scanf("%d",&b[i]),pb[b[i]]=i;
	    init();
	    for(int i=1;i<=n;i++)   to[i].reset(),to[i].set(i);
	    bfs();
		while(q--){
			int op,x,y,l,r;scanf("%d%d%d",&op,&x,&l);
			if(op==1){y=l;eraA(x);eraA(y);swap(a[x],a[y]);pa[a[x]]=x;pa[a[y]]=y;insA(x);insA(y);}
			else if(op==2){y=l;eraB(x);eraB(y);swap(b[x],b[y]);pb[b[x]]=x;pb[b[y]]=y;insB(x);insB(y);}
			else{
				scanf("%d",&r);
				S=to[x];query(l,r);
				int ans=0;
				int L=1,R=id[n],p=0;
				while(L<=R){
					int mid=(L+R)>>1;
					if((bsb[mid]&S).any())	p=mid,L=mid+1;
					else R=mid-1;
				}
				if(p)for(int i=br[p];i>=bl[p];i--)if(S[pb[i]]){ans=i;break;}
				printf("%d\n",ans);
			}
		}
	}
}
bool mem2;
int main(){
	double sta=clock();
	int T=1;scanf("%*d%d",&T);while(T--)MATT::matt();
	debug("%.2fMB,%.0fms\n",abs(&mem1-&mem2)/1024./1024,(clock()-sta)/CLOCKS_PER_SEC*1000);
}