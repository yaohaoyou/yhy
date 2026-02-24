#include<bits/stdc++.h>
#define int long long
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=3e5+10;
int n,m,q;
int p[maxn],v[maxn];
unordered_map<string,pii> mp;
pii a[maxn];
ll out[maxn];
vector<pii> Q[maxn];
ll c[maxn];
stack<int> stk;
struct node
{
	int l,r;
	ll tag1,tag2,sum;
	void update(ll mul,ll add)
	{
		sum=sum*mul+(r-l+1)*add;
		tag1=tag1*mul;
		tag2=tag2*mul+add;
	}
}tree[maxn<<2];
int x,y;
void pushdown(int p)
{
	tree[p*2].update(tree[p].tag1,tree[p].tag2);
	tree[p*2+1].update(tree[p].tag1,tree[p].tag2);
	tree[p].tag1=1;
	tree[p].tag2=0;
}
void build(int p,int l,int r)
{
	tree[p].l=l,tree[p].r=r;
	tree[p].sum=0,tree[p].tag1=1,tree[p].tag2=0;
	if(l==r)    return;
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
}
void update(int p,ll mul,ll add)
{
	if(x<=tree[p].l&&y>=tree[p].r)
	{
		tree[p].update(mul,add);
		return ;
	}
	pushdown(p);
	int mid=(tree[p].l+tree[p].r)/2;
	if(x<=mid)
		update(p*2,mul,add);
	if(mid<y)
		update(p*2+1,mul,add);
	tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
	return ;
}
ll ans;
void query(int p)
{
	if(x<=tree[p].l&&tree[p].r<=y)
	{
		ans+=tree[p].sum;
		return ;
	}
	pushdown(p);
	int mid=(tree[p].l+tree[p].r)/2;
	if(x<=mid)
		query(2*p);
	if(y>mid)
		query(2*p+1);
	tree[p].sum=tree[p*2].sum+tree[p*2+1].sum;
	return ;
}
inline ll query(int l,int r){x=l;y=r;ans=0;query(1);return ans;}
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m>>q;
    for(int i=1;i<=n;i++){
        string s;
        cin>>p[i]>>v[i]>>s;
        mp[s]=pii(p[i],v[i]);
    }
    for(int i=1;i<=m;i++){
        string s;cin>>s;
        a[i]=mp[s];
        p[i]=a[i].fi;
    }
    build(1,1,m);
    for(int i=1;i<=q;i++){int l,r;cin>>l>>r;Q[r].eb(l,i);}
    for(int i=1;i<=m;i++){
        while(!stk.empty()&&a[stk.top()].fi<a[i].fi)    stk.pop();
        int j=(stk.empty()?0:stk.top())+1;
        stk.ep(i);
        // for(int k=1;k<j;k++)    c[k]=c[k]-c[j]*2+a[i].se;
        // for(int k=j;k<=i;k++)   c[k]=-c[k]+a[i].se;
        ll cj=query(j,j);
        if(j>1){
            x=1;y=j-1;
            update(1,1,-cj*2ll+a[i].se);
        }
        if(j<=i){
            x=j;y=i;
            update(1,-1,a[i].se);
        }
        for(pii k:Q[i]) out[k.se]=query(k.fi,k.fi);
    }
    for(int i=1;i<=q;i++)   cout<<out[i]<<'\n';
}