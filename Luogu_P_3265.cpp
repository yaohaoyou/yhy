#include<cstdio>
#include<algorithm>
#include<math.h>
#define db double
using namespace std;
const int maxn=510;
const db eps=1e-6;
int n,m;
struct node{
    long db a[maxn];
    int c;
}b[maxn];
int p[maxn];
int ans1,ans2;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)   scanf("%Lf",&b[i].a[j]);
    for(int i=1;i<=n;i++)    scanf("%d",&b[i].c);
    sort(b+1,b+n+1,[&](node x,node y){return x.c<y.c;});
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(fabs(b[i].a[j])<eps)  continue;
            if(!p[j]){ans1++;ans2+=b[i].c;p[j]=i;break;}
            db tmp=b[i].a[j]/b[p[j]].a[j];
            for(int k=j;k<=m;k++)   b[i].a[k]-=tmp*b[p[j]].a[k];
        }
    }
    printf("%d %d\n",ans1,ans2);
}