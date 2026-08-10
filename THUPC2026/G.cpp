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
const int maxn=5e5+10;
int n;
int c[maxn];
void solve(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%1d",&c[i]);
    int ans=1e9;
    for(int i=0;i<(1<<n);i++){
        int x=0,y=0;
        for(int j=0;j<n;j++){
            if(i&(1<<j))    x=x<<1|c[j+1];
            else y=y<<1|c[j+1];
        }
        if(x+y==8) printf("%d %d\n",x,y);
        ans=min(ans,x+y);
    }
    printf("%d\n",ans);
    if(!ans)    return puts("0"),void();
    vector<int> v;while(ans)v.eb(ans&1),ans>>=1;
    reverse(v.begin(),v.end());
    for(int i:v)    printf("%d",i);puts("");
}
void matt(){
    scanf("%d",&n);
    int a=0,b=0;
    vector<int> v1,v2;v1.clear();v2.clear();
    for(int i=1;i<=n;i++)   scanf("%1d",&c[i]);
    a=accumulate(c+1,c+n+1,0);
    if(!a)  return puts("0"),void();
    pii p=pii(1e9,1e9);
    for(int i=n;i;i--){
        if(c[i])    a--;
        p=min(p,pii(max(a,n-i+1),i));
    }
    for(int i=n;i>=p.se;i--)  v2.eb(c[i]);
    for(int i=p.se-1;i;i--)if(c[i])v1.eb(c[i]);
    // for(int i:v1)printf("%d",i);puts("");
    // for(int i:v2)printf("%d",i);puts("");
    // reverse(v1.begin(),v1.end());
    // reverse(v2.begin(),v2.end());
    while(v1.size()<v2.size())  v1.eb(0);
    while(v1.size()>v2.size())  v2.eb(0);
    vector<int> ans;ans.clear();
    int k=0;
    for(int i=0,j=0;i<v1.size()&&j<v2.size();i++,j++){
        int out=v1[i]+v2[j]+k;
        if(out>1) k=1,out-=2;
        else k=0;
        ans.eb(out);
    }
    if(k)  ans.eb(k);
    reverse(ans.begin(),ans.end());
    k=0;
    while(k+1<ans.size()&&!ans[k])  k++;
    while(k<ans.size()) printf("%d",ans[k++]);puts("");
}
void data(){
    srand(time(0));
    n=5;
    int T=100;
    printf("%d\n",T);
    while(T--){
        printf("%d\n",n);
        for(int i=1;i<=n;i++)   printf("%d",rand()&1);
        puts("");
    }
    exit(0);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}