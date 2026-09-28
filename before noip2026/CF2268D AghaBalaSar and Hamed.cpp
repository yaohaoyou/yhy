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
int a[maxn],nx[maxn],pre[maxn];
ll f[maxn];int cnt[maxn],buc[maxn];
stack<int> stk;
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    while(!stk.empty()) stk.pop();
    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]<a[i]) stk.pop();
        nx[i]=stk.empty()?0:stk.top();
        stk.ep(i);
    }
    for(int i=1;i<=n;i++)   pre[i]=max(pre[i-1],nx[i]);
    int now=0;
    for(int i=1;i<=n;i++)   buc[nx[i]]++;
    ll ans=1ll*n*(n-1)/2;
    for(int i=n;i;i--){
        f[i]=cnt[i]=0;
        int p=pre[i];
        if(p>i){
            if(nx[i])   f[i]+=(nx[i]-i-1)*2,cnt[i]+=nx[i]-i-1;
            int w=now-(nx[i]&&buc[nx[i]])-(p!=nx[i]&&p&&buc[p]);
            // printf("w = %d\n",w);
            cnt[i]+=w;f[i]+=w*2;
            if(nx[nx[i]]&&nx[nx[i]]<p&&!buc[nx[nx[i]]])  f[i]+=2,cnt[i]++;
            w=p-i-1-(nx[i]!=p);
            // printf("w = %d\n",w);
            f[i]+=(w-cnt[i])*3;cnt[i]=w;
            if(nx[i]==p)    f[i]+=f[p]+cnt[p]+1,cnt[i]+=cnt[p]+1;
            else{
                f[i]+=f[p]+(cnt[p]+1)*2,cnt[i]+=cnt[p]+1;
                if(nx[i])   f[i]++,cnt[i]++;
            }
        }
        buc[nx[i]]--;if(nx[i]&&!buc[nx[i]])now--;
        now+=bool(buc[i]);
        ans+=f[i];
        // printf("f[%d] = %d %d %d\n",i,f[i],cnt[i],now);
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}