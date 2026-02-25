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
const int maxn=1e6+10;
int n;
int a[maxn],nx[maxn],c[maxn];
priority_queue<int,vector<int>,greater<int>> v[maxn];
bool vis[maxn];
int main(){
    freopen("merge.in","r",stdin);freopen("merge.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        nx[i]=i+1;c[i]=1;
        v[a[i]].ep(i);
    }
    vector<int> clr,vec;
    int ans=0;
    for(int o=1;o<=n+n;o++){
        clr.clear();
        if(!v[o].empty())   ans=o;
        while(!v[o].empty()){
            int i=v[o].top();v[o].pop();
            if(vis[i])  continue;
            int cnt=0,lst=0;vec.clear();
            for(int j=i;j<=n&&a[j]==o;j=nx[j]){vis[j]=true;clr.eb(j);lst=j;cnt+=c[j];}
            if(cnt<2)   continue;
            if(cnt&1){
                a[i]=o+1;c[i]=cnt>>1;nx[i]=n+1;
                a[lst]=o+1;c[lst]=cnt>>1;
                v[o+1].ep(i);v[o+1].ep(lst);
            }
            else{a[i]=o+1;c[i]=cnt>>1;nx[i]=nx[lst];v[o+1].ep(i);}
        }
        for(int i:clr)vis[i]=false;
    }
    printf("%d\n",ans);
}