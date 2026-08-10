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
int n,k,beg,c0,c1,cq;
char s[maxn];int sum[maxn];
int b[maxn];
int dp[maxn];
vector<pii> v;
void DP(){
    int s1=0,s2=0;
    for(int i=1;i<=k;i++){
        s1+=b[i];s2+=2;
        dp[c1+s1]=min(dp[c1+s1],beg-s2);
    }
}
void matt(){
    v.clear();
    for(int i=0;i<=n;i++)   dp[i]=0x3f3f3f3f;
    scanf("%d%s",&n,s+1);
    c0=count(s+1,s+n+1,'0'),c1=count(s+1,s+n+1,'1'),cq=count(s+1,s+n+1,'?');
    for(int i=1;i<=n;i++)   sum[i]=sum[i-1]+(s[i]=='?');
    int lst=0;k=0;
    for(int i=1;i<=n;i++){
        if(s[i]=='1'){
            if(lst!=-1&&sum[i]!=sum[lst])   b[++k]=sum[i]-sum[lst],v.eb(lst+1,i);
            lst=i;
        }
        else if(s[i]=='0')lst=-1;
    }
    beg=1;
    for(int i=2;i<=n;i++)
        if((s[i]=='1')+(s[i-1]=='1')==1)    beg++;
    sort(b+1,b+k+1);dp[c1]=beg;DP();
    int en=0;
    for(int i=1;i<=n;i++)   if(dp[i]!=dp[n+1])  en=i;
    for(int i=1;i<=en;i++)  dp[i]=min(dp[i],dp[i-1]);

    for(pii x:v)for(int i=x.fi;i<=x.se;i++)if(s[i]=='?')s[i]='1';
    k=0;int ss=0;
    for(int i=1;i<=n;i++){
        if(s[i]!='?')   continue;
        int j=i;
        while(s[j]=='?')    j++;j--;
        if(((s[i-1]=='0')+(s[j+1]=='0'))==1)  ss+=j-i+1;
        else    b[++k]=j-i+1;
        i=j;
    }
    sort(b+1,b+k+1,greater<int>());
    for(int i=en+1;i<=en+ss;i++)  dp[i]=dp[i-1];
    int p=en+ss;
    for(int i=1;i<=k;i++){
        dp[p+1]=dp[p]+2;p++;
        while(--b[i])   dp[p+1]=dp[p],p++;
    }
    for(int i=0;i<c1;i++)   printf("-1 ");
    for(int i=c1;i+c0<=n;i++)   printf("%d ",dp[i]);
    for(int i=n-c0+1;i<=n;i++)  printf("-1 ");
    puts("");
}
int main(){mems(dp,0x3f);int T;scanf("%d",&T);while(T--)matt();}