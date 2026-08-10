#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define eb emplace_back
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,x,y) for(int i=(x);i<=(y);i++)
#define per(i,y,x) for(int i=(y);i>=(x);i--)
bool Memst;
namespace cyzz
{
    #define N 500005
    #define mod 1000000007
    inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
    inline void Add(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline int qpow(int x,int y){int ret=1;for(;y;y>>=1,x=1ll*x*x%mod)if(y&1)ret=1ll*ret*x%mod;return ret;}
    int n,q,a[N];int pre[N];
    struct Node{int l,r,id;};
    vector<Node>c[N];
    int f[N],g[N*2];
    int ans[N],bk[N],I[N];
    inline int qry(int l,int r)
    {
        int tmp=add(pre[r],mod-pre[l-1]);
        return 1ll*tmp*tmp%mod*I[r-l+1]%mod*I[r-l+1]%mod;
    }
    void MAIN()
    {
        scanf("%d%d",&n,&q);
        rep(i,1,n) scanf("%d",&a[i]),I[i]=qpow(i,mod-2);
        sort(a+1,a+n+1,greater<int>());
        rep(i,1,n) a[i]%=mod,pre[i]=add(pre[i-1],a[i]);
        rep(i,1,q)
        {
            int l,r;scanf("%d%d",&l,&r);
            int rest=n%l;
            if(!rest) c[l].eb((Node){1,n,i});
            else
            {
                if(l==r) {bk[i]=-1;continue;}
                int cnt=(rest+r-l-1)/(r-l),res=rest%(r-l);
                if(cnt>n/l) {bk[i]=-1;continue;}
                c[l].eb((Node){1,(n/l-cnt)*l,i});
                if(res)
                {
                    Add(ans[i],qry((n/l-cnt)*l+1,(n/l-cnt)*l+l+res));
                    c[r].eb((Node){n-(cnt-1)*r+1,n,i});
                }
                else
                    c[r].eb((Node){n-cnt*r+1,n,i});
            }
        }
        rep(i,1,n)
        {
            for(int j=i;j<=n;j+=i)
                f[j]=add(f[j-i],qry(j-i+1,j));
            for(int j=n-i+1;j>0;j-=i)
                g[j]= (g[j+i],qry(j,j+i-1));
            for(Node j:c[i])
            {
                if(j.l==1)
                    Add(ans[j.id],f[j.r]);
                else if(j.r==n)
                    Add(ans[j.id],g[j.l]);
            }
        }
        rep(i,1,q)
        {
            if(bk[i]) printf("-1\n");
            else printf("%d\n",ans[i]);
        }
    }
}bool Memed;
int main()
{
    // freopen("in.in","r",stdin);
    // freopen("out.out","w",stdout);
    cyzz::MAIN();
    debug("%.2lfms %.2lfMB",1.0*clock()/CLOCKS_PER_SEC*1000,
        1.0*abs(&Memed-&Memst)/1024/1024);
}