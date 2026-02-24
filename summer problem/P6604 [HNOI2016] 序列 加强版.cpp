#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10,mod=998244353;
const ll INF=1e18;
int n,q;
int a[maxn];
ll f[maxn],g[maxn],ff[maxn],gg[maxn];
namespace gen{
	ull s,a,b,c,lastans=0;
	ull rand(){
		return s^=(a+b*lastans)%c;
	}
};
struct Stack{
    int st[maxn],len;
    inline int& operator[](int x){return st[x];}
    inline void ep(int x){st[++len]=x;}
    inline void pop(){len--;}
    inline int top(){return st[len];}
    inline int size(){return len;}
    inline bool empty(){return !len;}
    inline void clear(){len=0;}
}stk;
struct ST{
    int Log[maxn];
    pii st[20][maxn];
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=n;i++)   st[0][i]=pii(a[i],i);
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)  st[i][j]=min(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline pii query(int l,int r){int k=Log[r-l+1];return min(st[k][l],st[k][r-(1<<k)+1]);}
}st;
int main(){
    int typ;
    scanf("%d%d%d",&n,&q,&typ);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    ll sum=0,now=0;
    stk[0]=n+1;
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]>=a[i]) now-=1ll*(stk[stk.size()-1]-stk.top())*a[stk.top()],stk.pop();
        now+=1ll*(stk.top()-i)*a[i];sum+=now;
        stk.ep(i);
        f[i]=sum;ff[i]=now;
    }
    stk.clear();
    stk[0]=0;
    sum=now=0;
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]>=a[i]) now-=1ll*(stk.top()-stk[stk.size()-1])*a[stk.top()],stk.pop();
        now+=1ll*(i-stk.top())*a[i];sum+=now;
        stk.ep(i);
        g[i]=sum;gg[i]=now;
    }
    if(typ) scanf("%d%d%d%d",&gen::s,&gen::a,&gen::b,&gen::c);
    st.build();
    ull out=0;
    while(q--){
        int l,r;
        if(typ){
            l=gen::rand()%n+1;
            r=gen::rand()%n+1;
            if(l>r) std::swap(l,r);
        }
        else scanf("%d%d",&l,&r);
        ll ans=0;
        int pos=st.query(l,r).se;
        ans+=1ll*(pos-l+1)*(r-pos+1)*a[pos];
        ans+=f[l]-f[pos]-(pos-l)*ff[pos];
        ans+=g[r]-g[pos]-(r-pos)*gg[pos];
        gen::lastans=ans;
        out^=ans;
    }
    printf("%llu\n",out);
}