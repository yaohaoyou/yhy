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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=200;
int n;
int a[maxn],en[maxn],f[maxn];
bool bk[10];
bool mem2;
int main(){
    freopen("mex.in","r",stdin);freopen("mex.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    if(!count(a+1,a+n+1,0)) return puts("0"),0;
    int k=0;
    for(int i=n;i;i--){
        f[i]=k;
        bk[a[i]]=true;
        if(count(bk,bk+10,1)==10)   en[++k]=i,mems(bk,0);
    }
    int len=k+1;
    if(k){
        mems(bk,0);
        for(int i=1;i<en[k];i++)bk[a[i]]=true;
        if(count(bk+1,bk+10,1)==9)  len++;
    }
    // for(int i=1;i<=n;i++)   printf("%d ",f[i]);puts("");
    // printf("k = %d\n",k+1);
    int now=0;
    for(int i=1;i<=len;i++){
        // printf("now = %d\n",now);
        int bef=now;
        for(int c=(i==1);c<=9;c++){
            bool fl=false;
            for(int j=bef+1;j<=n;j++)if(a[j]==c){
                if(f[j]<len-i) now=j;
                else    fl=true;
                break;
            }
            if(!fl){
                printf("%d",c);
                break;
            }
            assert(c^9);
        }
    }
}