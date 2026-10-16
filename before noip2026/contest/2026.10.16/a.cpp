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
const int maxn=1e6+10;
bool mem1;
int n;
unordered_map<int,int> f;
vector<int> fac;
priority_queue<pii,vector<pii>,greater<pii>> q;
bool mem2;
void matt(int _cases){
    fac.clear();f.clear();
    scanf("%d",&n);
    for(int i=1;1ll*i*i<=n+1;i++)if((n+1)%i==0){
        int x=(n+1)/i;
        fac.eb(i);if(x!=i)fac.eb(x);
    }
    sort(fac.begin(),fac.end());
    f[1]=0;
    for(int i:fac){
        int x=__gcd(i,n+1-i);
        for(int j:fac)if(j>i){
            int stp=(j-i+x-1)/x;
            if(f.find(j)==f.end()||f[j]>f[i]+stp)f[j]=f[i]+stp;
        }
    }
    printf("%d\n",f[n+1]);
}
int main(){freopen("a.in","r",stdin);freopen("a.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}