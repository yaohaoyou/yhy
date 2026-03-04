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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn];
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    iota(a+1,a+n+1,1);
    int ans=0;
    do{
        int mx1=0,mx2=0;bool flag=true;
        for(int i=1;i<=n;i++)if(b[i]^a[i]&&~b[i]){flag=false;break;}
        if(!flag)   continue;
        for(int i=1;i<=n;i++){
            if(mx1>a[i])    gmx(mx2,a[i]);
            if(mx2>a[i]){flag=false;break;}
            gmx(mx1,a[i]);
        }
        if(!flag)   continue;
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(a[j]<a[i])   continue;
                for(int k=j+1;k<=n;k++){
                    if(a[k]>a[i])   continue;
                    for(int l=k+1;l<=n;l++){
                        if(a[l]>a[k]&&a[l]<a[i]){flag=false;break;}
                    }
                }
            }
        }
        ans+=flag;
    }while(next_permutation(a+1,a+n+1));
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}