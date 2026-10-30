// start coding at 18:30
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define ep emplace
#define eb emplace_back
#define cpy(a,b,siz) copy(b,b+siz+1,a)
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
bool mem1;
namespace OIMATT{
	const int maxn=5e5+10,V=1e3;
	int n,q;
	char s[maxn];
	namespace ACAM{
		int tot;
		int nx[maxn][4],fail[maxn],w[maxn];
		vector<int> v[maxn];
		void ins(int x){
			int len=strlen(s+1);
			int p=0;
			for(int i=1;i<=len;i++){
				int o=s[i]-'a',&t=nx[p][o];
				if(!t)	t=++tot;
				p=t;
			}
			v[p].eb(x);
		}
		queue<int> que;
		void build(){
			for(int i=0;i<4;i++)if(nx[0][i])que.ep(nx[0][i]);
			while(!que.empty()){
				int u=que.front();que.pop();
				for(int i=0;i<4;i++){
					int &t=nx[u][i];
					if(t)	que.ep(t),fail[t]=nx[fail[u]][i];
					else	t=nx[fail[u]][i];
				}
			}
		}
	}
	using namespace ACAM;
	namespace SGT{
		const int maxp=maxn*20;
		#define ls lc[p]
		#define rs rc[p]
		#define lson ls,l,mid
		#define rson rs,mid+1,r
		#define al(x) rt[x],0,V
		#define all(x,y) rt[x],rt[y],0,V
		#define setpos int p,int l,int r
		#define setmid int mid=(l+r)>>1
		int cur;
		int rt[maxn],tr[maxp],lc[maxp],rc[maxp];
		void upd(int &p,int q,int l,int r,int x){
			p=++cur;tr[p]=tr[q]+1;ls=lc[q];rs=rc[q];
			if(l==r)return;
			setmid;
			x<=mid?upd(ls,lc[q],l,mid,x):upd(rs,rc[q],mid+1,r,x);
		}
		int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=0;if(pl<=mid&&ls)res=query(lson,pl,pr);if(pr>mid&&rs)res+=query(rson,pl,pr);return res;}
	}
	using namespace SGT;
	namespace Graph{
		#define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
		int cnt;
		int head[maxn];
		struct edge{int nxt,to;}e[maxn];
		inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
	}
	using namespace Graph;
	int dfn[maxn],dep[maxn],cot;
	int up[20][maxn],Log[maxn];
	namespace stLCA{
		int st[20][maxn];
		inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
		void dfs(int u,int ft){up[0][u]=ft;dep[u]=dep[ft]+1;st[0][dfn[u]=++cot]=ft;go(u,i)dfs(t,u);}
		void build(){
			dfs(0,0);
			for(int i=2;i<=cot;i++)Log[i]=Log[i/2]+1;
			for(int i=1;i<=Log[cot];i++)
				for(int j=1;j+(1<<i)-1<=cot;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
		}
		inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
	}
	using stLCA::LCA;
	void dfs(int u){
		if(!v[u].empty()){
			for(int x:v[u]){
				if(!rt[u])	upd(all(u,fail[u]),x);
				else	upd(all(u,u),x);
			}
		}
		// else	rt[u]=rt[fail[u]];
		go(u,i)dfs(t);
	}
	inline int jp(int x,int d){while(d)x=up[Log[d]][x],d^=(1<<Log[d]);return x;}
	vector<int> son[maxn];
	vector<piii> vec;
	int b[maxn],c[maxn<<1],k;
	int f[maxn];
	void dfs2(int u){
		for(int t:son[u]){
			dfs2(t);
			vec.eb(pii(jp(t,dep[t]-dep[u]-1),t),f[t]);
			f[u]+=f[t];
		}
	}
	void matt(int _c){
		scanf("%d%d",&n,&q);
		for(int i=1;i<=n;i++){
			int x;
			scanf("%s%d",s+1,&x);
			ins(x);
		}
		// for(int i=0;i<=tot;i++)for(int j=0;j<4;j++)if(nx[i][j])printf("%d %d %c\n",i,nx[i][j],j+'a');
		build();
		for(int i=1;i<=tot;i++)add(fail[i],i);
		stLCA::build();dfs(0);
		for(int i=1;i<=Log[tot];i++)for(int j=0;j<=tot;j++)up[i][j]=up[i-1][up[i-1][j]];
		while(q--){
			int K;
			scanf("%s%d",s+1,&K);
			int m=strlen(s+1),p=0;
			k=0;b[++k]=0;
			for(int i=1;i<=m;i++){
				int o=s[i]-'a';
				p=nx[p][o];b[++k]=p;f[p]++;
			}
			auto cmp=[&](int x,int y){return dfn[x]<dfn[y];};
			sort(b+1,b+k+1,cmp);k=unique(b+1,b+k+1)-b-1;
			int kk=0;c[kk]=b[1];
			for(int i=2;i<=k;i++){
				c[++kk]=LCA(b[i-1],b[i]);
				c[++kk]=b[i];
			}
			sort(c+1,c+kk+1,cmp);k=unique(c+1,c+kk+1)-c-1;
			for(int i=2;i<=k;i++){
				int l=LCA(c[i-1],c[i]);
				if(l^c[i])	son[l].eb(c[i]);
			}
			dfs2(0);
			int L=0,R=5e8,ans=0;
			while(L<=R){
				int mid=(L+R)>>1;
				int now=0;
				// printf("mid = %d\n",mid);
				for(auto [seg,x]:vec){
					int l=seg.fi,r=seg.se;
					// printf("%d %d %d : %d\n",l,r,(mid+x-1)/x,query(al(r),(mid+x-1)/x,V)-query(al(fail[l]),(mid+x-1)/x,V));
					if((mid+x-1)/x<=V)	now+=query(al(r),(mid+x-1)/x,V)-query(al(fail[l]),(mid+x-1)/x,V);
				}
				if(now>=K)	ans=mid,L=mid+1;
				else	R=mid-1;
			}
			printf("%d\n",ans);
			vec.clear();
			for(int i=1;i<=k;i++)son[c[i]].clear(),f[c[i]]=0;
		}
	}
}
bool mem2;
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
	int T=1;for(int i=1;i<=T;i++)OIMATT::matt(i);
	debug("%.0fms\n",double(clock())/CLOCKS_PER_SEC);
}