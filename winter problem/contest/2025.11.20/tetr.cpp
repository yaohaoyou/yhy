#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pdi pair<int,db>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define db double
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
int n,ans;
char op[maxn];
int a[maxn],b[maxn];
int v[maxn],vl;
mt19937 Matt(time(0));
inline int rd(){return abs((int)Matt());}
inline db sqr(db x){return x*x;}
inline db calc(int x,int y,int z){db avg=(x+y+z)/3.0;return sqr(x-avg)+sqr(y-avg)+sqr(z-avg);}
inline int f(){
    int p=0;
    int b[3]={0,0,0};
    db s;
    for(int i=1;i<=n;i++){
        if(op[i]=='A')   b[a[i]]+=2;
        else b[0]++,b[1]++;
        p+=(b[0]==b[1]&&b[1]==b[2]);
    }
    return p;
}
void changeans(){for(int i=1;i<=n;i++)b[i]=a[i];}
void SA(){
    double beginT=3000,endT=1e-4,delT=0.999;
    int b[3]={0,0,0};
    for(int i=1;i<=n;i++){
        if(op[i]=='A'){
            if(i<n&&op[i+1]=='A'&&b[0]<b[2])   b[0]+=2,b[1]+=2,a[i]=0,a[i+1]=1,i++;
            else    b[2]+=2,a[i]=2;
        }
        else    b[0]++,b[1]++;
    }
    int lst=f();if(lst>ans)changeans(),ans=lst;
    for(db T=beginT;T>endT;T*=delT){
        int x=v[rd()%vl+1],ax=a[x];
        if(!a[x]){
            if(a[x+2]!=2)   continue;
            a[x]=2;a[x+1]=0;a[x+2]=1;
        }
        else if(a[x]==1)    a[x]=a[x-1]=2;
        else if(a[x]==2){
            if(a[x+1]!=2)   continue;
            a[x]=0;a[x+1]=1;
        }
        int now=f();
        if(now>lst||exp((now-lst)/T)*INT_MAX>rd()){
            if(now>ans){changeans();ans=now;}
            lst=now;
        }
        else{
            if(!ax) a[x]=0,a[x+1]=1,a[x+2]=2;
            else if(ax==1)  a[x-1]=0,a[x]=1;
            else if(ax==2)  a[x]=a[x+1]=2;
        }
    }
}
namespace allA{
    bool check(){for(int i=1;i<=n;i++)if(op[i]=='B')return false;return true;}
    void solve(){
        printf("%d\n",n/3);
        for(int i=1;i<=n;i++)   printf("%d",i%3+1);puts("");
    }
}
namespace allB{
    bool check(){for(int i=1;i<=n;i++)if(op[i]=='A')return false;return true;}
    void solve(){
        puts("0");
        for(int i=1;i<=n;i++)   printf("1");puts("");
    }
}
void matt(int _cases){
    double sta=clock();ans=0;
    scanf("%d%s",&n,op+1);
    if(allA::check())   return allA::solve();
    if(allB::check())   return allB::solve();
    for(int i=1;i<=n;i++){
        if(op[i]=='B')  a[i]=-1;
        else v[++vl]=i;
    }
    while((clock()-sta)/CLOCKS_PER_SEC<0.07) SA();
    printf("%d\n",ans);
    for(int i=1;i<=n;i++){
        if(!~a[i])  a[i]=1;
        else a[i]++;
        printf("%d",a[i]);
    }
    puts("");
}
int main(){freopen("tetr.in","r",stdin);freopen("tetr.out","w",stdout);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}