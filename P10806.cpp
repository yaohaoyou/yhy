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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e5+10;
int n,m;
int a[maxn],b[maxn];
set<int> st;
bool out[maxn],c[maxn];
int lst[maxn];
bool check(int x){
    mems(lst,0);mems(c,0);
    int j=0;
    for(int i=1;i<=n;i++){
        out[i]=1;
        while(j<m&&b[j+1]<a[i]){
            j++;
            if(a[i]-x>b[j]) return false;
            if(!lst[i]) lst[i]=j;
            out[i]=0;
        }
        if(i>1&&!out[i]&&b[lst[i-1]]>=a[i]-x){
            c[i]=true;
            while(j<m&&b[j+1]<=a[i-1]+x)  j++;
        }
        if(out[i]){
            while(j<m&&b[j+1]<=a[i]+x)  j++;
        }
        // if(x==327562297)printf("%d %d %d %d %d\n",out[i],j,c[i],a[i],b[j]);
    }
    for(int i=n;i;i--)if(c[i])out[i-1]=1,c[i]=c[i-1]=0;
    return j==m;
}
int main(){
    a[0]=-1e9;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),st.ep(a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    {int M=0;for(int i=1;i<=m;i++)if(!st.count(b[i]))b[++M]=b[i];m=M;}
    int l=0,r=1e9,ans=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else l=mid+1;
    }
    printf("%d\n",ans);
    if(~ans){
        check(ans);
        for(int i=1;i<=n;i++)putchar(out[i]?'R':'L');
    }
}