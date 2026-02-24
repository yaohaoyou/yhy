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
const int maxn=4e5+10;
int n,m;
char s[maxn];
int a[maxn],b[maxn];
void matt(){
    scanf("%d%d",&n,&m);n--;m--;
    scanf("%s",s+1);
    int x=1,y=1,c=m-count(s+1,s+n+m+1,'R');
    a[1]=1;
    for(int i=1;i<=n+m;i++){
        bool flag=s[i]=='?';
        if(s[i]=='?'){
            if(c)   s[i]='R',c--;
            else    s[i]='D';
        }
        if(s[i]=='R')    a[++x]=y;
        else    y++;
        if(flag)    s[i]='?';
    }
    ll ans=0;
    c=n-count(s+1,s+n+m+1,'D');
    x=y=1;
    for(int i=1;i<=n+m;i++){
        bool flag=s[i]=='?';
        if(s[i]=='?'){
            if(c)   s[i]='D',c--;
            else    s[i]='R';
        }
        if(s[i]=='R')    b[x++]=y;
        else    y++;
        if(i==n+m) b[x]=y;
        if(flag)    s[i]='?';
    }
    // for(int i=1;i<=m+1;i++) printf("%d %d\n",a[i],b[i]);
    for(int i=1;i<=m+1;i++)   ans+=b[i]-a[i]+1;
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}