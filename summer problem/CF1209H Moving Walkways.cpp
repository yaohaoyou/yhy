#include<bits/stdc++.h>
#define db double
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pdd pair<db,db>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
const db eps=1e-10;
int n,L;
db ans;
priority_queue<pdd> q;
void add(int len,db v){
    db E=len/(v+1);
    ans+=len/(v+1);
    if(v==1)    q.ep(v,1e9);
    else q.ep(v,len/(v+1)+len/(v-1));
    while(E>eps){
        pdd x=q.top();q.pop();
        db del=min(E,x.se);
        E-=del;x.se-=del;ans+=del/(x.fi);
        if(x.se>eps)    q.ep(x.fi,x.se);
    }
}
int main(){
    scanf("%d%d",&n,&L);
    db lst=0;
    for(int i=1;i<=n;i++){
        int x,y;db s;scanf("%d%d%lf",&x,&y,&s);
        add(x-lst,1);add(y-x,s+1);lst=y;
    }
    add(L-lst,1);
    printf("%.15lf\n",ans);
}