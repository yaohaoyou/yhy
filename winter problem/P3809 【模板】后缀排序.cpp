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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e6+10;
int n,m='z';
char a[maxn];
int sa[maxn],rk[maxn],y[maxn],buc[maxn],ht[maxn];
void build_ht(){
    for(int i=1,k=0;i<=n;i++){
        if(rk[i]==1){k=0;continue;}
        if(k)   k--;
        int j=sa[rk[i]-1];
        while(i+k<=n&&j+k<=n&&a[i+k]==a[j+k]) k++;
        ht[rk[i]]=k;
    }
    for(int i=1;i<=n;i++)   printf("%d ",ht[i]);
}
int main(){
    scanf("%s",a+1);n=strlen(a+1);
    for(int i=1;i<=n;i++)   buc[rk[i]=a[i]]++;
    for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
    for(int i=n;i;i--)  sa[buc[rk[i]]--]=i;
    for(int w=1;w<=n;w<<=1){
        int p=0;
        for(int i=n-w+1;i<=n;i++)   y[++p]=i;
        for(int i=1;i<=n;i++)if(sa[i]>w)y[++p]=sa[i]-w;
        mems(buc,0);
        for(int i=1;i<=n;i++)   buc[rk[i]]++;
        for(int i=1;i<=m;i++)   buc[i]+=buc[i-1];
        for(int i=n;i;i--)  sa[buc[rk[y[i]]]--]=y[i];
        memc(y,rk);
        rk[sa[1]]=m=1;
        for(int i=2;i<=n;i++){
            if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+w]==y[sa[i-1]+w])  rk[sa[i]]=m;
            else    rk[sa[i]]=++m;
        }
        if(m==n)    break;
    }
    for(int i=1;i<=n;i++)   printf("%d ",sa[i]);puts("");
    // build_ht();
}