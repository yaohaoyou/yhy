#include<bits/stdc++.h>
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
const int maxn=110;
int tp;
ll n,k;
bool dp[maxn][maxn][300];
int fr[maxn][maxn][300];
void solve3(){
    if(n==1)    return puts("1"),void();
    if(n==2){
        if(k==1)    puts("2");
        else if(!tp)    puts("3");
        else puts("1 2");
        return;
    }
    if(n==3){
        if(k==1)    puts("3");
        else if(k==2){
            if(!tp) puts("3");
            else puts("1 2");
        }
        else{
            if(!tp) puts("0");
            else puts("1 2 3");
        }
        return;
    }
}
namespace N100{
    bool check(){return n<=100;}
    void solve(){
        debug("N<=100\n");
        const int V=(1<<__lg(n)+1)-1;
        for(int i=0;i<=n;i++)for(int j=0;j<=k;j++)for(int l=0;l<=V;l++)dp[i][j][l]=0;
        dp[0][0][0]=true;
        for(int i=0;i<n;i++){
            for(int j=0;j<=k;j++){
                for(int l=0;l<=V;l++){
                    if(dp[i][j][l]){
                        if(j<k) dp[i+1][j+1][l^(i+1)]=true,fr[i+1][j+1][l^(i+1)]=i+1;
                        dp[i+1][j][l]=true;fr[i+1][j][l]=fr[i][j][l];
                    }
                }
            }
        }
        int ans=0;
        for(int i=V;~i;i--)if(dp[n][k][i]){ans=i;break;}
        if(!tp) printf("%d\n",ans);
        else{
            int x=k,y=ans,l=n;
            vector<int> out;out.clear();
            while(x){
                // printf("%d %d %d : %d\n",l,x,y,fr[l][x][y]);
                int f=fr[l][x][y];
                out.eb(f);
                y^=f;l=f-1;
                x--;
            }
            sort(out.begin(),out.end());
            for(int i:out)  printf("%d ",i);puts("");
        }
    }
}
#define int long long
inline ll calc(ll x){
    ll y=x,res=0;while(y%4)  y--;
    for(ll i=y;i<=x;i++)    res^=i;
    return res;
}
unordered_set<ll> st;
vector<ll> out;
bool slv(){
    out.clear();
    if(!st.count(1)&&!st.count(2)&&!st.count(3)&&k%4==3){
        out.eb(1);out.eb(2);out.eb(3);
        st.ep(1);st.ep(2);st.ep(3);
        k-=3;
    }
    if(k%4) return false;
    for(int i=4;i<=n;i+=4){
        if(k<4) break;
        if(!st.count(i)&&!st.count(i+1)&&!st.count(i+2)&&!st.count(i+3)){
            out.eb(i);out.eb(i+1);out.eb(i+2);out.eb(i+3);
            st.ep(i);st.ep(i+1);st.ep(i+2);st.ep(i+3);
            k-=4;
        }
    }
    return !k;
}
void solve(int _cases){
    scanf("%lld%lld",&n,&k);
    // if(_cases==282) printf("query(%lld,%lld)\n",n,k);
    // if(!(k<=3||n-k<=2))    printf("%lld : ",(1ll<<__lg(n)+1)-1);
    if(n<=3)    return solve3();
    if(N100::check())   return N100::solve();
    if(k==1)    return printf("%lld\n",n),void();
    int lg=__lg(n);
    if(k==2){
        ll ans=(1ll<<lg+1)-1;
        if(!tp) printf("%lld\n",ans);
        else{
            ll x=1ll<<lg,y=ans^x;
            if(x>y)swap(x,y);
            printf("%lld %lld\n",x,y);
        }
        return;
    }
    if(k==3){
        ll ans=(1ll<<lg+1)-1;
        if(!tp) printf("%lld\n",ans);
        else{
            ll a=1ll<<lg,b=1ll<<lg-1,c=ans^a^b;
            if(b>c)swap(b,c);if(a>b)swap(a,b);if(b>c)swap(b,c);
            printf("%lld %lld %lld\n",a,b,c);
        }
        return;
    }
    if(k==n){
        ll ans=calc(n);
        if(!tp) printf("%lld\n",ans);
        else{for(int i=1;i<=n;i++) printf("%lld ",i);puts("");}
        return;
    }
    if(k==n-1){
        ll S=calc(n),ans=0;
        for(int i=61;~i;i--){
            bool o=S&(1ll<<i);
            if(!o&&(ans|(1ll<<i))<=n)   ans|=(1ll<<i);
        }
        if(!ans)    ans=1;
        if(!tp) printf("%lld\n",ans^S);
        else{for(int i=1;i<=n;i++)if(i^ans)printf("%lld ",i);puts("");}
        return;
    }
    if(k==n-2){
        ll S=calc(n);
        ll ans1=0,ans2=0;
        for(int i=61;~i;i--){
            bool o=S&(1ll<<i);
            if(!o){
                if((ans1|(1ll<<i))<=n)  ans1|=(1ll<<i);
                else if((ans2|(1ll<<i))<=n) ans2|=(1ll<<i);
            }
        }
        if(!ans1)   ans1=1;
        if(!ans2){
            for(int i=61;~i;i--)
                if((1ll<<i)<=n&&((ans1^(1ll<<i))<=n)&&((ans1^(1ll<<i))>0)){ans1^=(1ll<<i),ans2=1ll<<i;break;}
            if(!ans2)   ans2=1;
        }
        if(!tp) printf("%lld\n",ans1^ans2^S);
        else{for(ll i=1;i<=n;i++)if((i^ans1)&&(i^ans2))printf("%lld ",i);puts("");}
        return;
    }
    if(!tp) printf("%lld\n",(1ll<<__lg(n)+1)-1);
    else{
        if(n-k>20){
            ll ans=(1ll<<lg+1)-1,K=k;
            if(n==ans){
                st.clear();
                st.ep(n);k--;
                if(slv()){
                    ans=0;
                    out.eb(n);
                    sort(out.begin(),out.end());
                    for(int i:out)  printf("%lld ",i),ans^=i;puts("");
                    assert(ans==(1ll<<lg+1)-1);
                    return;
                }
            }
            for(int i=2;i<=lg+1;i++){
                vector<int> tmp;tmp.clear();st.clear();
                k=K;
                ll tt=ans;
                for(int j=lg;j>lg-i+1;j--)    tmp.eb(1ll<<j),st.ep(1ll<<j),tt^=1ll<<j;
                tmp.eb(tt);st.ep(tt);if(!tt)continue;
                k-=i;
                if(slv()){
                    ans=0;
                    for(int j:tmp)out.eb(j);
                    sort(out.begin(),out.end());
                    for(int i:out)  printf("%lld ",i),ans^=i;puts("");
                    // debug("ans = %lld %lld\n",ans,(1ll<<lg+1)-1);
                    assert(ans==(1ll<<lg+1)-1);
                    return;
                }
            }
        }
        else{
            k=n-k;
            ll ans=(1ll<<lg+1)-1,K=k;
            ans^=calc(n);
            debug("%lld %lld %lld\n",n,k,ans);
            if(ans<=n){
                st.clear();
                st.ep(ans);k--;
                if(slv()){
                    ans=0;
                    for(int i=1;i<=n;i++)if(!st.count(i))ans^=i,printf("%lld ",i);
                    puts("");
                    assert(ans==(1ll<<lg+1)-1);
                    return;
                }
            }
            vector<int> vv;vv.clear();
            {
                int i=lg;
                for(;~i;i--)if(ans&(1ll<<i))break;
                for(;~i;i--)if(ans&(1ll<<i))vv.eb(1ll<<i);
            }
            // printf("vv = %d\n",vv.size());
            for(int i=1;i<=vv.size();i++){
                st.clear();
                k=K;
                ll tt=ans;
                for(int j=0;j<i-1;j++)    st.ep(vv[j]),tt^=vv[j];
                st.ep(tt);if(!tt||tt>n)continue;
                k-=i;
                // printf("i : %d\n",i);
                if(slv()){
                    ans=0;
                    int cc=0;
                    for(int j=1;j<=n;j++)if(!st.count(j))ans^=j,printf("%lld ",j),cc++;
                    puts("");
                    // printf("cc = %d,ans = %lld\n",cc,ans);
                    assert(ans==(1ll<<lg+1)-1);
                    return;
                }
            }
            k=K;
            if(k==3){
                st.clear();
                for(int i=0;i<=lg;i++){
                    for(int j=0;j<=lg;j++){
                        if(i==j)    continue;
                        ll x=ans^(1ll<<i)^(1ll<<j);
                        if((x^(1ll<<i))&&(x^(1ll<<j))&&(x<=n)&&x){
                            st.ep(x);st.ep(1ll<<i);st.ep(1ll<<j);
                            break;
                        }
                    }
                    if(st.size()==3)    break;
                }
                ans=0;
                for(int j=1;j<=n;j++)if(!st.count(j))ans^=j,printf("%lld ",j);
                puts("");
                assert(ans==(1ll<<lg+1)-1);
                return;
            }
            k=n-K;
        }
        printf("query(%lld,%d)\n",n,k);
        // assert(0);
        puts("-1");
    }
    return;
}
main(){int T;scanf("%lld%lld",&T,&tp);for(int i=1;i<=T;i++)solve(i);}