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
const int maxn=2e5+10,maxm=22,maxM=(1<<20)+10;
int n,m,M;ll k;
char s[maxm];
ll a[maxM],b[maxM];
void FWT(){
    for(int i=0;i<m;i++)
        for(int j=0;j<=M;j++)
            if(!(j&(1<<i))){
                ll x=a[j],y=a[j^(1<<i)];
                a[j]=x+y;a[j^(1<<i)]=x-y;
            }
}
void IFWT(){
    for(int i=0;i<m;i++)
        for(int j=0;j<=M;j++)
            if(!(j&(1<<i))){
                ll x=a[j],y=a[j^(1<<i)];
                a[j]=(x+y)/2,a[j^(1<<i)]=(x-y)/2;
            }
}
int main(){
    scanf("%d%d%lld",&n,&m,&k);M=(1<<m)-1;
    for(int i=1;i<=n;i++){
        scanf("%s",s+1);
        int sta=0;
        for(int j=1;j<=m;j++,sta<<=1)   sta|=(s[j]=='A');
        sta>>=1;
        a[sta]++;
    }
    FWT();
    for(int i=0;i<=M;i++)   a[i]=a[i]*a[i];
    IFWT();
    a[0]=0;
    ll sum=0;
    for(int i=0;i<=M;i++)   b[i]=a[i]>>1,sum+=b[i];
    for(int i=0;i<m;i++)for(int j=0;j<=M;j++)if(j&(1<<i))b[j]+=b[j^(1<<i)];
    int ans=0;
    b[0]=0;
    for(int i=0;i<=M;i++)   ans+=sum-b[i]>=k;
    printf("%d\n",ans);
}