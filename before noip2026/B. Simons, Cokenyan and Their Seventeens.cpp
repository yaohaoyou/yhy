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
const int maxn=1e6+10;
bool mem1;
int n,m;
int a[maxn],b[maxn];
int solve(int s0,int s1){
    gmx(s0,0);gmx(s1,0);
    int res=0;
    if(!count(b+1,b+m+1,1)){
        int o=1;
        for(int i=1;i<=m;i++){
            if(s1&&s0)  res+=2,s1--,s0--,o=1;
            else    res++,s0--,o=0;
        }
        if(s1){res+=s1+o;s0--;}
        res+=max(0,s0);
    }
    else if(!s1){
        for(int i=1,o=1;i<=m;i++){
            if(b[i]){
                s0-=o;
                if(i!=m&&!b[i+1])    res+=o+1,i++,o=1;
                else    res+=o+1,o=0;
            }
            else{
                s0-=o;res+=o;
                o=1;
            }
            // printf("%d %d %d\n",b[i],res,o);
        }
        res+=max(0,s0);
    }
    else return 1e9;
    return res;
}
bool mem2;
void matt(int _cases){
    m=0;int s0,s1;
    scanf("%d%d%d",&n,&s0,&s1);
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    int ans=1e9,sum=0;
    {
        int ss=s1;
        for(int i=1;i<=n;i++){
            if((i==n||a[i+1])&&a[i]&&ss){ss--;sum+=2;}
            else    b[++m]=a[i];
        }
        int k=0;
        for(int i=1;i<=m;i++){
            if(a[i]&&ss){ss--;sum+=2;}
            else    b[++k]=b[i];
        }
        m=k;ans=solve(s0,ss)+sum;
    }
    {
        m=sum=0;int _s0=s0,_s1=s1,N=n;
        if(s1)sum+=s1-1,s1=1;
        for(int i=1;i<=n;i++){
            if((i==n||a[i+1])&&a[i]&&s1)    s1--,sum+=2;
            else    b[++m]=a[i];
        }
        // for(int i=1;i<=m;i++)   printf("%d",b[i]);puts("");
        n=0;
        for(int i=1;i<=m;i++){
            if(b[i]&&s0){
                int j=i;while(j<=m&&b[j])j++;
                s0--;sum+=j-i+1;i=j;
            }
            else    b[++n]=b[i];
        }
        m=n;
        gmn(ans,sum+solve(s0,s1));
        s0=_s0;s1=_s1;n=N;
    }
    {
        m=sum=0;
        if(s1)sum+=s1-1,s1=1;
        for(int i=1;i<=n;i++){
            if(i<n&&!a[i]&&s1)  s0--,s1--,sum+=2;
            else    b[++m]=a[i];
        }
        gmn(ans,sum+solve(s0,s1));
    }
    // for(int i=1;i<=m;i++)   printf("%d",b[i]);puts("");
    // printf("%d %d %d\n",ans,s0,s1);
    // debug("s1 = %d %d\n",s1,count(b+1,b+m+1,1));
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}