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
char s[maxn];
int id[maxn],sa[maxn],height[maxn],oldrnk[maxn<<1],rnk[maxn<<1],cnt[maxn];
void SuffixSort(){
    int m=128;
    for(int i=1;i<=n;i++){
        rnk[i]=s[i];
        cnt[rnk[i]]++;
    }
    for(int i=1;i<=m;i++)   cnt[i]+=cnt[i-1];
    for(int i=n;i;i--){
        sa[cnt[rnk[i]]]=i;
        cnt[rnk[i]]--;
    }
    memcpy(oldrnk,rnk,sizeof(rnk));
    for(int p=0,i=1;i<=n;i++){
        if(oldrnk[sa[i]]==oldrnk[sa[i-1]])  rnk[sa[i]]=p;
        else    rnk[sa[i]]=++p;
    }
    for(int w=1;w<n;w<<=1,m=n){
        // 对 rnk[sa[i]]+w 排序
        memc(id,sa);mems(cnt,0);
        for(int i=1;i<=n;i++)   ++cnt[rnk[id[i]+w]];
        for(int i=1;i<=m;i++)   cnt[i]+=cnt[i-1];
        for(int i=n;i;i--)  sa[cnt[rnk[id[i]+w]]--]=id[i];
        // 对 rnk[sa[i]] 排序
        memc(id,sa);mems(cnt,0);
        for(int i=1;i<=n;i++)   ++cnt[rnk[id[i]]];
        for(int i=1;i<=m;i++)   cnt[i]+=cnt[i-1];
        for(int i=n;i;i--)  sa[cnt[rnk[id[i]]]--]=id[i];
        memcpy(oldrnk,rnk,sizeof(rnk));
        for(int p=0,i=1;i<=n;i++){
            if(oldrnk[sa[i]]==oldrnk[sa[i-1]]&&oldrnk[sa[i]+w]==oldrnk[sa[i-1]+w])  rnk[sa[i]]=p;
            else    rnk[sa[i]]=++p;
        }
    }
}
int main(){
    scanf("%d%s",&n,s+1);
    if(count(s+1,s+n+1,s[1])==n)    return printf("%lld\n",1ll*(n-1)*(n+2)),0;
    SuffixSort();
    for(int i=1,k=0;i<=n;i++){
        if(rnk[i]==1)	continue;
        if(k)	--k;
        while(i+k<=n&&sa[rnk[i]-1]+k<=n&&s[i+k]==s[sa[rnk[i]-1]+k])	k++;
        height[rnk[i]]=k;
    }
    ll ans=1ll*n*(n+1)/2;
    for(int i=1;i<=n;i++)   ans-=height[rnk[i]];
    printf("%lld\n",ans+1ll*n*(n+1)/2-2);
}