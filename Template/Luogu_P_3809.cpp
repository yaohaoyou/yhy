//  P3809 【模板】后缀排序
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+10;
char s[maxn];
int n,m;
int id[maxn],sa[maxn],oldrnk[maxn<<1],rnk[maxn<<1],cnt[maxn];
int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    m=127;
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
        memcpy(id,sa,sizeof(id));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)   ++cnt[rnk[id[i]+w]];
        for(int i=1;i<=m;i++)   cnt[i]+=cnt[i-1];
        for(int i=n;i;i--)  sa[cnt[rnk[id[i]+w]]--]=id[i];

        // 对 rnk[sa[i]] 排序
        memcpy(id,sa,sizeof(id));
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++)   ++cnt[rnk[id[i]]];
        for(int i=1;i<=m;i++)   cnt[i]+=cnt[i-1];
        for(int i=n;i;i--)  sa[cnt[rnk[id[i]]]--]=id[i];

        memcpy(oldrnk,rnk,sizeof(rnk));
        for(int p=0,i=1;i<=n;i++){
            if(oldrnk[sa[i]]==oldrnk[sa[i-1]]&&oldrnk[sa[i]+w]==oldrnk[sa[i-1]+w])
                rnk[sa[i]]=p;
            else    rnk[sa[i]]=++p;
        }
    }
    for(int i=1;i<=n;i++)   printf("%d ",sa[i]);
}