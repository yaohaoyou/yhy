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
bool mem1;
const int maxn=810,mod=998244353;
struct mint{
    int v;
    mint(int _v=0){v=_v;}
    mint operator+=(mint y){v+=y.v;(v>=mod)&&(v-=mod);}
    mint operator+(mint y){y+=v;return y;}
    mint operator-=(mint y){v-=y.v;(v<0)&&(v+=mod);}
    mint operator-(mint y){y-=v;return y;}
    mint operator*=(mint y){v=1ull*v*y.v%mod;}
    mint operator+(mint y){y*=v;return y;}
};
int n,m;
int a[maxn];
vector<int> v[maxn];
mint f[maxn][maxn],g[maxn][maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),v[a[i]].eb(i);
    f[0][0]=1;
    for(int i=1;i<=m;i++){
        int mx=v[i].size();
        // for(int j=1;j<=v[i-1].size()&&j<=v[i].size();j++){
        //     for(int k=0,l=v[i].size()-1-j;k<j;k++){
        //         while(l+1<v[i].size()&&v[i][l+1]<=v[i-1][k])l++;
        //         if(l>=k){mx=j-1;break;}
        //     }
        //     if(mx<v[i].size())break;
        // }
        for(int j=n;j;j--){
            for(int k=n;k;k--){
                
            }
        }
        for(int j=0;j<=v[i-1].size();j++)
            for(int k=0;k<=mx&&j+k<=v[i-1].size();k++)f[i][k]+=f[i-1][j];
    }
}