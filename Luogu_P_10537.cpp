#include <bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define eb emplace_back
#define ull unsigned long long
const int maxn=1e5+10,maxm=maxn<<1,base=2;
int n,m;
namespace Graph{
	int cnt=1;
	int head[maxn];
	struct edge{int nxt,to;}e[maxm];
	inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
	inline void initgraph(){for(int i=1;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
ull s[10];
inline ull qpow(ull x,int y){
	ull res=1;
	while(y){
		if(y&1) res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}
vector<pii> v;
int ans;
bool flag[maxn];
bool dfs(int u,int fa){
    int son=0;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        if(!dfs(t,u))    return false;
        if(flag[t])
        son++;
    }
    return true;
}
int solve(int N, int M, std::vector<int> F, std::vector<std::vector<int>> S) {
	n=N;m=M;ans=0;v.clear();memset(flag,0,sizeof(flag));
	for(int i=0;i<m;i++)	s[i]=0;
    int lst=-1;
	for(int i=0;i<n-1;i++){
		ull x=0;bool flag=true;
		for(int j=0;j<m;j++){
			s[j]+=qpow(base,S[j][i]);
			if(!x)	x=s[j];
			if(x!=s[j])	flag=false;
		}
		if(flag){
            v.eb(lst+1,i);
            lst=i;
        }
	}
    for(int i=0;i<v.size();i++){
        for(int j=v[i].first;j<=v[i].second;j++)
            flag[j]=true;
        dfs(1,0);
    }
	return ans;
}