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
const int maxn=1e5+10,mod=1e9+7,base=191981,mod2=998244353,base2=20250803;
int cnt;
map<pii,int> mp;
bool bk[maxn];
int n,m;
vector<int> a[maxn];
vector<int> b[maxn];
priority_queue<pii> pq;
void ins(pii k){
    while(!pq.empty()&&pq.top()>k){
        if(!pq.top().fi)    exit(puts("No")&0);
        int x=pq.top().se;
        bk[x]=false;
        pq.pop();ins(pii(0,x));
    }
    k.fi=bk[k.se];
    if(!pq.empty()&&pq.top()>k) exit(puts("No")&0);
    pq.ep(k);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        int nw=0,nw2=0;
        for(int j=1;j<=x;j++){
            int t;scanf("%d",&t);
            int &y=mp[pii(nw,nw2)];
            if(!y)  y=++cnt;
            b[y].eb(t);
            nw=(1ll*nw*base+t)%mod;nw2=(1ll*nw2*base2+t)%mod;
            a[i].eb(t);
        }
        if(mp.find(pii(nw,nw2))!=mp.end())  exit(puts("No")&0);
    }
    mems(bk,true);
    for(int i=1;i<=cnt;i++){
        if(b[i].size()==1)  continue;
        for(int j:b[i]) ins(pii(bk[j],j));
        priority_queue<pii>().swap(pq);
    }
    for(int i=2;i<=n;i++){
        for(int j=0;j<a[i].size()&&j<a[i-1].size();j++){
            pii x=pii(bk[a[i-1][j]],a[i-1][j]),y=pii(bk[a[i][j]],a[i][j]);
            if(x>y) exit(puts("No")&0);
            else if(x<y)    break;
        }
    }
    puts("Yes");
    printf("%d\n",count(bk+1,bk+m+1,false));
    for(int i=1;i<=m;i++)if(!bk[i])printf("%d ",i);puts("");
}