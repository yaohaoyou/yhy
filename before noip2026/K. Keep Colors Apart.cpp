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
const int maxn=2e5+10;
bool mem1;
int n;
struct node{int d,c,w;}a[maxn];
priority_queue<pii> q;
map<int,int> mp,pre;
int in[maxn];
bool mem2;
void matt(int _cases){
    mp.clear();pre.clear();
    for(int i=1;i<=n;i++)   in[i]=0;
    while(!q.empty())   q.pop();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d%d",&a[i].d,&a[i].c,&a[i].w);
    sort(a+1,a+n+1,[&](node x,node y){return x.d<y.d;});
    a[0].d=0;
    int now=1e9,lst=0;ll sum=0,ans=0;
    for(int i=n;i>0;i--){
        if(q.empty())   gmn(now,a[i].d);
        while(i&&a[i].d>=now){
            q.ep(a[i].w,i);
            i--;
        }
        while(now>a[i].d&&!q.empty()){
            if(a[q.top().se].c!=lst) sum+=q.top().fi,lst=a[q.top().se].c,mp[now]=q.top().se,in[q.top().se]=now,q.pop();
            else if(q.size()>1){
                pii x=q.top();q.pop();
                sum+=q.top().fi;lst=a[q.top().se].c;q.pop();
                mp[now]=q.top().se;
                in[q.top().se]=now;
                q.ep(x);
            }
            else lst=0;
            now--;
        }
        i++;
    }
    for(auto [i,j]:mp)  printf("%d %d\n",i,j);
    ans=sum;
    {
        int mn=1e9;
        for(auto [i,j]:mp)gmn(mn,a[j].w),pre[i]=mn;
    }
    for(int i=1;i<=n;i++)if(!in[i]){
        auto it=pre.lower_bound(a[i].d);
        if(it!=pre.begin()) printf("%d %d %d %d\n",a[i].d,a[i].w,prev(it)->fi,prev(it)->se),gmx(ans,sum-(--it)->se+a[i].w);
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}