#include<bits/stdc++.h>
using namespace std;
const int maxn=55;
int n,m,c;
int res=1e9;
int a[maxn],b[maxn][maxn],ans[maxn][maxn];
inline int f(){
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(i<n&&b[i][j]!=b[i+1][j])  cnt++;
            if(j<m&&b[i][j]!=b[i][j+1])  cnt++;
        }
    }
    return cnt;
}
inline void changeans(){
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)   ans[i][j]=b[i][j];
}
inline void init(){
    for(int i=1,k=1,lst=a[k];i<=n;i++){
        for(int j=1;j<=m;j++){
            b[i][j]=k;
            if(!--lst)lst=a[++k];
        }
    }
}
inline int change(int x1,int y1){
    int now=0;
    if(x1>1)    now+=(b[x1][y1]!=b[x1-1][y1]);
    if(x1<n)    now+=(b[x1][y1]!=b[x1+1][y1]);
    if(y1>1)    now+=(b[x1][y1]!=b[x1][y1-1]);
    if(y1<m)    now+=(b[x1][y1]!=b[x1][y1+1]);
    return now;
}
void SA(){
    init();int lst=f();
    double beginT=3000,endT=1e-15,changeT=0.99999;
    int cnt=0;
    for(double T=beginT;T>endT;T*=changeT){
        cnt++;
        int x1=rand()%n+1,y1=rand()%m+1,x2=rand()%n+1,y2=rand()%m+1;
        if(b[x1][y1]==b[x2][y2])continue;
        int now=lst;
        now-=change(x1,y1);
        now-=change(x2,y2);
        swap(b[x1][y1],b[x2][y2]);
        now+=change(x1,y1);
        now+=change(x2,y2);
        if(now<lst||exp((lst-now)/T)*RAND_MAX>rand()){
            if(now<res){changeans();res=now;}
            lst=now;
        }
        else swap(b[x1][y1],b[x2][y2]);
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&c);
    for(int i=1;i<=c;i++){
        scanf("%d",&a[i]);
    }
    // while(clock()<0.1*CLOCKS_PER_SEC){
        srand(time(0)+clock()*rand());
        SA();
    // }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)   printf("%d ",ans[i][j]);
        puts("");
    }
}