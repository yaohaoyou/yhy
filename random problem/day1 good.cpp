#pragma GCC optimize(2,3,"Ofast")
#include<bits/stdc++.h>
#define db double
#define ll long long
#define eb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e7+10;
const db eps=1e-10;
int n,k,ans;
bool vis[maxn];
int bitsum[maxn];
int zhuolie[maxn][10];
int q[maxn],he=1,ta;
inline int calc(int x){
    return bitsum[x];
    // int ret=0;
    // while(x){ret+=x%10;x/=10;}
    // return ret;
}
void bfs(){
    while(he<=ta){
        int u=q[he];he++;
        #pragma unroll(4)
        for(int i=1;i<=zhuolie[u][0];i++){
            int x=zhuolie[u][i];
            if(!vis[x]){vis[x]=true;q[++ta]=x;ans++;}
        }
        #pragma unroll(4)
        for(int i=1;i<=63;i++){
            int x=u+i*k;
            if(x>n) break;
            if(calc(x)^i)  continue;
            if(!vis[x]){vis[x]=true;q[++ta]=x;ans++;}
        }
    }
}
int main(){
    int x;
    scanf("%d%d%d",&n,&x,&k);
    for(int i=0;i*10<=n;i++)
        for(int j=0;j<=9;j++)   bitsum[i*10+j]=bitsum[i]+j;
    for(int i=2;i*i<=n;i++){
        int j=i*i;
        while(true){
            zhuolie[j][++zhuolie[j][0]]=i;
            if(1ll*j*i>n)   break;
            j*=i;
        }
    }
    vis[x]=true;q[++ta]=x;
    ans=1;
    bfs();
    printf("%d\n",ans);
}