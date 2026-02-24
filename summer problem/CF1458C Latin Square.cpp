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
const int maxn=1010,maxq=1e5+10,maxN=maxn*maxn;
int n,q;
int a[maxN][3],out[maxn][maxn];
char s[maxq];
void matt(int _cases){
    scanf("%d%d",&n,&q);
    int cnt=0;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++){int x;scanf("%d",&x);a[++cnt][0]=i;a[cnt][1]=j;a[cnt][2]=x;}
    scanf("%s",s+1);
    int p[3]={0,0,0},b[3]={0,1,2};
    for(int i=1;i<=q;i++){
        if(s[i]=='U')   p[0]--;
        if(s[i]=='D')   p[0]++;
        if(s[i]=='R')   p[1]++;
        if(s[i]=='L')   p[1]--;
        if(s[i]=='I')   swap(b[1],b[2]),swap(p[1],p[2]);
        if(s[i]=='C')   swap(b[0],b[2]),swap(p[0],p[2]);
    }
    p[0]%=n;p[1]%=n;p[2]%=n;
    for(int i=1;i<=cnt;i++){
        int x=a[i][b[0]],y=a[i][b[1]],w=a[i][b[2]];
        (x+=p[0]+n)%=n;if(!x)x=n;
        (y+=p[1]+n)%=n;if(!y)y=n;
        (w+=p[2]+n)%=n;if(!w)w=n;
        out[x][y]=w;
    }
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%d ",out[i][j]);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}