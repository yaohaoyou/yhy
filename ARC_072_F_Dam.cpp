#pragma GCC optimize(2,3,"Ofast")
#include<bits/stdc++.h>
#define ll long long
#define db double
#define eb emplace_back
#define pii pair<int,int>
#define pdi pair<db,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e6+10,maxx=110;
int n,m;
int t[maxn],v[maxn];
ll s[maxn];
db mix(db t1,int v1,db t2,int v2){return (t1*v1+t2*v2)/(v1+v2);}
pdi q[maxn];int hd=1,en;
int main(){
    // freopen("soda.in","r",stdin);freopen("soda.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d%d",&t[i],&v[i]);
    db ans=0;
    int now=0;
    for(int i=1;i<=n;i++){
        ans+=(1ll*t[i]*v[i]);
        now+=v[i];
        q[++en]=pdi(t[i],v[i]);

        while(hd<=en&&now-q[hd].se>=m){now-=q[hd].se;ans-=q[hd].fi*q[hd].se;hd++;}
        if(hd<=en&&now>m){
            q[hd].se-=(now-m);
            ans-=q[hd].fi*(now-m);
            now=m;
        }
        while(en-hd+1>=2&&q[en].fi<q[en-1].fi){
            en--;
            q[en].fi=mix(q[en].fi,q[en].se,q[en+1].fi,q[en+1].se);
            q[en].se+=q[en+1].se;
        }
        printf("%.7lf\n",ans/m);
    }
}