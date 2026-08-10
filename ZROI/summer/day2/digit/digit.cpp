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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+1000+10,B=7000;
bool mem1;
int n=2e5,tot;
pii a[maxn];
int f[maxn/B*9+10][maxn],g[maxn/B*9+10][maxn];
vector<int> trans[maxn];
int id[maxn];
struct Queue{
    int q[maxn<<1],hd,ta;
    inline void clear(){hd=1;ta=0;}
    inline bool empty(){return hd>ta;}
    inline int top(){return q[hd];}
    inline void ep(int x){q[++ta]=x;}
    inline void pop(){hd++;}
}q1,q2;
int F[maxn];
bool mem2;
inline int max_digit(int x){int res=0;while(x)gmx(res,x%10),x/=10;return res;}
inline bool find_digit(int x,int c){while(x)if(x%10==c)return true;else x/=10;return false;}
void solve(int i){
    id[i]=++tot;
    int o=id[i];
    q1.clear();f[o][i]=1;q1.ep(i);
    while(!q1.empty()){
        int x=q1.top();q1.pop();
        for(int i:trans[x]){
            if(!f[o][i]){   
                f[o][i]=f[o][x]+1;
                q1.ep(i);
            }
        }
    }
    q1.clear();g[o][i]=1;q1.ep(i);
    while(!q1.empty()){
        int x=q1.top();q1.pop();
        int j=x;
        while(j){
            if(!g[o][x+j%10])   g[o][x+j%10]=g[o][x]+1,q1.ep(x+j%10);
            if(!g[o][x-j%10])   g[o][x-j%10]=g[o][x]+1,q1.ep(x-j%10);
            j/=10;
        }
    }
}
int x,y;
int block;
int b[maxn];
int lst;
void out(int x){
    if(x>n+n)lst=-1;
    else    lst=x;
    printf("%d\n",lst);
}
void matt(int _cases){
    scanf("%d%d",&x,&y);x^=(lst+1);y^=(lst+1);
    // if(_cases<=20)    debug("%d %d\n",x,y);
    if(id[x])   return out(g[id[x]][y]-1);
    if(y>x){
        int k=lower_bound(b+1,b+block+1,x)-b;
        if(k<=block&&y>b[k]+8){
            int ans=1e9;
            for(int i=b[k];i<=b[k]+8;i++)if(f[id[i]][x]&&g[id[i]][y])gmn(ans,f[id[i]][x]-1+g[id[i]][y]-1);
            return out(ans);
        }
    }
    else{
        int k=lower_bound(b+1,b+block+1,y)-b;
        if(k<=block&&x>b[k]+8){
            int ans=1e9;
            for(int i=b[k];i<=b[k]+8;i++)if(f[id[i]][x]&&g[id[i]][y])gmn(ans,f[id[i]][x]-1+g[id[i]][y]-1);
            return out(ans);
        }
    }
    // if(abs(y-x)>B+B)    debug("%d %d\n",x,y);
    // assert(abs(y-x)<=B+B);
    // if(_cases<=20)    debug("nboj\n");
    int L=max(0,min(x,y)-200),R=max(x,y)+200;
    q1.clear();F[x]=1;q1.ep(x);
    while(!q1.empty()){
        int u=q1.top();q1.pop();
        int j=u;
        while(j){
            if(u+j%10<=R&&!F[u+j%10])   F[u+j%10]=F[u]+1,q1.ep(u+j%10);
            if(u-j%10>=L&&!F[u-j%10])   F[u-j%10]=F[u]+1,q1.ep(u-j%10);
            j/=10;
        }
        if(F[y])break;
    }
    if(!F[y])   F[y]=1e9;
    out(F[y]-1);
    fill(F+L,F+R+1,0);
}
int main(){
    freopen("digit.in","r",stdin);freopen("digit.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    for(int i=0;i<maxn/B*9+10;i++)for(int j=n+1000;j<maxn;j++)g[i][j]=1e9;
    for(int i=0;i<=n;i++)
        for(int j=max(0,i-9);j<=min(n,i+9);j++)
            if((j^i)&&find_digit(j,abs(j-i)))trans[i].eb(j);
    for(int i=B;i<=n;i+=B){
        b[++block]=i;
        for(int j=i;j<=i+8;j++) solve(j);
    }
    int T;scanf("%d",&T);
    for(int i=1;i<=T;i++)matt(i);
}