#include<bits/stdc++.h>
#define db double
#define ll long long
#define ep emplace
#define eb emplace_back
#define ef emplace_front
#define pii pair<int,int>
#define piiii pair<pii,pii>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
bool mem1;
namespace MATT{
	const int maxn=1.2e5+10;
	int n,q;
	int a[maxn];
	ll ans[maxn];
	vector<pii> Q[maxn];
	struct Stack{
	    int s[maxn],tp;
	    inline void clear(){tp=0;}
	    inline bool empty(){return !tp;}
	    inline void ep(int x){s[++tp]=x;}
	    inline void pop(){tp--;}
	    inline int top(){return s[tp];}
	    inline int size(){return tp;}
	    int& operator[](int x){return s[x];}
	}s[2];
	namespace SegmentTree{
	    #define ls p<<1
	    #define rs p<<1|1
	    #define lson ls,l,mid
	    #define rson rs,mid+1,r
	    #define all 1,1,n
	    #define setmid int mid=(l+r)>>1
	    #define setpos int p,int l,int r
	    int tr[maxn<<2],cnt[maxn<<2],tag[maxn<<2];
	    ll his[maxn<<2];int sum[maxn<<2];
	    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);cnt[p]=tr[ls]<tr[rs]?cnt[ls]:(tr[ls]>tr[rs]?cnt[rs]:cnt[ls]+cnt[rs]);his[p]=his[ls]+his[rs];}
	    inline void pt(int p,int s){tag[p]+=s;tr[p]+=s;}
	    inline void pthis(int p,int s){his[p]+=1ll*cnt[p]*s,sum[p]+=s;}
	    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}if(sum[p]){if(tr[p]==tr[ls])pthis(ls,sum[p]);if(tr[p]==tr[rs])pthis(rs,sum[p]);sum[p]=0;}}
	    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
	    inline void upd(int x){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=0;cnt[p]=1;while(p>>=1)pu(p);}
	    ll query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return his[p];pd(p);setmid;ll res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res+=query(rson,pl,pr);return res;}
	    void build(setpos){if(l==r)return tr[p]=1e9,cnt[p]=1,void();setmid;build(lson);build(rson);pu(p);}
	}
	using namespace SegmentTree;
	void matt(){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)	scanf("%d",&a[i]);
		scanf("%d",&q);
		for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[r].eb(l,i);}
		build(all);
		for(int i=1;i<=n;i++){
	        while(!s[0].empty()&&a[s[0].top()]>a[i]){
	            upd(all,s[0][s[0].size()-1]+1,s[0].top(),a[s[0].top()]-a[i]);
	            s[0].pop();
	        }
	        s[0].ep(i);
	        while(!s[1].empty()&&a[s[1].top()]<a[i]){
	            upd(all,s[1][s[1].size()-1]+1,s[1].top(),a[i]-a[s[1].top()]);
	            s[1].pop();
	        }
	        s[1].ep(i);
        	if(i^1)	upd(all,1,i-1,-1);upd(i);
        	pthis(1,1);
        	for(pii t:Q[i])	ans[t.se]=query(all,t.fi,i);
		}
		for(int i=1;i<=q;i++)	printf("%lld\n",ans[i]);
	}
}
bool mem2;
int main(){int T=1;while(T--)MATT::matt();}