//  P3806 【模板】点分治 1
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10,inf=1e7+10;
int n,q,cnt=0,rt=0,sum;
int head[maxn],siz[maxn],ques[maxn],maxx[maxn],dis[maxn];
bool vis[maxn],tf[inf],ok[maxn];
struct edge{
	int nxt,to,w;
}e[maxn];
void build(int x,int y,int w){
	e[++cnt]={head[x],y,w};
	head[x]=cnt;
}
void heaviest(int x,int fa){  // 找重心 
	siz[x]=1;
	maxx[x]=0;
	for(int i=head[x];i;i=e[i].nxt){
		if(e[i].to==fa||vis[e[i].to])	continue;
		heaviest(e[i].to,x);
		maxx[x]=max(maxx[x],siz[e[i].to]);
		siz[x]+=siz[e[i].to];
	}
	maxx[x]=max(maxx[x],sum-siz[x]);
	if(maxx[x]<maxx[rt])	rt=x;
}
int dd[maxn],tot=0;
void calcdist(int x,int fa){
	dd[++tot]=dis[x];
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==fa||vis[to])	continue;
		dis[to]=dis[x]+e[i].w;
		calcdist(to,x);
	}
}
queue<int> tag;
void dfs(int x,int fa){
	tf[0]=1;
	tag.push(0);
	vis[x]=1;
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==fa||vis[to])	continue;
		dis[to]=e[i].w;
		calcdist(to,x);
		for(int j=1;j<=tot;j++){
			for(int k=1;k<=q;k++)	if(ques[k]>=dd[j])	ok[k]|=tf[ques[k]-dd[j]];
		}
		for(int j=1;j<=tot;j++){
			if(dd[j]<inf)	tag.push(dd[j]),tf[dd[j]]=1;
		}
		tot=0;
	}
	while(!tag.empty())	tf[tag.front()]=0,tag.pop();
	for(int i=head[x];i;i=e[i].nxt){
		int to=e[i].to;
		if(to==fa||vis[to])	continue;
		sum=siz[to];
		rt=0;
		maxx[rt]=0x3f3f3f3f;
		heaviest(to,x);
		heaviest(rt,-1);
		dfs(rt,x);
	}
}
int main(){
	scanf("%d%d",&n,&q);
	for(int i=1;i<n;i++){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		build(x,y,w);
		build(y,x,w);
	}
	for(int i=1;i<=q;i++)	scanf("%d",&ques[i]);
	sum=n;
	rt=0;
	maxx[rt]=0x3f3f3f3f;
	heaviest(1,-1);  // rt为重心
	dfs(rt,-1);
	for(int i=1;i<=q;i++){
		if(ok[i])	puts("AYE");
		else	puts("NAY");
	}
}