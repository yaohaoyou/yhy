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
int n,tp;
char a[maxn],b[maxn];
int pr[maxn],nx[maxn];
inline void era(int x){int p=pr[x],xx=nx[x];pr[xx]=p;nx[p]=xx;}
void matt(int _cases){
    tp=0;
    scanf("%s",a+1);n=strlen(a+1);
    for(int i=1;i<=n;i++){
        if(a[i]^'C'){
            b[++tp]=a[i];
            continue;
        }
        while(tp&&b[tp]=='A')   tp--;
        int x=0;bool flag=false;
        for(int j=tp;j;j--){
            if(b[j]=='C')   break;
            if(b[j]=='A')   x--;
            else    x++;
            if(x==0)    flag=true,x=j;
            if(x<=0) break;
        }
        if(flag)    tp=x-1;
        else    b[++tp]=a[i];
    }
    nx[0]=1;
    for(int i=1;i<=tp;i++)  pr[i]=i-1,nx[i]=i+1;
    int p=1;
    while(nx[p]<=tp){
        if(p<1) p=nx[p];
        else if(b[p]=='A'&&b[nx[p]]=='B')    era(p),era(nx[p]),p=pr[p];
        else    p=nx[p];
    }
    int ans=0;
    for(int i=0;i<=tp;i=nx[i])  ans+=b[i]=='B';
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}