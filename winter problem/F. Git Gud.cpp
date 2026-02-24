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
const int maxn=1e6+10,B=63;
int n;
int a[maxn],b[maxn];
vector<pii> ans;
vector<int> v[maxn];
int main(){
    scanf("%d",&n);
    fill(b+1,b+n+1,1);
    int i=B;
    for(;i/B<=n;i*=B){
        // printf("i = %d\n",i);
        for(int j=1;j<=n;j++)if(b[j])v[j%i].eb(j);
        for(int j=1;j<i;j++){
            sort(v[j].begin(),v[j].end(),greater<int>());
            for(int k:v[j])   ans.eb(k,i/B),b[k+i/B]+=b[k],b[k]=0;
            v[j].clear();
        }
        v[0].clear();
    }
    i/=B;
    printf("%d\n",ans.size());
    int sum=0;
    pii lst=pii(1e9,0);
    for(pii i:ans){
        if(i.fi<=lst.fi)    sum+=i.se;
        else sum+=i.se+1000;
        printf("%d %d\n",i.fi,i.se);
        lst=i;
    }
    // printf("sum = %d\n",sum);
    // for(int i=1;i<=n;i++)if(b[i])printf("%d ",i);puts("");
}