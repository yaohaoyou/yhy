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
const int maxn=2e5+10;
int n;
pii a[maxn];
int buc[maxn];
unordered_set<int> p;
void makefactors(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            while(x%i==0)   x/=i;
            buc[i]++;
            p.ep(i);
        }
    }
    if(x^1) buc[x]++,p.ep(x);
}
void del(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            while(x%i==0)   x/=i;
            buc[i]--;
        }
    }
    if(x^1) buc[x]--;
}
bool chk(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            while(x%i==0)   x/=i;
            if(buc[i])  return true;
        }
    }
    if(x^1) return buc[x];
    return false;
}
void clear(){
    for(int i:p)    buc[i]=0;
    p.clear();
}
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].fi);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i].se);
    sort(a+1,a+n+1,[&](pii x,pii y){return x.se<y.se;});
    for(int i=1;i<=n;i++)   makefactors(a[i].fi);
    for(int i:p)if(buc[i]>1)return puts("0"),clear();
    int ans=a[1].se+a[2].se;
    for(int i=1;i<=n;i++)
        if(chk(a[i].fi+1)){ans=a[i].se;break;}
    del(a[1].fi);
    for(int i:p){
        if(!buc[i]) continue;
        ans=min(ans,a[1].se*(i-a[1].fi%i));
    }
    printf("%d\n",ans);clear();
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}