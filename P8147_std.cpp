#include<bits/stdc++.h>
#define lc(x) t[x].c[0]
#define rc(x) t[x].c[1]
using namespace std;
inline int reads(char s[]) {
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'z')ch=getchar();
	while(ch>='0'&&ch<='z')s[x++]=ch,ch=getchar();
	s[x]='\0';
	return x;
}
inline int read() {
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
typedef long long ll;
const int maxn=5e5+5;
struct tree {
	int c[2],siz;
} t[maxn*30];
int tr[maxn][4],fail[maxn],siz[maxn],rt[maxn],v[maxn],n,m,tot=1,cnt,f[maxn][19],d[maxn],zc[maxn],book[maxn],st[maxn],top,p[maxn],pos,lg2[maxn];
char s[maxn];
queue<int> q;
vector<int> e[maxn],w[maxn],bj[maxn];
typedef vector<int>::iterator iter;
bool cmp(int x,int y) {
	return p[x]<p[y];
}
void insert(int u) {
	int len=strlen(s),rt=1;
	for(register int i=0; i<len; i++) {
		int y=s[i]-'a';
		if(!tr[rt][y])tr[rt][y]=++tot;
		rt=tr[rt][y];
	}
	bj[rt].push_back(u);
}
void getfail() {
	for(register int i=0; i<4; i++)tr[0][i]=1;
	q.push(1);
	while(!q.empty()) {
		int u=q.front(),f=fail[u];
		q.pop();
		for(register int i=0; i<4; i++) {
			int j=tr[u][i];
			if(!j) {
				tr[u][i]=tr[f][i];
				continue;
			}
			fail[j]=tr[f][i];
			q.push(j);
		}
	}
}
void add(int &id,int o,int l,int r,int v) {
	id=++cnt,t[id]=t[o],t[id].siz++;
	if(l==r)return;
	int mid=l+r>>1;
	v<=mid?add(lc(id),lc(o),l,mid,v):add(rc(id),rc(o),mid+1,r,v);
}
int ask(int id,int o,int l,int r,int v) {
	if(!id)return 0;
	if(l>=v)return t[id].siz-t[o].siz;
	int mid=l+r>>1,sum=ask(rc(id),rc(o),mid+1,r,v);
	if(v<=mid)sum+=ask(lc(id),lc(o),l,mid,v);
	return sum;
}
void dfs(int u,int fa) {
	rt[u]=rt[fa];
	for(register iter it=bj[u].begin(); it!=bj[u].end(); it++)add(rt[u],rt[u],1,1000,v[*it]);
	d[u]=d[fa]+1,f[u][0]=fa,p[u]=++pos;
	for(register int i=1; i<=lg2[d[u]]; i++)f[u][i]=f[f[u][i-1]][i-1];
	for(iter it=e[u].begin(); it!=e[u].end(); it++)dfs(*it,u);
}
int lca(int x,int y) {
	if(d[x]<d[y])swap(x,y);
	while(d[x]>d[y])x=f[x][lg2[d[x]-d[y]]-1];
	if(x==y)return x;
	for(register int i=lg2[d[x]]-1; i>=0; i--)
		if(f[x][i]!=f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
int check(int u,int fa,int mid) {
	int sum=0;
	siz[u]=book[u];
	for(register iter it=w[u].begin(); it!=w[u].end(); it++)sum+=check(*it,u,mid),siz[u]+=siz[*it];
	if(u!=1)sum+=(mid-1)/siz[u]+1>1000?0:ask(rt[u],rt[fa],1,1000,(mid-1)/siz[u]+1);//小细节，这里的剪枝可以大大优化常数
	return sum;
}
void clear(int u) {
	for(register iter it=w[u].begin(); it!=w[u].end(); it++)clear(*it);
	siz[u]=book[u]=0,w[u].clear();
}
int main() {
	int k,sl1=0,sl2=0;
	n=read(),m=read();
	for(register int i=1; i<=n; i++)reads(s),sl1+=strlen(s),v[i]=read(),insert(i);
	getfail();
	for(register int i=2; i<=tot; i++)e[fail[i]].push_back(i);
	for(register int i=1; i<=tot; i++)lg2[i]=lg2[i-1]+((1<<lg2[i-1])==i);
	dfs(1,0);//建 AC 自动机，fail 树
	while(m--) {
		reads(s),sl2+=strlen(s),k=read();
		int u=1,len=strlen(s);
		for(register int i=0; i<len; i++)u=tr[u][s[i]-'a'],zc[i+1]=u,book[u]++;//得到 T 的所有节点
		sort(zc+1,zc+len+1,cmp),len=unique(zc+1,zc+len+1)-zc-1;
		st[top=1]=zc[1];
		for(register int i=2; i<=len; i++) {
			int la=lca(st[top],zc[i]);
			while(top) {
				if(d[la]>=d[st[top-1]]) {
					if(la!=st[top])w[la].push_back(st[top]),la!=st[top-1]?st[top]=la:top--;
					break;
				}
				w[st[top-1]].push_back(st[top]),top--;
			}
			st[++top]=zc[i];
		}
		while(--top)w[st[top]].push_back(st[top+1]);//建出虚树
		int l=1,r=1e9,ans=0;
		while(l<=r) {
			int mid=l+r>>1;
			if(check(st[1],1,mid)>=k)l=mid+1,ans=mid;
			else r=mid-1;
		}//二分答案
		printf("%d\n",ans);
		clear(st[1]);
	}
}