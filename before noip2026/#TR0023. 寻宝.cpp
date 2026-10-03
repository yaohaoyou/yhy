#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1010;
int n,m;
vector<pii> out;
vector<pii> v[2][2];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    debug("%d\n",n*n/2*m+m*m/2*n);
    // assert((n&1)||(m&1));
    bool fl=!(n&1);
    if(!(n&1)&&!(m&1)){
        fl=false;
        for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)  v[i>n/2][j>m/2].eb(i,j);
        for(int i=0;i<v[0][0].size();i++)   out.eb(v[0][0][i]),out.eb(v[1][1][i]);
        for(int i=0;i<v[0][1].size();i++)   out.eb(v[0][1][i]),out.eb(v[1][0][i]);
        // printf("%d %d %d %d\n",v[0][0].size(),v[0][1].size(),v[1][0].size(),v[1][1].size());
    }
    else{   
        if(fl)swap(n,m);
        for(int i=1,j=m;i<j;i++,j--){
            for(int l=1,r=n;l<=r;l++,r--){
                out.eb(l,i);if(l^r)out.eb(r,j);
            }
            if(n&1) out.eb(1,j);
            for(int l=n,r=1+(n&1);l>=r;l--,r++){
                out.eb(l,i);out.eb(r,j);
            }
        }
        if(m&1){
            int x=(m+1)>>1;
            for(int i=1,j=n;i<=j;i++,j--){
                out.eb(i,x);
                if(i^j) out.eb(j,x);
            }
        }
    }
    out.eb(1,1);
    if(fl){for(auto &&[i,j]:out)swap(i,j);swap(n,m);}
    int ans=0;
    int x=1,y=1;
    for(auto [i,j]:out)ans+=abs(x-i)+abs(y-j),x=i,y=j;
    printf("%d\n%d\n",ans,n*m);
    for(auto [i,j]:out) printf("%d %d\n",i,j);
}