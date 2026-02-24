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
const int maxn=1e6+10,n=20;
int a[maxn],b[maxn],c[maxn];
void print(int x){printf("%d\n",x);fflush(stdout);}
void print01(int x,int y){return;printf("%d %d\n",x,y);fflush(stdout);}
void matt(int _cases){
    int x,s=0;scanf("%d",&x);
    for(int j=1;j<=n;j++)  scanf("%d",&c[j]),s^=c[j];
    if(x^20)    print(bool(s&(1<<x-1)));
    else{
        s=0;
        for(int j=1;j<n;j++)    s^=bool(c[j]&(1<<j-1));
        print(s);
    }
}
void data(){
    scanf("%*d");
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int sum=0;for(int i=1;i<=n;i++)   sum^=a[i];printf("s = %d\n",sum);
    puts("1");
    iota(c+1,c+n+1,1);
    random_shuffle(c+1,c+n+1);
    for(int i=1;i<=n;i++){
        printf("%d ",c[i]);
        for(int j=1;j<=n;j++)printf("%d ",j==c[i]?0:a[j]);
        puts("");
    }
    if(1){
        for(int i=1;i<=n;i++){
            int x,y;scanf("%d%d",&x,&y);
            b[y]=x;
        }
        printf("%d\n",n);
        random_shuffle(c+1,c+n+1);
        for(int i=1;i<=n;i++){
            printf("%d ",c[i]);
            for(int j=1;j<=n;j++)printf("%d ",j==c[i]?0:a[j]);
            for(int j=1;j<=n;j++)printf("%d",b[j]);
            puts("");
        }
        printf("ans : ");for(int i=1;i<=n;i++)   printf("%d ",a[c[i]]);puts("");
    }
    exit(0);
}
int main(){
    // data();
    int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
    int K;scanf("%d",&K);
    for(int i=1;i<=K;i++){
        int x;scanf("%d",&x);
        for(int j=1;j<=n;j++)   scanf("%d",&c[j]);
        for(int j=1;j<=n;j++)   scanf("%1d",&a[j]);
        if(x^20){
            int s=a[n];
            for(int j=1;j<n;j++)    s^=bool(c[j]&(1<<j-1));
            c[x]=(s<<x-1);
            s=0;
            for(int j=1;j<n;j++){
                bool o=c[j]&(1<<j-1);
                s^=((a[j]^o)<<j-1);
            }
            // printf("s = %d\n",s);
            c[x]=0;
            for(int j=1;j<=n;j++)   s^=c[j];
            print(s);
        }
        else{
            int s=0;
            for(int j=1;j<n;j++){
                bool o=c[j]&(1<<j-1);
                s^=((a[j]^o)<<j-1);
            }
            // printf("s = %d\n",s);
            for(int j=1;j<=n;j++)   s^=c[j];
            print(s);
        }
    }
    // while(true);
}