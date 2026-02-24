#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define piii pair<int,pii>
#define pb push_back
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10;
basic_string<int> v[maxn],b[maxn];
bool ans[110][maxn],out[110][maxn],tmp[110][maxn];
int id[maxn],bel[maxn];
int n,k,q,mx;
int tot;
int a[maxn],tp;
void discrete(){
    sort(a+1,a+tp+1);
    mx=unique(a+1,a+tp+1)-a-1;
    for(int i=1;i<=n;i++){
        for(int l=0;l<v[i].size();l++){
            int j=v[i][l];
            int x=lower_bound(a+1,a+mx+1,j)-a;
            v[i][l]=++tot;
            id[tot]=x;bel[tot]=i;
            b[x].pb(tot);
        }
    }
}
void solve(){
    cin>>n>>k>>q;
    tot=tp=0;
    for(int i=1;i<=n;i++){
        int l;cin>>l;
        while(l--){
            int x;cin>>x;
            v[i].pb(x);
            a[++tp]=x;
        }
    }
    discrete();
    for(int i=1;i<=n;i++)
        for(int j:v[i])
            if(id[j]==1)    tmp[1][j]=true;
    for(int t=1;t<=100;t++){
        for(int i=1;i<=n;i++){
            int cnt=0;
            for(int j=0;j<v[i].size();j++){
                ans[t][v[i][j]]|=cnt;
                cnt+=tmp[t][v[i][j]];
                if(j>=k-1)  cnt-=tmp[t][v[i][j-k+1]];
            }
        }
        for(int i=1;i<=mx;i++){
            int s=0,p=0;
            for(int j=0;j<b[i].size();j++){
                int l=b[i][j];
                if(!ans[t][l])   continue;
                if(bel[l]!=p)   s++;
                if(s==1)  p=bel[l];
            }
            if(s)
                for(int j=0;j<b[i].size();j++)
                    if((s^1)||(bel[b[i][j]]^p)) tmp[t+1][b[i][j]]=true;
            out[t][i]=s;
        }
    }
    while(q--){
        int r,x;cin>>r>>x;
        int k=lower_bound(a+1,a+mx+1,x)-a;
        if(k<=0||k>mx||a[k]!=x) putchar('0');
        else putchar(out[r][k]+'0');
        putchar('\n');
    }
    mems(ans,0);mems(out,0);mems(tmp,0);
    for(int i=1;i<=n;i++)   v[i].clear();
    for(int i=1;i<=mx;i++)  b[i].clear();
}
int main(){
    freopen("chain.in","r",stdin);freopen("chain.out","w",stdout);
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int T;cin>>T;while(T--) solve();
}
