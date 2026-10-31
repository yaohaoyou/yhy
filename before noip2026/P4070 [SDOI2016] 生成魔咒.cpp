// start coding at 21:30
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
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
	const int maxn=2e5+10;
	ll ans=0;
	namespace SAM{
		int lst=1,tot=1;
		int len[maxn],fa[maxn];
		__gnu_pbds::gp_hash_table<int,int> nx[maxn];
		inline int w(int x){return len[x]-len[fa[x]];}
		inline void ins(int o){
            int x=++tot,p=lst;lst=x;
            len[x]=len[p]+1;
            while(p&&nx[p].find(o)==nx[p].end())nx[p][o]=x,p=fa[p];
            if(!p)  return fa[x]=1,ans+=w(x),void();
            int q=nx[p][o];
            if(len[q]==len[p]+1)    return fa[x]=q,ans+=w(x),void();
            int nw=++tot;
            ans-=w(q);
            nx[nw]=nx[q];fa[nw]=fa[q];len[nw]=len[p]+1;
            fa[q]=fa[x]=nw;
            ans+=w(q)+w(x)+w(nw);
            while(nx[p].find(o)!=nx[p].end()&&nx[p][o]==q)  nx[p][o]=nw,p=fa[p];
		}
	}
	using namespace SAM;
	void matt(int _c){
		int n;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			int x;scanf("%d",&x);
			ins(x);printf("%lld\n",ans);
		}
	}
}
bool mem2;
int main(){
	freopen("P4070.in","r",stdin);freopen("P4070.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
	int T=1;for(int i=1;i<=T;i++)OIMATT::matt(i);
	debug("%.0fms\n",double(clock())/CLOCKS_PER_SEC);
}