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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e6+10;
bool mem1;
int n;
int a[maxn],b[maxn],pr[maxn],sf[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    ll ans=0;
    for(int s=1;s<(1<<n);s++){
        vector<int> v;
        ll w=0;for(int i=1;i<=n;i++)if(s&(1<<i-1))v.eb(i),w+=b[i];
        if(w<=ans)continue;
        pr[0]=a[v[0]];for(int i=1;i<v.size();i++)pr[i]=max(pr[i-1],a[v[i]]);
        sf[v.size()-1]=a[v.back()];for(int i=int(v.size())-2;~i;i--)sf[i]=min(sf[i+1],a[v[i]]);
        bool flg=true;
        for(int i=0;i<v.size();i++){
            if(sf[i]==pr[i]){flg=false;break;}
        }
        if(flg) ans=w;
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}