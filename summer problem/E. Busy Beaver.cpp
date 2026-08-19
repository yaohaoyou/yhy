#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){x=max(x,y);}
const int maxn=2e5+10;
int n;ll m;
vector<int> a[maxn],b[maxn];
struct node{
    ll lim,ad;int i,j;
    node(ll _x=0,ll _y=0,int _z=0,int _w=0){lim=_x;ad=_y;i=_z;j=_w;}
    bool operator<(const node& y)const{return lim> y.lim;}
};
int p[maxn];
priority_queue<node> q;
void matt(int _cases){
    while(!q.empty())   q.pop();
    for(int i=1;i<=n;i++)   a[i].clear(),b[i].clear(),p[i]=-1;
    scanf("%d%lld",&n,&m);
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        for(int j=1;j<=x;j++){int y;scanf("%d",&y);a[i].eb(y);}
        for(int j=1;j<=x;j++){int y;scanf("%d",&y);b[i].eb(y);}
        ll now=0,s=0,mx=0;
        for(int j=0;j<x;j++){
            gmx(mx,a[i][j]-s);s+=b[i][j]-a[i][j];
            if(s>=0)    q.ep(mx,s,i,j),s=0;
        }
    }
    while(!q.empty()){
        if(m>=q.top().lim)   m+=q.top().ad,gmx(p[q.top().i],q.top().j);
        else    break;
        q.pop();
    }
    pii ans=pii(0,-1);
    for(int i=1;i<=n;i++){
        ll now=m;
        for(int j=0;j<a[i].size();j++){
            if(j>p[i]){
                if(now<a[i][j])    break;
                now-=a[i][j]-b[i][j];
            }
            gmx(ans,pii(j+1,-i));
        }
    }
    printf("%d %d\n",ans.fi,-ans.se);
}
int main(){mems(p,-1);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}