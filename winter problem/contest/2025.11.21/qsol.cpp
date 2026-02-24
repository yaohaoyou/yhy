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
const int maxn=1.2e6+10;
int n;
int a[maxn];
vector<int> v[maxn];
inline ll sqr(int x){return 4ll*x*x;}
int main(){
    freopen("qsol.in","r",stdin);freopen("qsol.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        v[i].eb(a[i]/2);
        v[i].eb(0);
    }
    for(int i=n+1;i<n+n;i++){
        int x,y;scanf("%d%d",&x,&y);
        ll ans=0;
        if(v[x].size()>v[y].size()) v[x].swap(v[y]);
        for(int j=0,k=0;j+1<v[x].size()&&k<v[y].size();j+=2){
            while(k+1<v[y].size()&&v[y][k+1]>v[x][j])   k+=2;
            while(k+1<v[y].size()&&v[y][k]>=v[x][j+1]){
                ans+=max(0ll,sqr(min(v[x][j],v[y][k]))-sqr(max(v[x][j+1],v[y][k+1])));
                if(k+2>=v[y].size()||v[y][k+2]<v[x][j+1])   break;
                k+=2;
            }
        }
        vector<int> tmp(v[x].size()+v[y].size());
        merge(v[x].begin(),v[x].end(),v[y].begin(),v[y].end(),tmp.begin(),greater<int>());
        for(int j=0;j+1<tmp.size();j++){
            if(tmp[j]==tmp[j+1])    j++;
            else v[i].eb(tmp[j]);
        }
        v[i].eb(0);
        printf("%lld\n",ans);
    }
}