#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e6+10;
int n,m='z';
int buc[maxn],sa[maxn],id[maxn],rnk[maxn],nwrnk[maxn],oldrnk[maxn];
int p[maxn];
char s[maxn];
inline void radixsort(){
    mems(buc,0);
    for(int i=1;i<=n;i++)   buc[p[i]]++;
    for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
    for(int i=n;i;i--)      nwrnk[id[i]]=buc[p[i]]--;  // 对于 p[i]=p[j],按 id[i],id[j] 排序
    for(int i=1;i<=n;i++)   sa[nwrnk[i]]=i;
}
int main(){
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)   id[i]=i;
    for(int i=1;i<=n;i++)   p[i]=rnk[i]=s[i];
    memc(oldrnk,rnk);
    radixsort();
    for(int i=1,p=0;i<=n;i++){
        if(oldrnk[sa[i]]==oldrnk[sa[i-1]])  rnk[sa[i]]=p;
        else    rnk[sa[i]]=++p;
    }
    for(int w=1;w<=n;w<<=1,m=n){
        memc(oldrnk,rnk);
        memc(id,sa);
        for(int i=1;i<=n;i++)   p[i]=rnk[sa[i]+w];
        radixsort();
        memc(id,sa);
        for(int i=1;i<=n;i++)   p[i]=rnk[sa[i]];
        radixsort();
        for(int i=1,p=0;i<=n;i++){
            if(oldrnk[sa[i]]==oldrnk[sa[i-1]]&&oldrnk[sa[i]+w]==oldrnk[sa[i-1]+w])  rnk[sa[i]]=p;
            else    rnk[sa[i]]=++p;
        }
    }
    for(int i=1;i<=n;i++)   printf("%d ",sa[i]);
}