#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#include<ext/pb_ds/hash_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define puu pair<ull,ull>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
using namespace __gnu_pbds;
mt19937_64 matt(1121);
const int maxn=1e5+100,N=1e5,inf=1e9;
const ull bs=matt();
int n,m,k;
char s[maxn],t[maxn],tmp[maxn];
ull hs[maxn],ht[maxn],pq[maxn];
vector<int> zhuan[maxn];
int vec[maxn*100],vl;
pii F[maxn<<1];int dp[maxn<<1];
vector<pii> vf[maxn];
gp_hash_table<int,pii> fr[maxn];
int f[2][maxn];vector<int> clr[2];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void data(){
    srand(time(0));
    n=1e5;m=1e5;k=10;
    printf("%d\n",k);
    for(int i=1;i<=n;i++)putchar('a');putchar('\n');
    for(int i=1;i<=m;i++)putchar('a');putchar('\n');
    exit(0);
}
inline ull Hash(int l,int r,bool o){
    if(!o)  return hs[r]-pq[r-l+1]*hs[l-1];
    return ht[r]-pq[r-l+1]*ht[l-1];
}
inline void getf(int x,int y){if(f[x&1][y]==inf)f[x&1][y]=dp[x-y+N],clr[x&1].eb(y);}
inline void getfr(int x,int y){if(fr[x].find(y)==fr[x].end())   fr[x][y]=F[x-y+N];}
int main(){
    freopen("string.in","r",stdin);freopen("string.out","w",stdout);
    scanf("%d%s%s",&k,s+1,t+1);n=strlen(s+1);m=strlen(t+1);
    {
        int x=0;
        for(int i=1;i<=k;i++)   tmp[++x]='!';
        for(int i=1;i<=n;i++)   tmp[++x]=s[i];
        for(int i=1;i<=k;i++)   tmp[++x]='!';
        n=x;swap(tmp,s);
    }
    mems(dp,0x3f);mems(f,0x3f);
    pq[0]=1;for(int i=1;i<=max(n,m);i++)    pq[i]=pq[i-1]*bs;
    for(int i=1;i<=n;i++)   hs[i]=hs[i-1]*bs+s[i];
    for(int i=1;i<=m;i++)   ht[i]=ht[i-1]*bs+t[i];
    int all=0;
    for(int i=1;i<=n;i++){
        for(int j:clr[i&1])  f[i&1][j]=inf;
        clr[i&1].clear();
        for(pii j:vf[i])    f[i&1][j.fi]=j.se,clr[i&1].eb(j.se);
        bool flag=false;
        sort(zhuan[i].begin(),zhuan[i].end());
        int p=0;vl=0;
        for(int j=1;1;j++){
            flag|=(s[i]==t[j]);
            f[i&1][j]=j-flag;fr[i][j]=pii(i,1);
            while(p<zhuan[i].size()&&zhuan[i][p]<j){vec[++vl]=zhuan[i][p];p++;}
            if(p==zhuan[i].size()||(zhuan[i][p]^j)) vec[++vl]=j;
            if(j>k||j>m)    break;
        }
        while(p<zhuan[i].size()){vec[++vl]=zhuan[i][p];p++;}
        sort(vec+1,vec+vl+1);
        all+=vl;
        for(int o=1;o<=vl;o++){
            int j=vec[o];
            getf(i-1,j);getf(i,j-1);getf(i-1,j-1);
            clr[i&1].eb(j);
            gmn(f[i&1][j],min(min(f[(i-1)&1][j],f[i&1][j-1]),f[(i-1)&1][j-1])+1);
            if(f[i&1][j]==f[(i-1)&1][j]+1)    fr[i][j]=pii(i-1,j),getfr(i-1,j);
            else if(f[i&1][j]==f[i&1][j-1]+1)    fr[i][j]=pii(i,j-1),getfr(i,j-1);
            else if(f[i&1][j]==f[(i-1)&1][j-1]+1)  fr[i][j]=pii(i-1,j-1),getfr(i-1,j-1);
            if(s[i]==t[j]){
                gmn(f[i&1][j],f[(i-1)&1][j-1]);
                if(f[i&1][j]==f[(i-1)&1][j-1])    fr[i][j]=pii(i-1,j-1),getfr(i-1,j-1);
            }
            if(f[i&1][j]>k){dp[i-j+N]=inf;continue;}
            int l=1,r=min(n-i,m-j),p=0;
            while(l<=r){
                int mid=(l+r)>>1;
                if(Hash(i,i+mid,0)==Hash(j,j+mid,1))    p=mid,l=mid+1;
                else r=mid-1;
            }
            if(p){dp[i-j+N]=f[i&1][j];F[i-j+N]=pii(i,j);vf[i+p].eb(j+p,f[i&1][j]);fr[i+p][j+p]=pii(i,j);}
            else dp[i-j+N]=inf;
            zhuan[i+p+1].eb(j+p+1);
        }
        vector<int>().swap(zhuan[i]);
        if(i>k&&f[i&1][m]<=k){
            int x=i,y=m;
            while(y^1){
                int tx=fr[x][y].fi,ty=fr[x][y].se;
                x=tx;y=ty;
            }
            printf("%d %d\n",max(1,x-k),min(i,n-k)-k);
            return 0;
        }
        if(clock()/CLOCKS_PER_SEC>0.96)break;
    }
    puts("NIE");
}