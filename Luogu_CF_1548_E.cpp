#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=6e5+10;
int n,m,X;
int a[maxn],b[maxn];
int la[maxn],ra[maxn],lb[maxn],rb[maxn];
stack<int> stk;
void Preprocess(){
    while(!stk.empty())stk.pop();

    for(int i=1;i<=n;i++){
        while(!stk.empty()&&a[stk.top()]>a[i])  stk.pop();
        if(!stk.empty())    la[i]=stk.top();
        else    la[i]=0;
        stk.push(i);
    }
    while(!stk.empty())stk.pop();

    for(int i=n;i;i--){
        while(!stk.empty()&&a[stk.top()]>=a[i])  stk.pop();
        if(!stk.empty())    ra[i]=stk.top();
        else    ra[i]=0;
        stk.push(i);
    }
    while(!stk.empty())stk.pop();
    
    for(int i=1;i<=m;i++){
        while(!stk.empty()&&b[stk.top()]>b[i])  stk.pop();
        if(!stk.empty())    lb[i]=stk.top();
        else    lb[i]=0;
        stk.push(i);
    }
    while(!stk.empty())stk.pop();
    
    for(int i=m;i;i--){
        while(!stk.empty()&&b[stk.top()]>=b[i])  stk.pop();
        if(!stk.empty())    rb[i]=stk.top();
        else    rb[i]=0;
        stk.push(i);
    }
}
struct ST{
    int len;
    int Log[maxn];
    int mx[20][maxn],nx[20][maxn];
    void build(int s[]){
        for(int i=2;i<=len;i++) Log[i]=Log[i/2]+1;
        for(int i=1;i<=len;i++) mx[0][i]=s[i],nx[0][i]=i+1;
        for(int i=1;i<20;i++){
            for(int j=1;j<=len;j++){
                nx[i][j]=nx[i-1][nx[i-1][j]];
                mx[i][j]=max(mx[i-1][j],mx[i-1][nx[i-1][j]]);
            }
        }
    }
    int query(int l,int r){if(!l||!r)return maxn-15;int k=Log[r-l+1];return max(mx[k][l],mx[k][r-(1<<k)+1]);}
}st[2];
namespace BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=maxn-10){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x-=lowbit(x);}return res;}
}
int ma[maxn],mb[maxn];
int pos[maxn],p[maxn];
ll ans;
int main(){
    scanf("%d%d%d",&n,&m,&X);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    st[0].len=n;st[0].build(a);
    st[1].len=m;st[1].build(b);
    Preprocess();
    for(int i=1;i<=n;i++){
        ma[i]=min(st[0].query(la[i],i),st[0].query(i,ra[i]));
        p[i]=i;
    }
    for(int i=1;i<=m;i++){
        mb[i]=min(st[1].query(lb[i],i),st[1].query(i,rb[i]));
        mb[i]=X-mb[i];
        pos[i]=i;
    }
    // for(int i=1;i<=n;i++)   printf("%d ",ma[i]);puts("");
    // for(int i=1;i<=m;i++)   printf("%d ",-mb[i]+X);puts("");
    sort(pos+1,pos+m+1,[&](int x,int y){return mb[x]<mb[y];});
    sort(p+1,p+n+1,[&](int x,int y){return a[x]<a[y];});
    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=m;j++){
    //         if(a[i]<=X-b[j]&&a[i]>mb[j]&&ma[i]>X-b[j]) printf("res = (%d,%d)\n",a[i],b[j]);
    //     }
    // }
    for(int i=1,j=1;i<=n;i++){
        while(j<=m&&mb[pos[j]]<a[p[i]]){
            if(X-b[pos[j]]>0){
                BIT::add(max(1,X-b[pos[j]]),1);
                // printf("%d in %d\n",X-b[pos[j]],j);
            }
            j++;
        }
        ans+=BIT::que(ma[p[i]]-1)-BIT::que(a[p[i]]-1);
        // printf("%d [%d,%d]\n",ans,a[i],ma[i]-1);
    }
    printf("%lld\n",ans);
}